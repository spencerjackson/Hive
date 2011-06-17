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


#include "space.h"

#include "graph/node.h"
#include "graph/externaldependency.h"
#include "graph/nodeparser.h"
#include "graph/externaldependencyresolver.h"

namespace hive {

Space::Space(std::shared_ptr<NodeParser> parser,
		      std::unique_ptr<ExternalDependencyResolver>&& external_resolver)
: parser(parser), external_resolver(std::move(external_resolver)) {}

Space::~Space() {}

void Space::add_package(std::string const& name) {
	std::shared_ptr<Node> node = parser->get_node(name);
	//Resolve dependencies
	for (std::shared_ptr<ExternalDependency> &external_dependency : node->get_external_dependencies()) {
		external_dependencies.insert(external_dependency);
	}
	resolve_internal_dependency(node);
}

void Space::resolve_internal_dependency(std::shared_ptr<Node> node) const {
	for (std::string &dependency_name : node->get_unresolved_dependencies()) {
		std::shared_ptr<Node> dependency = parser->get_node(dependency_name);
		node->add_dependency(dependency);
		resolve_internal_dependency(dependency);
	}
}
} //hive
