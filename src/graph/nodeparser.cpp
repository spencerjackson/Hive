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

#include <iostream>
#include "fcntl.h"
#include <fstream>
#include <stdexcept>


#include "node.h"
#include "nodesax2handler.h"
#include "util/io/file.h"
#include "util/io/directory.h"
#include "util/io/resourcereference.h"
#include "util/xml/xercessax2parser.h"
#include "exceptions/parserexception.h"
#include "exceptions/invalidparserrequestexception.h"

namespace hive {

NodeParser::NodeParser() : parser(new XercesSAX2Parser{}) {}

NodeParser::~NodeParser() {}

void NodeParser::add_node(std::shared_ptr< Node > const& node) {
	node_pool[node->get_name()] = node;
}

void NodeParser::add_collection(Directory const& directory) {
	for (ResourceReference &subdir_ref : directory.get_directories()) {
		Directory subdir{subdir_ref};
		for (ResourceReference &file : subdir.get_files()) {
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
	node_pool[handler.get_name()] = std::shared_ptr<Node>{new Node{handler.get_name(), handler.get_dependencies()}};
}

std::shared_ptr<Node> NodeParser::get_node(std::string const& name) const {
	try {
		return node_pool.at(name);
	} catch (std::out_of_range& e) {
		throw (InvalidParserRequestException(name));
	}
}


} //hive

