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


#ifndef INTERSTATEARGUMENT_H
#define INTERSTATEARGUMENT_H
#include "argument.h"

class InterstateArgument : public Argument {
public:
	InterstateArgument(std::list<std::string>&& possible_tokens, std::string const& description,
			   int arguments, std::function<void (ArgumentParserState*, ArgumentParser&, std::list<std::string>&&)> function);
	virtual ~InterstateArgument();

	virtual unsigned int get_argument_count() const;

	virtual void register_state(ArgumentParserState* state);
	virtual void operator()(ArgumentParser&, std::list<std::string>&&);
protected:
	const int arguments;
	const std::function<void (ArgumentParserState*, ArgumentParser&, std::list<std::string>&&)> function;
	ArgumentParserState* state;
};

#endif // INTERSTATEARGUMENT_H
