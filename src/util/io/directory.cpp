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


#include "directory.h"

#include "dirent.h"

namespace hive {

Directory::Directory(std::string const& path) : path(path), dir(opendir(path.c_str())) {}

Directory::Directory(ResourceReference const& resource) : path(resource.get_path()), dir(opendir(resource.get_path().c_str())) {}

Directory::~Directory() {
	closedir(dir);
}

std::list< ResourceReference > Directory::get_directories(std::regex const& restriction) const {
	std::list< ResourceReference > ret;
	dirent* entry = NULL;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR && is_valid_path(entry->d_name)
			&& std::regex_match(entry->d_name, restriction)) ret.push_back(ResourceReference(path+"/"+entry->d_name));
	}
	return ret;
}

std::list< ResourceReference > Directory::get_files(std::regex const& restriction) const {
	std::list< ResourceReference > ret;
	dirent* entry = NULL;
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_REG &&
			std::regex_match(entry->d_name, restriction)
		) ret.push_back(ResourceReference(path+"/"+entry->d_name));
	}
	return ret;
}

bool Directory::is_valid_path(const std::string& path) const {
	return path != "." && path != "..";
}

} //hive
