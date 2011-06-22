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


#ifndef GRAPH_H
#define GRAPH_H
#include <memory>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace hive {

class Node;

class Graph {
public:
	Graph();
	virtual ~Graph();

	void add_node(std::shared_ptr<Node> node);
	std::shared_ptr<Node> get_node(std::string const& name) const;
	bool has_node(std::string const& name) const;
	void add_directed_edge(std::shared_ptr<const Node> const& parent, std::shared_ptr<const Node> const& child);

	std::list<std::shared_ptr<const Node> > get_linearization() const;
	/** Return a sub graph consisting of the specified nodes and all children */
	Graph copy_component(std::list<std::string> const& items) const;
	Graph copy_component(std::string const& item) const;

	void add_component(Graph const& graph);
	void add_component(Graph&& graph);
protected:
	void copy_component_rec(Graph& graph, std::shared_ptr<Node> node) const;
	std::list<std::shared_ptr<const Node> > get_basal_nodes() const;
	std::unordered_map< std::string, std::shared_ptr<Node> > node_pool;
	std::unordered_map< std::shared_ptr<const Node>, std::list<std::shared_ptr<const Node> > > out_edges;
	std::unordered_map< std::shared_ptr<const Node>, std::list<std::shared_ptr<const Node> > > in_edges;
	std::unordered_set<std::shared_ptr<const Node> > basal_nodes;

};

} //hive

#endif // GRAPH_H
