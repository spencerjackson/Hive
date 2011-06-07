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


#include "argumentparserstate.h"

ArgumentParserState::ArgumentParserState(std::string&& name, std::shared_ptr< ArgumentParser > parser, std::function<void (ArgumentParser&, ArgumentParserState&)> terminate_function)
: name(std::move(name)), parser(parser), terminate_function(terminate_function), remaining_tokens_to_feed(0) {}

ArgumentParserState::~ArgumentParserState() {}

std::string ArgumentParserState::get_name() const {
	return name;
}

void ArgumentParserState::add_argument(std::shared_ptr<Argument> argument) {
	for (std::string token : argument->get_tokens()) {
		arguments[token] = argument;
	}
	argument->register_state(this);
}

void ArgumentParserState::process_token(std::string&& token) {
	if (remaining_tokens_to_feed == 0) {
		//Obtain correct argument
		to_be_fed = arguments[token];
		remaining_tokens_to_feed = to_be_fed->get_argument_count();
	} else tokens_to_feed.push_back(token);

	if (remaining_tokens_to_feed == tokens_to_feed.size()) (*to_be_fed)(*parser, std::move(tokens_to_feed));
}

void ArgumentParserState::terminate() {
	terminate_function(*parser, *this);
}

