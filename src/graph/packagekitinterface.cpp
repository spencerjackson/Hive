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

#include <iostream>

#include "packagekitinterface.h"
#include "externaldependency.h"

#include <dbus/dbus-glib.h>
#include "string.h"

namespace hive {

PackageKitInterface::PackageKitInterface(std::unique_ptr<ExternalDependencyMapperInterface>&& mapper)
: ExternalDependencyResolver(std::move(mapper)) {
	g_type_init();
	/* get a session bus connection */
	connection = dbus_g_bus_get (DBUS_BUS_SESSION, NULL);

	/* connect to PackageKit */
	proxy = dbus_g_proxy_new_for_name (connection,
					   "org.freedesktop.PackageKit",
					   "/org/freedesktop/PackageKit",
					   "org.freedesktop.PackageKit.Modify");
}

PackageKitInterface::~PackageKitInterface() {
}

void PackageKitInterface::resolve() {
	GError *error = NULL;
	gboolean ret;

	//We have package names. To use them, they must be resolved through PackageKit.
	gpointer resolved_packages = NULL;
	//First, convert the strings to gchar**
	gchar** packages = new gchar*[unresolved_dependencies.size()+1];
	{
		unsigned int index = 0;
		for (std::shared_ptr<ExternalDependency> package : unresolved_dependencies) {
			packages[index++] = strdup(package->get_dependency_name().c_str());
		}
		packages[index] = NULL;
	}
	//Invoke PackageKit
	/* execute sync method */
	ret = dbus_g_proxy_call (proxy, "InstallPackageNames", &error,
				 G_TYPE_UINT, 0, /* window xid, 0 for none */
				 G_TYPE_STRV, packages,
				 G_TYPE_STRING, "show-confirm-search,hide-finished",
				 G_TYPE_INVALID, G_TYPE_INVALID);
	//FIXME: Check for failures
}


} //hive

