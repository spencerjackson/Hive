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


#ifndef XERCESSAX2PARSER_H
#define XERCESSAX2PARSER_H

#include <string>

#include "xercesparser.h"
#include "xercesc/sax2/ContentHandler.hpp"
#include "xercesc/sax/ErrorHandler.hpp"
#include "xercesc/sax2/SAX2XMLReader.hpp"

namespace hive {

class XercesSAX2Parser : public XercesParser {
public:
	XercesSAX2Parser();
	virtual ~XercesSAX2Parser();

	void parse(std::string const& filepath, xercesc::ContentHandler* content, xercesc::ErrorHandler* error);
protected:
	xercesc::SAX2XMLReader* parser;
};

} //hive

#endif // XERCESSAX2PARSER_H
