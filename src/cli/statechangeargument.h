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


#ifndef STATECHANGEARGUMENT_H
#define STATECHANGEARGUMENT_H

#include "argument.h"

#include <memory>

class ArgumentParserState;
class StateChangeArgument : public Argument {
public:
	StateChangeArgument(std::list<std::string>&& possible_tokens, std::string const& description, std::shared_ptr<ArgumentParserState> state);
	virtual ~StateChangeArgument();

	virtual unsigned int get_argument_count() const;

	virtual void operator()(ArgumentParser&, std::list<std::string>&&);
protected:
	std::shared_ptr<ArgumentParserState> state;
};

#endif // STATECHANGEARGUMENT_H
