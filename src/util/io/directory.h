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


#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <list>

#include "file.h"
#include "resourcereference.h"


typedef struct __dirstream DIR;

namespace hive {

class Directory {
public:
	Directory(std::string const& path);
	Directory(ResourceReference const& resource);
	virtual ~Directory();

	std::list<ResourceReference> get_files() const;
	std::list<ResourceReference> get_directories() const;

protected:
	bool is_valid_path(std::string const& path) const;
	std::string path;
	DIR* dir;

};

} //hive

#endif // DIRECTORY_H
