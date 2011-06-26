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


#include "mapsax2handler.h"

#include "xercesc/sax2/Attributes.hpp"

#include "externaldependencymapper.h"

namespace hive {

MapSAX2Handler::MapSAX2Handler(std::string const& distro, std::shared_ptr<ExternalDependencyMapper> mapper)
: distro{distro}, mapper{mapper}, buffer{xercesc::XMLString::transcode("")} {}

MapSAX2Handler::~MapSAX2Handler() {}

void MapSAX2Handler::endElement(const XMLCh*const uri, const XMLCh*const localname, const XMLCh*const qname) {
	if (parse_next_pair) {
		mapper->add_map(key, std::string{xercesc::XMLString::transcode(buffer)});
	}
}

void MapSAX2Handler::startElement(const XMLCh*const uri, const XMLCh*const localname, const XMLCh*const qname, const xercesc_3_0::Attributes& attrs) {
	if (!xercesc::XMLString::compareIString(localname, xercesc::XMLString::transcode("map"))) {
		key = std::string{xercesc::XMLString::transcode(attrs.getValue(xercesc::XMLString::transcode("key")))};
	}
	if (!xercesc::XMLString::compareIString(localname, xercesc::XMLString::transcode("value"))) {
		parse_next_pair = (!xercesc::XMLString::compareIString(attrs.getValue(xercesc::XMLString::transcode("distribution")), xercesc::XMLString::transcode(distro.c_str())));
	}

	buffer = xercesc::XMLString::transcode("");
}

} //hive

