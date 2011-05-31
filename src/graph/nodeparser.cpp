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

#include "node.h"
#include <graph/protocolbuffers/packagedescription.pb.h>
#include "nodefactory.h"
#include "util/io/file.h"
#include "util/io/directory.h"
#include "util/io/resourcereference.h"

namespace hive {

NodeParser::NodeParser() {}

NodeParser::~NodeParser() {}

void NodeParser::add_node(std::shared_ptr< Node > const& node) {
	node_pool[node->get_name()] = node;
}

void NodeParser::add_collection(Directory const& directory) {
	for (ResourceReference &subdir_ref : directory.get_directories()) {
		Directory subdir{subdir_ref};
		for (ResourceReference &file : subdir.get_files()) {
			add_file(File(file, O_RDONLY));
		}
	}
}

void NodeParser::add_file(File const& file) {
	PackageDescription deserialized_package;
	if (!deserialized_package.ParseFromFileDescriptor(file)) return;
	add_node(NodeFactory::construct_node(deserialized_package));
}

std::shared_ptr<Node> NodeParser::get_node(std::string const& name) const {
	return node_pool.at(name);
}


} //hive

