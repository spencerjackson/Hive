/*
    <one line to give the program's name and a brief idea of what it does.>
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

namespace hive {

Graph::Graph() {}

Graph::~Graph() {}

void Graph::add_node(Node const& node) {
	node_pool.insert(std::pair<std::string, Node>(node.get_name(), Node{node.get_name()}));
	out_edges[&(node_pool.at(node.get_name()))] = std::list<Node*>{};
	in_edges[&(node_pool.at(node.get_name()))] = std::list<Node*>{};
	basal_nodes.insert(&(node_pool.at(node.get_name())));
}

Node Graph::get_node(std::string const& name) const {
	return node_pool.at(name);
}

void Graph::add_directed_edge(Node const& parent, Node const& child) {
	out_edges[&(node_pool.at(parent.get_name()))].push_back(&(node_pool.at(child.get_name())));
	in_edges[&(node_pool.at(child.get_name()))].push_back(&(node_pool.at(parent.get_name())));
	basal_nodes.erase(&(node_pool.at(parent.get_name())));
}

std::list< Node const * > Graph::get_basal_nodes() const {
	std::list<Node const *> ret;
	for (Node const * node : basal_nodes) {
		ret.push_back(node);
	}
	return ret;
}

std::list<Node const*> Graph::get_linearization() const {
	std::queue< Node const * > nodes;
	std::unordered_set<Node const *> processed;
	std::list<Node const *> ret{};
	for (Node const * node : get_basal_nodes()) {
		nodes.push(node);
	}
	while (!nodes.empty()) {
		Node const * node = nodes.front();
		processed.insert(node);
		for (Node * reverse_dependency : in_edges.at(node)) {
			bool resolved = true;
			for (Node * reverse_dependency_dependency : out_edges.at(reverse_dependency)) {
				if (processed.find(reverse_dependency_dependency) == processed.end()) {
					resolved = false;
					break;
				}
			}
			if (resolved) {
				nodes.push(reverse_dependency);
			}
		}
		nodes.pop();
		ret.push_back(node);
	}
	return ret;
}


} //hive