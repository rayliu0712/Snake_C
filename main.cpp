#include "engine/game.hpp"

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