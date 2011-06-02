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

#include "nodefactory.h"

#include "node.h"

#include "graph/protocolbuffers/packagedescription.pb.h"
#include "externaldependencypool.h"

namespace hive {

std::shared_ptr<Node> NodeFactory::construct_node(PackageDescription const& package) {
	std::shared_ptr<Node> ret{ new Node{package.name()}};
	//Add dependencies
	for (int i = 0; i < package.external_dependency_size(); i++) {
		ExternalDependencyPool::add_dependency(package.external_dependency(i));
		ret->add_external_dependency(ExternalDependencyPool::get_dependency(package.external_dependency(i)));
	}
	for (int i = 0; i < package.dependency_size(); i++) {
		ret->add_unresolved_dependency(package.dependency(i));
	}
	return ret;
}


} //hive
