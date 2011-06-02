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


#include "unknownmapexception.h"

#include "util/l10n/l10n.h"

namespace hive {

UnknownMapException::UnknownMapException(std::string const& package_key) : package_key(package_key) {}

UnknownMapException::~UnknownMapException() throw() {}

//TODO: Include distribution name
const char* UnknownMapException::what() const throw() {
	return _("The package %s does not have a known mapping for your OS.");
}


} //hive
