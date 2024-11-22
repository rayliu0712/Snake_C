#pragma once
#include "cur.hpp"
#include <chrono>
#include <thread>

class Drawer : public Cur {
  public:
	const int minMapL = 5, minMapW = 10;
	const int maxMapL = LINES - 5, maxMapW = COLS - 2;
	int mapL = minMapL, mapW = minMapW;

	inline void sleep(int millis) {
		this_thread::sleep_for(chrono::milliseconds(millis));
	}

	void drawWall(int y, int x, bool gameHasStart) {
		string block = Str::ascii(COLOR_RED);
		auto floor = Line(block, mapW + 2);
		auto wall = Line(block + Str::repeat(" ", mapW) + block);

		Lines lines(mapL + 2);
		lines[0] = lines[mapL + 1] = floor;
		for (int i = 1; i <= mapL; i++)
			lines[i] = wall;

		if (gameHasStart)
			print(lines, Align::CENTER, Align::CENTER);
		else
			syncPrint([&] {
				clear();
				print(lines, y, Align::CENTER, {}, {x, x + mapW + 1});
				auto size = Line(format("{} x {}", mapL, mapW));
				print(size, Align::CENTER, Align::CENTER, {y, y + mapL + 1}, {x, x + mapW + 1});
			});
	}

	void drawCurtain(int i, bool isIn) {
		auto line = Line(Str::ascii(COLOR_CYAN), COLS);

		auto lines = Lines(isIn ? i + 1 : i, line);
		syncPrint([&] {
			print(lines, 0, 0);
			if (i >= LINES / 2)
				print(Line("Snake Game", 1, {COLOR_WHITE, COLOR_CYAN}), i - LINES / 2, Align::CENTER);
		});
		sleep(100 - i * 2);
	}

	void adjustMapToGameTransition() {
		for (int i = 0; i < LINES; i++)
			drawCurtain(i, true);

		sleep(1000);

		for (int i = LINES - 1; i >= 0; i--)
			syncPrint([&] {
				clear();
				drawWall(0, 0, true);
				drawCurtain(i, false);
			});
	}
};