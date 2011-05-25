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

#include "node.h"

namespace hive {
Node::Node(std::string const& name, std::list<std::string>&& unresolved_dependencies) : name(name),
unresolved_dependencies(std::move(unresolved_dependencies)) {}

Node::~Node() {}

void Node::add_dependency(std::shared_ptr<Node> const& dependency) {
	//Check if dependency exists in unresolved list, and remove it
	std::list<std::string>::iterator it = unresolved_dependencies.begin();
	while (it !=unresolved_dependencies.end() || *it != dependency->get_name()) {}
	if (it !=unresolved_dependencies.end()) unresolved_dependencies.erase(it);
	dependency->add_reverse_dependency(std::shared_ptr<Node>(shared_from_this()));
	dependencies.push_back(dependency);
}

void Node::add_reverse_dependency(std::shared_ptr<Node> const& reverse_dependency) {
	reverse_dependencies.push_back(reverse_dependency);
}

void Node::add_external_dependency(std::shared_ptr<ExternalDependency> const& dependency) {
	external_dependencies.push_back(dependency);
}

void Node::add_unresolved_dependency(std::string const& dependency) {
	unresolved_dependencies.push_back(dependency);
}

bool Node::is_resolved() const {
	return unresolved_dependencies.empty();
}

std::list< std::shared_ptr<Node> > Node::get_dependencies() const {
	return dependencies;
}

std::list< std::shared_ptr<ExternalDependency> > Node::get_external_dependencies() const {
	return external_dependencies;
}

std::list< std::string > Node::get_unresolved_dependencies() const {
	return unresolved_dependencies;
}

} //hive
