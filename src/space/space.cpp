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

#include "graph/graph.h"
#include "graph/node.h"
#include "graph/externaldependency.h"
#include "graph/nodeparser.h"
#include "graph/externaldependencyresolver.h"

namespace hive {

Space::Space(std::string&& name, std::string&& architecture,
	      std::unique_ptr<Graph>&& graph, std::unique_ptr<ExternalDependencyResolver> external_resolver)
: name{std::move(name)}, architecture{std::move(architecture)},
dependency_graph{std::move(graph)}, external_resolver{std::move(external_resolver)} {}

Space::~Space() {}

} //hive
