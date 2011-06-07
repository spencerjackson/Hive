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


#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <list>

class ArgumentParserState;
class ArgumentParser {
public:
	ArgumentParser(const int argc, const char * const * const argv);
	virtual ~ArgumentParser();

	void set_state(std::string const& state_name);
	void set_failure_state(std::string const& state);
	void add_state(std::shared_ptr<ArgumentParserState> state);

	void execute();

protected:
	const int argc;
	const char * const * const argv;
	std::shared_ptr< ArgumentParserState > state;
	std::shared_ptr< ArgumentParserState > failure_state;
	std::unordered_map< std::string, std::shared_ptr<ArgumentParserState> > possible_states;

};

#endif // ARGUMENTPARSER_H
