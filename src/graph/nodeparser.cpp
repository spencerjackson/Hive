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


#include "nodeparser.h"

#include <regex>
#include <iostream>
#include "fcntl.h"
#include <fstream>
#include <stdexcept>


#include "node.h"
#include "nodesax2handler.h"
#include "graph.h"
#include "externaldependencymapperinterface.h"
#include "util/io/file.h"
#include "util/io/directory.h"
#include "util/io/resourcereference.h"
#include "util/xml/xercessax2parser.h"

namespace hive {

NodeParser::NodeParser(std::shared_ptr<ExternalDependencyMapperInterface> mapper,
		       std::shared_ptr<Graph> graph)
: parser{new XercesSAX2Parser{}}, mapper{mapper}, graph{graph} {}

NodeParser::~NodeParser() {}

void NodeParser::add_collection(Directory const& directory) {
	for (ResourceReference &subdir_ref : directory.get_directories()) {
		Directory subdir{subdir_ref};
		for (ResourceReference &file : subdir.get_files(std::regex{"manifest.xml"})) {
			try {
				add_file(file);
			} catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
		}
	}
}

void NodeParser::add_file(ResourceReference const& file) {
	NodeSAX2Handler handler;
	parser->parse(file, &handler, &handler);
	std::shared_ptr<Node> node{new Node{handler.get_name()}};
	graph->add_node(node);
	//Record external dependencies
	for (std::string& external_dependency : handler.get_external_dependencies()) {
		node->add_external_dependency(mapper->map(external_dependency));
	}
	//Add internal dependencies to the graph
	for (std::string& dependency : handler.get_dependencies()) {
		if (graph->has_node(dependency)) graph->add_directed_edge(node, graph->get_node(dependency));
		//We haven't yet found the Node's dependency... note this and add it later
		else {
			unresolved_edges.insert(std::make_pair(dependency, node));
		}
	}
	//Check whether this Node resolves any previously unresolvable dependencies
	for (std::unordered_multimap<std::string, std::shared_ptr<Node> >::iterator it = unresolved_edges.equal_range(node->get_name()).first; it != unresolved_edges.equal_range(node->get_name()).second; it++) {
		graph->add_directed_edge(it->second, node);
		unresolved_edges.erase(it);
	}
}


} //hive

