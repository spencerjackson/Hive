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


#ifndef MAPSAX2HANDLER_H
#define MAPSAX2HANDLER_H

#include <memory>
#include <string>

#include <util/xml/defaultxercessax2handler.h>

namespace hive {
class ExternalDependencyMapper;

class MapSAX2Handler : public DefaultXercesSAX2Handler {
public:
	MapSAX2Handler(std::string const& distro, std::shared_ptr<ExternalDependencyMapper> mapper);
	virtual ~MapSAX2Handler();

	virtual void startElement(const XMLCh*const uri,
						  const XMLCh*const localname,
					   const XMLCh*const qname,
					   const xercesc_3_0::Attributes& attrs);

	virtual void endElement(const XMLCh *const uri,
		const XMLCh *const localname,
		const XMLCh *const qname
	);
protected:
	std::string distro;
	std::shared_ptr<ExternalDependencyMapper> mapper;

	std::string key;
	bool parse_next_pair;
	XMLCh* buffer;
};

} //hive

#endif // MAPSAX2HANDLER_H
