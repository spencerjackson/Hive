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

#include "xercessax2parser.h"

#include <string>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/ContentHandler.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

namespace hive {

XercesSAX2Parser::XercesSAX2Parser() : parser(xercesc::XMLReaderFactory::createXMLReader()) {
	parser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
}

XercesSAX2Parser::~XercesSAX2Parser() {
	delete parser;
}

void XercesSAX2Parser::parse(const std::string& filepath, xercesc::ContentHandler* content, xercesc::ErrorHandler* error) {
	parser->setContentHandler(content);
	parser->setErrorHandler(error);
	parser->parse(filepath.c_str());
}

}