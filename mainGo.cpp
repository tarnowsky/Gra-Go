#define _CRT_SECURE_NO_WARNINGS
#include"graGo.h"

int main() {
	_setcursortype(_NOCURSOR);
	settitle("Gra GO");
	backgroundColor(LIGHTGRAY);
	game();
	_setcursortype(_NORMALCURSOR);
	return 0;
}
