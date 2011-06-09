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


#ifndef RESOURCEREFERENCE_H
#define RESOURCEREFERENCE_H

#include <string>

namespace hive {

class ResourceReference {
public:
	ResourceReference(std::string const& path);
	~ResourceReference();

	std::string get_path() const;
	operator std::string() const;
protected:
	std::string path;
};

} //hive

#endif //RESOURCEREFERENCE_H
