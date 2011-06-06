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


#include "argumentparser.h"

#include <iostream>

#include "argumentparserstate.h"

ArgumentParser::ArgumentParser(const int argc, const char * const * const argv)
: argc(argc), argv(argv) {}

ArgumentParser::~ArgumentParser() {}

void ArgumentParser::add_state(std::shared_ptr< ArgumentParserState > state) {
	possible_states[state->get_name()] = state;
}

void ArgumentParser::set_state(std::string const& state_name) {
	state = possible_states[state_name];
}

void ArgumentParser::set_failure_state(std::string const& state_name) {
	failure_state = possible_states[state_name];
}

void ArgumentParser::execute() {
	try {
		for (int i = 1; i < argc; i++) {
			state->process_token(std::string(argv[i]));
		}
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		set_state(failure_state->get_name());
	}
	state->terminate();
}