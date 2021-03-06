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


#ifndef ARGUMENTPARSERSTATE_H
#define ARGUMENTPARSERSTATE_H

#include <list>
#include <functional>
#include <string>
#include <memory>
#include <unordered_map>

#include "argument.h"

class ArgumentParserState {
public:
	ArgumentParserState(std::string&& name, std::shared_ptr<ArgumentParser> parser, std::function<void (ArgumentParser&, ArgumentParserState&)> terminate_function,
		std::function<void (ArgumentParserState*, ArgumentParser&, std::string&&) > unrecognized_token);
	virtual ~ArgumentParserState();

	std::string get_name() const;

	void add_argument(std::shared_ptr< Argument > argument);
	void process_token(std::string&& token);
	virtual void terminate();

	void append_config_list(std::string const& key, std::string const& value);
	std::list<std::string> get_config_list(std::string const& key) const;
	void set_config_value(std::string const& key, std::string const& value);
	std::string get_config_value(std::string const& key) const;
	bool config_value_set(std::string const& key) const;
protected:
	std::string name;
	std::shared_ptr<ArgumentParser> parser;
	std::function<void (ArgumentParser&, ArgumentParserState&)> terminate_function;
	std::function<void (ArgumentParserState*, ArgumentParser&, std::string&&) > unrecognized_token;
	std::unordered_map< std::string, std::shared_ptr<Argument> > arguments;

	std::shared_ptr<Argument> to_be_fed;
	int remaining_tokens_to_feed;
	std::list<std::string> tokens_to_feed;

	std::unordered_map< std::string, std::list<std::string> > list_map;
	std::unordered_map< std::string, std::string> map;
};

#endif // ARGUEMENTPARSERSTATE_H
