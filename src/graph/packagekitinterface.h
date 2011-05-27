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


#ifndef PACKAGEKITINTERFACE_H
#define PACKAGEKITINTERFACE_H

#include <string>
#include <unordered_map>

#include "externaldependencyresolver.h"

typedef struct _DBusGConnection DBusGConnection;
typedef struct _DBusGProxy DBusGProxy;

namespace hive {
class PackageKitInterface : public ExternalDependencyResolver {

public:
	PackageKitInterface(std::unique_ptr<ExternalDependencyMapperInterface>&& mapper);
	virtual ~PackageKitInterface();

	virtual void resolve();

protected:
	DBusGConnection *connection;
	DBusGProxy *proxy;

};
} //hive

#endif // PACKAGEKITINTERFACE_H
