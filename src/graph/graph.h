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


#ifndef GRAPH_H
#define GRAPH_H
#include <memory>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>


#include "node.h"

namespace hive {

class Graph {
public:
	Graph();
	virtual ~Graph();

	void add_node(Node const& node);
	Node get_node(std::string const& name) const;
	void add_directed_edge(Node const& parent, Node const& child);

	std::list<Node const *> get_linearization() const;
	/** Return a graph consisting of the specified nodes and all children */
	Graph get_subset(std::list<std::string> const& items) const;

	void add_subset(Graph const& graph);
	void add_subset(Graph&& graph);
protected:
	std::list< Node const * > get_basal_nodes() const;
	std::unordered_map< std::string, Node > node_pool;
	std::unordered_map< Node const *, std::list<Node*> > out_edges;
	std::unordered_map< Node const *, std::list<Node*> > in_edges;
	std::unordered_set<Node const *> basal_nodes;

};

} //hive

#endif // GRAPH_H
