/*
    Hive: A robotics package manager
    Copyright (C) 2011  Spencer Jackson <spencerandrewjackson@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "graph.h"

#include <queue>

#include "node.h"

namespace hive {

Graph::Graph() {}

Graph::~Graph() {}

void Graph::add_node(std::shared_ptr<Node> node) {
	node_pool[node->get_name()] = node;
	out_edges[node] = std::list<std::shared_ptr<const Node> >{};
	in_edges[node] = std::list<std::shared_ptr<const Node> >{};
	basal_nodes.insert(node_pool.at(node->get_name()));
}

std::shared_ptr<Node> Graph::get_node(std::string const& name) const {
	return node_pool.at(name);
}

void Graph::add_directed_edge(std::shared_ptr<const Node> const& parent, std::shared_ptr<const Node> const& child) {
	out_edges[parent].push_back(child);
	in_edges[parent].push_back(child);
	basal_nodes.erase(child);
}

std::list<std::shared_ptr<const Node> > Graph::get_basal_nodes() const {
	std::list<std::shared_ptr<const Node> > ret;
	for (std::shared_ptr<const Node> node : basal_nodes) {
		ret.push_back(node);
	}
	return ret;
}

Graph Graph::copy_component(std::list< std::string > const& items) const {
	Graph ret{};
	for (std::string const &item : items) {
		ret.add_component(copy_component(item));
	}
	return ret;
}

void Graph::copy_component_rec(Graph& graph, std::shared_ptr<Node> node) const {
	graph.add_node(node);
	for (std::shared_ptr<const Node> const& child : out_edges.at(node)) {
		std::shared_ptr<Node> child_copy{new Node{*child}};
		graph.add_node(child_copy);
		graph.add_directed_edge(node, child_copy);
		copy_component_rec(graph, child_copy);
	}
}

Graph Graph::copy_component(std::string const& item) const {
	Graph ret{};
	std::shared_ptr<Node> node = get_node(item);
	copy_component_rec(ret, node);
	return ret;
}

void Graph::add_component(Graph const& graph) {
	std::unordered_map<std::shared_ptr<const Node>, std::shared_ptr<const Node> > node_map;
	//Copy the nodes into the local node pool
	for (std::unordered_map< std::string, std::shared_ptr<Node> >::const_iterator iter = graph.node_pool.begin();
	     iter != graph.node_pool.end(); iter++) {
		std::shared_ptr<Node> local_node{new Node{*(iter->second)}};
		add_node(local_node);
		node_map[iter->second] = local_node;
	}
	//Copy the edges into the local edge lists
	for (std::unordered_map< std::string, std::shared_ptr<Node> >::const_iterator iter = graph.node_pool.begin();
	     iter != graph.node_pool.end(); iter++) {
		for (std::shared_ptr<const Node> const& edge_destination : graph.out_edges.at(iter->second)) {
			out_edges[node_map.at(iter->second)].push_back(node_map.at(edge_destination));
		}
		for (std::shared_ptr<const Node> const& edge_origin : graph.in_edges.at(iter->second)) {
			in_edges[node_map.at(iter->second)].push_back(node_map.at(edge_origin));
		}
	}
}

void Graph::add_component(Graph&& graph) {
	for (std::pair<const std::string, std::shared_ptr<Node> > keyvalue : graph.node_pool) {
		add_node(keyvalue.second);
	}
	for (std::pair<std::shared_ptr<const Node>, std::list<std::shared_ptr<const Node> > > edges : graph.out_edges) {
		for (std::shared_ptr<const Node> edge : edges.second) {
			//TODO: Can this cause redundant edges?
			out_edges[edges.first].push_back(edge);
		}
	}
}


std::list<std::shared_ptr<const Node> > Graph::get_linearization() const {
	std::queue<std::shared_ptr<const Node> > nodes;
	std::unordered_set<std::shared_ptr<const Node> > processed;
	std::list<std::shared_ptr<const Node> > ret{};
	for (std::shared_ptr<const Node> node : get_basal_nodes()) nodes.push(node);
	while (!nodes.empty()) {
		std::shared_ptr<const Node> node = nodes.front();
		nodes.pop();
		processed.insert(node);
		for (std::shared_ptr<const Node> reverse_dependency : in_edges.at(node)) {
			bool resolved = true;
			for (std::shared_ptr<const Node> reverse_dependency_dependency : out_edges.at(reverse_dependency)) {
				if (processed.find(reverse_dependency_dependency) == processed.end()) {
					resolved = false;
					break;
				}
			}
			if (resolved) {
				nodes.push(reverse_dependency);
			}
		}
		ret.push_back(node);
	}
	return ret;
}


} //hive