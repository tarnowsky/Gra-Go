#define _CRT_SECURE_NO_WARNINGS
#include"graGo.h"

int main() {
	_setcursortype(_NOCURSOR);
	settitle("Michal, Tarnowski, 193324");
	g_opt = chooseGameSettings(g_opt);
	game(g_opt);
	_setcursortype(_NORMALCURSOR);
	return 0;
}
