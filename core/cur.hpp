#pragma once
#include "../core/align.hpp"
#include <functional>
using VoidFn = std::function<void()>;

class Cur {
  private:
	bool alwaysFlush = true;
	void putColor(int fg, int bg, char c) {
		int colorPair = 8 * fg + bg + 1;
		attron(COLOR_PAIR(colorPair));
		addch(c);
		attroff(COLOR_PAIR(colorPair));
	}

  public:
	Cur() {
		initscr();
		start_color();
		keypad(stdscr, true);
		cbreak();
		noecho();
		curs_set(0);

		for (int fg = 0; fg < 8; fg++)
			for (int bg = 0; bg < 8; bg++)
				init_pair(8 * fg + bg + 1, fg, bg); // pair cannot be 0
	}
	~Cur() { endwin(); }

	inline void flush() {
		if (alwaysFlush)
			refresh();
	}

	void print(ValLines lines,
			   int y = Align::DEFAULT,
			   int x = Align::DEFAULT,
			   Pair2Int rangeY = pair(0, LINES - 1),
			   Pair2Int rangeX = pair(0, COLS - 1)) {

		auto yxs = Align(lines, y, x, rangeY, rangeX).yx;

		for (int i = 0; i < yxs.size(); i++) {
			int curY = yxs[i].first;
			int curXStart = yxs[i].second;
			move(curY, curXStart);

			auto line = lines[i];
			int m = line.str.size();

			for (int j = 0; j < m; j++) {
				char c = line.str[j];
				auto color = line.colors[j];

				if (c < ' ')
					putColor(color.fg, (int)c, ' ');
				else
					putColor(color.fg, color.bg, c);
			}
		}

		flush();
	}

	inline void print(ValLine line,
					  int y = Align::DEFAULT,
					  int x = Align::DEFAULT,
					  Pair2Int rangeY = pair(0, LINES - 1),
					  Pair2Int rangeX = pair(0, COLS - 1)) {

		print(Lines{line}, y, x, rangeY, rangeX);
	}

	inline void print(ValStr pattern,
					  int y = Align::DEFAULT,
					  int x = Align::DEFAULT,
					  Pair2Int rangeY = pair(0, LINES - 1),
					  Pair2Int rangeX = pair(0, COLS - 1)) {

		print(Line(pattern), y, x, rangeY, rangeX);
	}

	inline void print(StrInitList args,
					  int y = Align::DEFAULT,
					  int x = Align::DEFAULT,
					  Pair2Int rangeY = pair(0, LINES - 1),
					  Pair2Int rangeX = pair(0, COLS - 1)) {

		print(mkLines(args), y, x, rangeY, rangeX);
	}

	void printCenter(ValLines lines, bool newCanva = true) {
		if (newCanva)
			clear();
		print(lines, Align::CENTER, Align::CENTER);
	}

	inline void printCenter(ValLine line, bool newCanva = true) {
		printCenter(Lines{line}, newCanva);
	}

	inline void printCenter(ValStr pattern, bool newCanva = true) {
		printCenter(Line(pattern), newCanva);
	}

	inline void printCenter(StrInitList args, bool newCanva = true) {
		printCenter(mkLines(args), newCanva);
	}

	inline void syncPrint(VoidFn fun) {
		// prevent racing condition
		if (alwaysFlush) {
			alwaysFlush = false;
			fun();
			alwaysFlush = true;
			refresh();
		} else
			fun();
	}
};