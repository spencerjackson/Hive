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


#ifndef L10N_H
#define L10N_H

#include <string>
#include <boost/format.hpp>
#include <libintl.h>

#define _(STRING, ...) l10n::obtain(gettext(STRING), ##__VA_ARGS__)

class l10n {
public:
	l10n() = delete;
	l10n(const l10n& other) = delete;
	~l10n() = delete;
	l10n& operator=(const l10n& other) = delete;
	bool operator==(const l10n& other) const = delete;

	static const char* obtain(const char* string) {return string;}

	static const char* obtain(boost::format formatter) {
		return formatter.str().c_str();
	}

	template<typename... Args>
	static const char* obtain(const char* string, Args... args) {
		boost::format formatter{std::string{string}};
		return obtain(formatter, args...);
	}

	template<typename T, typename... Args>
	static const char* obtain(boost::format formatter, T value, Args... args) {
		formatter % value;
		return obtain(formatter, args...);
	}

};

#endif // L10N_H
