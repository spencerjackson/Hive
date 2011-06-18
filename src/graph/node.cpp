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
Node::Node(std::string const& name) : name(name) {}

Node::~Node() {}

void Node::add_external_dependency(std::shared_ptr<ExternalDependency> const& dependency) {
	external_dependencies.push_back(dependency);
}

std::list< std::shared_ptr<ExternalDependency> > Node::get_external_dependencies() const {
	return external_dependencies;
}

} //hive
