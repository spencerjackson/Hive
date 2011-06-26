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


#ifndef DEFAULTXERCESSAX2HANDLER_H
#define DEFAULTXERCESSAX2HANDLER_H

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

namespace hive {

class DefaultXercesSAX2Handler : public xercesc::DefaultHandler {
public:
	DefaultXercesSAX2Handler();

	virtual void fatalError(const xercesc::SAXParseException&);
	virtual void startElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname,
		const xercesc::Attributes& attrs
	);
	virtual void characters(const XMLCh *const chars, const XMLSize_t length);

	virtual void endElement(const XMLCh *const uri,
		const XMLCh *const localname,
		const XMLCh *const qname
	) = 0;
protected:
	XMLCh* buffer;


};

} //hive

#endif // DEFAULTXERCESSAX2HANDLER_H
