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

#ifndef EXTERNALDEPENDENCYRESOLVER_H
#define EXTERNALDEPENDENCYRESOLVER_H

#include <memory>
#include <list>

namespace hive {

class ExternalDependency;
class ExternalDependencyMapper;
class NativePackageManagerInterface;

class ExternalDependencyResolver {

public:
	ExternalDependencyResolver(std::unique_ptr<ExternalDependencyMapper>&& mapper);
	virtual ~ExternalDependencyResolver();

	bool is_resolved() const;
	void add_unresolved_dependency(const std::shared_ptr<ExternalDependency>& dependency);
	virtual void resolve() = 0;

protected:
	std::unique_ptr<ExternalDependencyMapper> mapper;
	std::list<std::shared_ptr<ExternalDependency> > unresolved_dependencies;

};

} //hive

#endif // EXTERNALDEPENDENCYRESOLVER_H
