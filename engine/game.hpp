#pragma once
#include "../engine/drawer.hpp"
#include <map>

class Game {
  public:
	Drawer d;
	Game() {
		d.printCenter({"Snake Game", "Press Any Key to Start"});
		getch();
		clear();
	}
	~Game() { getch(); }

	void adjustMapSize() {
		while (true) {
			auto hint = mkLines({"[Arrow/Home/PGUP/PGDN/End/(F)123456789] Adjust Map Size", "[Enter] Start"});

			d.drawWall(hint.size() + 1, 0, false);
			d.print(hint, 0, 0);

			map<int, VoidFn> keyMap = {
				{KEY_DOWN, [&] {if (d.mapL< d.maxMapL) d.mapL++; }},
				{KEY_UP, [&] {if (d.mapL > d.minMapL)d.mapL--; }},
				{KEY_RIGHT, [&] {if (d.mapW < d.maxMapW)d.mapW++; }},
				{KEY_LEFT, [&] {if (d.mapW > d.minMapW)d.mapW--; }},
				{KEY_PPAGE, [&] { d.mapL = d.minMapL; }},
				{KEY_NPAGE, [&] { d.mapL = d.maxMapL; }},
				{KEY_HOME, [&] { d.mapW = d.minMapW; }},
				{KEY_END, [&] { d.mapW = d.maxMapW; }},
			};

			// trap
			// main enter : '\n'
			// numeric keypad enter : KEY_ENTER
			int key = getch();
			if (keyMap.contains(key))
				keyMap[key]();
			else if (key == '\n' || key == KEY_ENTER)
				break;
			else if ('1' <= key && key <= '9')
				d.mapL = (key - '1') * (d.maxMapL - d.minMapL) / 8 + d.minMapL;
			else if (KEY_F(1) <= key && key <= KEY_F(9))
				d.mapW = (key - KEY_F(1)) * (d.maxMapW - d.minMapW) / 8 + d.minMapW;
		}
	}
};