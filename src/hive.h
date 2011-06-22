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


#ifndef HIVE_H
#define HIVE_H

#include <memory>
#include <string>
#include <list>

namespace hive {

class Graph;


class ExternalDependencyMapper;
class NodeParser;
class MapParser;
class Space;

class Hive {
public:
	Hive(std::list<std::string>&& collections, std::list<std::string>&& spaces);
	virtual ~Hive();

	void exec();
protected:
	std::shared_ptr<Graph> available_packages;
	std::shared_ptr<ExternalDependencyMapper> mapper;
	std::shared_ptr<NodeParser> node_parser;
	std::shared_ptr<MapParser> map_parser;
	std::list<std::shared_ptr<Space> > spaces;
};

} //hive

#endif // HIVE_H
