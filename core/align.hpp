#pragma once
#include "../core/color.hpp"
#include <utility>
using Pair2Int = pair<int, int>;

class Align {
  private:
	inline int mid(int n) { return (n + 1) / 2; } // tricky method as ceil()

  public:
	static const int DEFAULT = -1;
	static const int CENTER = -2;
	static const int END = -3;

	vector<Pair2Int> yx;

	Align(ValLines lines, int y, int x, Pair2Int rangeY, Pair2Int rangeX) {
		if (rangeY.second < 0)
			rangeY.second += LINES; // that's why arg rangeY cannot be const ref

		if (rangeX.second < 0)
			rangeX.second += COLS; // that's why arg rangeX cannot be const ref

		int curY = getcury(stdscr);
		int curX = getcurx(stdscr);

		// n: 有n行
		// i: 第i行
		// m: 該行長度m

		int n = lines.size();
		yx.assign(n, {});

		for (int i = 0; i < n; i++) {
			int m = lines[i].str.length();

			if (y >= 0)
				yx[i].first = y + i;
			else {
				int yMap[3];
				yMap[DEFAULT + 3] = curY + i;
				yMap[CENTER + 3] = mid(rangeY.first + rangeY.second - n) + i;
				yMap[END + 3] = rangeY.second - n + 1 + i;
				yx[i].first = yMap[y + 3];
			}

			if (x >= 0)
				yx[i].second = x;
			else {
				int xMap[3];
				xMap[DEFAULT + 3] = curX;
				xMap[CENTER + 3] = mid(rangeX.first + rangeX.second - m);
				xMap[END + 3] = rangeX.second - m + 1;
				yx[i].second = xMap[x + 3];
			}
		}
	}
};