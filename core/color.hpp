#pragma once
#include "../utility/dbg.hpp"
#include <initializer_list>
#include <ncurses.h>

struct Color {
	int fg = COLOR_WHITE;
	int bg = COLOR_BLACK;
};

using ValColor = const Color &;

class Line {
  public:
	string str;
	vector<Color> colors;

	// default constructor
	Line() {}

	Line(int n) {
		str.assign(n, 0);
		colors.assign(n, {});
	}

	Line(ValStr pattern, int times = 1, ValColor color = {}) {
		str = Str::repeat(pattern, times);
		colors.assign(pattern.length() * times, color);
	}
};

using ValLine = const Line &;

using Lines = vector<Line>;
using ValLines = const Lines &;

using StrInitList = std::initializer_list<string>;
Lines mkLines(StrInitList args) {
	Lines lines;
	for (const auto &arg : args)
		lines.push_back(arg);
	return lines;
}