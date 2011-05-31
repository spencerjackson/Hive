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

class Directory;
class File;
class Node;

class NodeParser {
public:
	NodeParser();
	virtual ~NodeParser();

	void add_node(std::shared_ptr<Node> const& node);
	void add_collection(Directory const& directory);
	void add_file(File const& file);

	std::shared_ptr<Node> get_node(std::string const& name) const;

protected:
	std::unordered_map< std::string, std::shared_ptr<Node> > node_pool;
};

} //hive

#endif // NODEPARSER_H
