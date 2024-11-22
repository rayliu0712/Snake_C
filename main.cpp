// game.hpp
// drawer.hpp
// curses.hpp
// align.hpp
// color.hpp
// dbg.hpp
// str.hpp

#include "game.hpp"

int main() {
	try {
		Game game;
		game.adjustMapSize();
		game.d.adjustMapToGameTransition();

	} catch (const char *msg) {
		dbg << msg << ln;
	} catch (ValStr msg) {
		dbg << msg << ln;
	}
}