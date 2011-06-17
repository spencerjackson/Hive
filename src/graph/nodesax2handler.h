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


#ifndef NODESAX2HANDLER_H
#define NODESAX2HANDLER_H

#include <string>
#include <list>

#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

class NodeSAX2Handler : public xercesc::DefaultHandler {
public:
	NodeSAX2Handler();
	virtual ~NodeSAX2Handler();

	virtual void startElement(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname,
		const xercesc::Attributes& attrs
	);
	virtual void fatalError(const xercesc::SAXParseException&);
	virtual void characters(const XMLCh *const chars, const unsigned int length);
	virtual void endElement(const XMLCh *const uri,
		const XMLCh *const localname,
		const XMLCh *const qname
	);

	std::string get_name() const;
	std::list<std::string> get_external_dependencies() const;
	std::list<std::string> get_dependencies() const;
protected:
	XMLCh* buffer;
	std::string name;
	std::list<std::string> external_dependencies;
	std::list<std::string> dependencies;

};

#endif // NODESAX2HANDLER_H
