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


#include "externaldependencymapper.h"

#include <stdexcept>

#include "exceptions/unknownmapexception.h"

namespace hive {
ExternalDependencyMapper::ExternalDependencyMapper() {}

ExternalDependencyMapper::~ExternalDependencyMapper() {}

void ExternalDependencyMapper::add_map(std::string const& key, std::string const& value) {
	internal_map[key] = std::shared_ptr<ExternalDependency>{new ExternalDependency{value}};
}
std::shared_ptr<ExternalDependency> ExternalDependencyMapper::map(std::string const& dependency) const {
	try {
		internal_map.at(dependency);
	} catch (std::out_of_range e) {
		throw UnknownMapException(dependency);
	}
}

} //hive
