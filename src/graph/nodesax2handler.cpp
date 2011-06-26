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


#include "nodesax2handler.h"

namespace hive {

NodeSAX2Handler::NodeSAX2Handler() {}

NodeSAX2Handler::~NodeSAX2Handler() {}

void NodeSAX2Handler::endElement(const XMLCh*const uri, const XMLCh*const localname, const XMLCh*const qname) {
	if (!xercesc::XMLString::compareIString(localname, xercesc::XMLString::transcode("name"))) name = std::string(xercesc::XMLString::transcode(buffer));
	else if (!xercesc::XMLString::compareIString(localname, xercesc::XMLString::transcode("externalDependency"))) external_dependencies.push_back(std::string(xercesc::XMLString::transcode(buffer)));
	else if (!xercesc::XMLString::compareIString(localname, xercesc::XMLString::transcode("dependency"))) dependencies.push_back(std::string(xercesc::XMLString::transcode(buffer)));
}


std::string NodeSAX2Handler::get_name() const {
	return name;
}

std::list<std::string> NodeSAX2Handler::get_external_dependencies() const {
	return external_dependencies;
}

std::list<std::string> NodeSAX2Handler::get_dependencies() const {
	return dependencies;
}

} //hive

