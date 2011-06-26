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

#include "graph/graph.h"
#include "graph/externaldependencyresolver.h"
#include "spacesax2handler.h"
#include "util/xml/xercessax2parser.h"

namespace hive {

SpaceSAX2Handler::SpaceSAX2Handler()
:readable(false) {}

void SpaceSAX2Handler::endElement(const XMLCh*const uri, const XMLCh*const localname, const XMLCh*const qname) {
	//Found beginning of new Space. Dump currently parsed data
	if (!xercesc::XMLString::compareIString(localname, xercesc::XMLString::transcode("name"))) {
		name = std::string{xercesc::XMLString::transcode(buffer)};
		architecture.clear();
		packages = std::list<std::string>{};
		readable = false;
	} else if (!xercesc::XMLString::compareIString(localname, xercesc::XMLString::transcode("architecture"))) {
		architecture = std::string{xercesc::XMLString::transcode(buffer)};
		readable = true;
	} else if (!xercesc::XMLString::compareIString(localname, xercesc::XMLString::transcode("package"))) {
		packages.push_back(std::string{xercesc::XMLString::transcode(buffer)});
	}
}

Space SpaceSAX2Handler::read_space(std::shared_ptr<Graph> available_packages, std::unique_ptr<ExternalDependencyResolver>&& external_resolver) {
	std::unique_ptr<Graph> graph{new Graph{}};
	graph->add_component(available_packages->copy_component(packages));
	return Space{std::move(name), std::move(architecture), std::move(graph), std::move(external_resolver) };
}


} //hive