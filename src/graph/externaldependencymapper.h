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


#ifndef EXTERNALDEPENDENCYMAPPER_H
#define EXTERNALDEPENDENCYMAPPER_H

#include <string>
#include <unordered_map>
#include "externaldependencymapperinterface.h"

namespace hive {

class ExternalDependencyMapper : public ExternalDependencyMapperInterface {
public:
	ExternalDependencyMapper();
	virtual ~ExternalDependencyMapper();

	void add_map(std::string const& key, std::string const& value);
	virtual std::string map(std::string const& dependency) const;

protected:
	std::unordered_map<std::string, std::string> internal_map;
};

} //hive
#endif // EXTERNALDEPENDENCYMAPPER_H
