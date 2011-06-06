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


#include "statechangeargument.h"
#include "argumentparser.h"
#include "argumentparserstate.h"

StateChangeArgument::StateChangeArgument(std::list<std::string>&& possible_tokens, std::string const& description, std::shared_ptr<ArgumentParserState> state)
: Argument(std::move(possible_tokens), description), state(state) {}

StateChangeArgument::~StateChangeArgument() {}

unsigned int StateChangeArgument::get_argument_count() const {
	return 0;
}

void StateChangeArgument::operator()(ArgumentParser& parser, std::list<std::string>&& arguments) {
	parser.set_state(state->get_name());
}
