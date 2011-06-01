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


#include "externaldependencypool.h"

#include "externaldependency.h"

namespace hive {

std::unordered_map<std::string, std::shared_ptr<ExternalDependency> > ExternalDependencyPool::pool = std::unordered_map<std::string, std::shared_ptr<ExternalDependency> >{};

void ExternalDependencyPool::add_dependency(const std::string& dependency) {
	pool[dependency] = std::shared_ptr<ExternalDependency>{ new ExternalDependency{dependency} };
}

std::shared_ptr<ExternalDependency> ExternalDependencyPool::get_dependency(const std::string& dependency) {
	return pool.at(dependency);
}


} //hive

