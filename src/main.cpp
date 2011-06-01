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

#include <list>
#include <string>
#include <memory>
#include <iostream>

/*#include "graph/packagekitinterface.h"
#include "graph/externaldependency.h"
#include "graph/dummyexternaldependencymapper.h"*/

#include "util/l10n/l10n.h"

#include "cli/argumentparser.h"
#include "cli/argumentparserstate.h"
#include "cli/argument.h"
#include "cli/interstateargument.h"
#include "cli/statechangeargument.h"
#include "util/io/directory.h"
#include "graph/nodeparser.h"

void default_state_terminate(ArgumentParser& parser, ArgumentParserState& state);
void default_add_collection(ArgumentParserState*, ArgumentParser&, std::list<std::string>&&);
void default_unknown_argument(ArgumentParserState*, ArgumentParser&, std::string&&);
void help_state_terminate(ArgumentParser& parser, ArgumentParserState& state);
void help_unknown_argument(ArgumentParserState*, ArgumentParser&, std::string&&);
void version_state_terminate(ArgumentParser& parser, ArgumentParserState& state);
void version_unknown_argument(ArgumentParserState*, ArgumentParser&, std::string&&);



int main(int argc, char* argv[]) {
	std::shared_ptr<ArgumentParser> parser{new ArgumentParser{argc, argv}};
	std::shared_ptr<ArgumentParserState> hivestate{new ArgumentParserState{"default", parser, &default_state_terminate, &default_unknown_argument}};
	hivestate->add_argument(std::shared_ptr< Argument > {new InterstateArgument{std::list<std::string>{"-c", "--collection"}, "Path to collection of packages to parser", 1, &default_add_collection}});
	std::shared_ptr<ArgumentParserState> helpstate{new ArgumentParserState{"help", parser, &help_state_terminate, &help_unknown_argument}};
	std::shared_ptr<ArgumentParserState> versionstate{new ArgumentParserState{"version", parser, &version_state_terminate, &version_unknown_argument}};
	hivestate->add_argument(std::shared_ptr< Argument > {new StateChangeArgument{std::list<std::string>{"-h", "--help"}, "Display possible CLI options for this program", helpstate}});
	hivestate->add_argument(std::shared_ptr< Argument > {new StateChangeArgument{std::list<std::string>{"-V", "--version"}, "Display version information for this program", versionstate}});
	parser->add_state(hivestate);
	parser->add_state(versionstate);
	parser->add_state(helpstate);
	parser->set_state("default");
	parser->set_failure_state("help");
	parser->execute();
	return 0;
}

void help_state_terminate(ArgumentParser& parser, ArgumentParserState& state) {
	std::cout << _("Usage: hive [OPTIONS]") << std::endl << _("Options are as follows:") << std::endl;
}

void help_unknown_argument(ArgumentParserState*, ArgumentParser&, std::string&&) {}
void version_unknown_argument(ArgumentParserState*, ArgumentParser&, std::string&&) {}
void default_unknown_argument(ArgumentParserState* state, ArgumentParser& parser, std::string&& token) {
	if (state->config_value_set("robot_definition")) state->set_config_value("robot_definition", token);
}


void default_state_terminate(ArgumentParser& parser, ArgumentParserState& state) {
	hive::NodeParser node_parser;
	try {
		for (std::string &collection : state.get_config_list("collection")) {
			hive::Directory collection_dir(collection);
			node_parser.add_collection(collection_dir);
		}
	} catch(std::exception& e) {
		std::cout << _("No package collections specified.") << std::endl;
	}

	std::cout << _("Default state has concluded.") << std::endl;
}

void version_state_terminate(ArgumentParser& parser, ArgumentParserState& state) {
	std::cout << "Hive 0.1 pre-release" << std::endl;
}

void default_add_collection(ArgumentParserState* state, ArgumentParser& parser, std::list<std::string>&& arguments) {
	state->append_config_list("collection", arguments.front());
	arguments.pop_front();
}