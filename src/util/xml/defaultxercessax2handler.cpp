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


#include "defaultxercessax2handler.h"

#include "exception/parserexception.h"
#include "util/l10n/l10n.h"

namespace hive {

DefaultXercesSAX2Handler::DefaultXercesSAX2Handler() : buffer{xercesc::XMLString::transcode("")} {}

void DefaultXercesSAX2Handler::fatalError(const xercesc::SAXParseException& e) {
	throw ParserException{_("Unable to process XML. Received error %1% at line %2%, column %3%",
				std::string{xercesc::XMLString::transcode(e.getMessage())}, e.getLineNumber(), e.getColumnNumber())};
}


void DefaultXercesSAX2Handler::startElement(const XMLCh*const uri, const XMLCh*const localname, const XMLCh*const qname, const xercesc_3_0::Attributes& attrs) {
	buffer = xercesc::XMLString::transcode("");
}

void DefaultXercesSAX2Handler::characters(const XMLCh *const chars, const XMLSize_t length){
	xercesc::XMLString::catString(buffer, chars);
}

} //hive
