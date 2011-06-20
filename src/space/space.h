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


#ifndef SPACE_H
#define SPACE_H

#include <memory>
#include <list>
#include <string>
#include <unordered_set>

namespace hive {

class Graph;
class ExternalDependencyResolver;
class ExternalDependency;
class Node;
class NodeParser;


class Space {
public:
	Space(std::string&& name, std::string&& architecture,
	      std::unique_ptr<Graph>&& graph, std::unique_ptr<ExternalDependencyResolver> external_resolver);
	virtual ~Space();

protected:
	std::string name;
	std::string architecture;
	std::unordered_set< std::shared_ptr<ExternalDependency> > external_dependencies;
	std::unique_ptr<ExternalDependencyResolver> external_resolver;
	std::unique_ptr<Graph> dependency_graph;
};

} //hive

#endif // SPACE_H
