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

#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>
#include <memory>

namespace hive {

class ExternalDependency;

class Node : public std::enable_shared_from_this<Node> {
public:
	Node(std::string const& name, std::list<std::string>&& unresolved_dependencies = std::list<std::string>{});
	virtual ~Node();

	std::string get_name() const {return name;}
	void add_dependency(std::shared_ptr<Node> const& dependency);
	void add_reverse_dependency(std::shared_ptr<Node> const& reverse_dependency);
	void add_external_dependency(std::shared_ptr<ExternalDependency> const& dependency);
	void add_unresolved_dependency(std::string const& dependency);

	bool is_resolved() const;
	std::list< std::shared_ptr<Node> > get_dependencies() const;
	std::list< std::shared_ptr<ExternalDependency> > get_external_dependencies() const;
	std::list< std::string > get_unresolved_dependencies() const;

protected:
	std::string name;
	std::list<std::shared_ptr<Node>> dependencies;
	std::list<std::shared_ptr<Node>> reverse_dependencies;
	std::list<std::shared_ptr<ExternalDependency>> external_dependencies;
	std::list<std::string> unresolved_dependencies;
};

} //hive

#endif // NODE_H
