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


#include "file.h"

#include "fcntl.h"
#include "unistd.h"
#include "errno.h"

#include "util/l10n/l10n.h"
#include "resourcereference.h"

#include "exception/filesystemexception.h"
#include "exception/filesystemopenexception.h"

namespace hive {

File::File(std::string const& path, int permissions) throw(FilesystemException)
: file(open(path.c_str(), permissions)) {
	if (file == -1) fail(path);
}

File::File(ResourceReference const& reference, int permissions) throw(FilesystemException)
: file(open(reference.get_path().c_str(), permissions)) {
	if (file == -1) fail(reference.get_path());
}

File::~File() throw() {
	close(file);
}

File::operator int() const {
	return file;
}

void File::fail(std::string const& resource_name) const throw(FilesystemException) {
	switch (errno) {
		case EACCES:
			throw(FilesystemOpenException(resource_name, l10n::_("Resource inaccessible")));
		case ENOENT:
			throw(FilesystemOpenException(resource_name, l10n::_("Resouce does not exist")));
		default:
			throw(FilesystemException());
	}
}


} //hive

