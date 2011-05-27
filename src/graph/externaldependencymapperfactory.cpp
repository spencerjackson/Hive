/*
    <one line to give the program's name and a brief idea of what it does.>
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


#include "externaldependencymapperfactory.h"

#include <string>

#include "externaldependencymapperinterface.h"
#include "dummyexternaldependencymapper.h"

#include "graph/protocolbuffers/packagemapcontainer.pb.h"
#include "externaldependencymapper.h"

namespace hive {

ExternalDependencyMapperFactory::ExternalDependencyMapperFactory() {}

ExternalDependencyMapperFactory::~ExternalDependencyMapperFactory() {}

std::unique_ptr< ExternalDependencyMapperInterface > ExternalDependencyMapperFactory::generate_mapper() const {
	return std::unique_ptr< ExternalDependencyMapperInterface >(new DummyExternalDependencyMapper{});
}
std::unique_ptr< ExternalDependencyMapperInterface > ExternalDependencyMapperFactory::generate_mapper(std::string const& distribution,
											     PackageMapContainer const& map) const {
	ExternalDependencyMapper* mapper = new ExternalDependencyMapper();
	std::unique_ptr< ExternalDependencyMapperInterface > ret(mapper);
	for (int package_index = 0; package_index < map.map_size(); package_index++) {
		for (int distro_index = 0; distro_index < map.map(package_index).value_size(); distro_index++) {
			if(map.map(package_index).value(distro_index).distro() == distribution) {
				mapper->add_map(map.map(package_index).package_name(), map.map(package_index).value(distro_index).value());
				break;
			}
		}
	}
	return ret;
}


} //hive

