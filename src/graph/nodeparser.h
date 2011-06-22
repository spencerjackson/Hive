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


#ifndef NODEPARSER_H
#define NODEPARSER_H

#include <unordered_map>
#include <memory>
#include <string>

namespace hive {

class XercesSAX2Parser;
class ResourceReference;
class Directory;
class Node;
class Graph;
class ExternalDependencyMapperInterface;

class NodeParser {
public:
	NodeParser(std::shared_ptr<ExternalDependencyMapperInterface> mapper, std::shared_ptr<Graph> graph);
	virtual ~NodeParser();

	void add_collection(Directory const& directory);
	void add_file(ResourceReference const& file);

protected:
	std::unique_ptr<XercesSAX2Parser> parser;
	std::shared_ptr<ExternalDependencyMapperInterface> mapper;
	std::unordered_multimap<std::string, std::shared_ptr<Node> > unresolved_edges;
	std::shared_ptr<Graph> graph;
};

} //hive

#endif // NODEPARSER_H
