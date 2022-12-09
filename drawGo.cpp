#include "graGo.h"

void drawBoard(struct game_state_values curr_state) {
	textcolor(board.color);
	textbackground(console.background_color);
	gotoxy(board.x_start, board.y_start);
	for (int row = 1; row <= board.size; row++) {
		for (int col = 1; col <= board.size*2-1; col++) {
			putCorrectCharOnBoard(row, col, curr_state);
		}
		gotoxy(board.x_start, board.y_start + row);
	}
	textcolor(CURSOR_COLOR_NORMAL);
}

void restoreChar(int x, int y, struct game_state_values curr_state) {
	textcolor(board.color);
	textbackground(console.background_color);
	gotoxy(x, y);
	int col = x - board.x_start + 1;
	int row = y - 4;
	putCorrectCharOnBoard(row, col, curr_state);
	textcolor(CURSOR_COLOR_NORMAL);
}

void print_position(int x, int y) {
	char coord[5] = {};
	const char position_text[] = "Pozycja: ";
	textcolor(TEXT_COLOR);
	textbackground(console.background_color);
	gotoxy(board.x_start, board.y_start - 2);
	x = (x - board.x_start + 2) / 2;

	y -= 4;

	cputs(position_text);
	intToString(x, coord);
	cputs(coord);
	cputs(", ");
	intToString(y, coord);
	cputs(coord);
	putch(' ');
	textcolor(CURSOR_COLOR_NORMAL);
}

void printLegend() {
	int y_offset = 2;
	textcolor(TEXT_COLOR);
	textbackground(console.background_color);
	gotoxy(legend.x_start, legend.y_start);
	cputs("== LEGENDA ==");

	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("Michal Tarnowski, 193324");
	y_offset++;
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("strzalki: -- poruszanie");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("q: --------- zamknij program");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("n: --------- nowa gra");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("enter: ----- potwierdz");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("esc: ------- anuluj");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("i: --------- poloz kamien");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("s: --------- zapisz");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("l: --------- wczytaj");
	/*gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("f: --------- zakoncz gre");*/
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	cputs("o: --------- opcje");

	y_offset++;
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	textcolor(WHITE);
	putch(STONE_CHAR);
	textcolor(TEXT_COLOR);
	cputs(" ---------- Gracz 1");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	textcolor(BLACK);
	putch(STONE_CHAR);
	textcolor(TEXT_COLOR);
	cputs(" ---------- Gracz 2");

	y_offset++;
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	textcolor(CURSOR_COLOR_NORMAL);
	putch(STONE_CHAR);
	textcolor(TEXT_COLOR);
	cputs(" ---------- Kursor");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	textcolor(CURSOR_COLOR_ACTIVE);
	putch(STONE_CHAR);
	textcolor(TEXT_COLOR);
	cputs(" ---------- Potwierdz / wroc");
	gotoxy(legend.x_start, legend.y_start + y_offset++);
	textcolor(CURSOR_ON_STONE);
	putch(STONE_CHAR);
	textcolor(TEXT_COLOR);
	cputs(" ---------- Na kamieniu");

	y_offset++;

}

void printPoints(struct game_state_values curr_state, struct GameSettings curr_g_opt) {
	int y_offset = 0;
	char buff[4] = {};
	textcolor(TEXT_COLOR);
	textbackground(console.background_color);
	gotoxy(board.x_start + 15, board.y_start + board.size + 1);
	cputs("Punkty:  ");
	y_offset++;
	textcolor(WHITE);
	putch(STONE_CHAR);
	putch(SPACE);
	textcolor(TEXT_COLOR);
	intToString(curr_state.points_player_one, buff);
	cputs(buff);
	if (curr_g_opt.handicup == 1) {
		cputs(".5");
	}
	cputs("  ");
	textcolor(BLACK);
	putch(STONE_CHAR);
	putch(SPACE);
	textcolor(TEXT_COLOR);
	intToString(curr_state.points_player_two, buff);
	cputs(buff);
}

void putCorrectCharOnBoard(int row, int col, struct game_state_values curr_state) {
	if (col % 2 == 1) {
		switch (curr_state.board[row - 1][(col+1)/2 - 1]) {
		case EMPTY:
			textcolor(board.color);
			putBoardChar(row, col);
			break;
		case STONE_P1:
			textcolor(WHITE);
			putch(STONE_CHAR);
			break;
		case STONE_P2:
			textcolor(BLACK);
			putch(STONE_CHAR);
			break;
		}
	}
	else {
		textcolor(board.color);
		putBoardChar(row, col);
	}
}

void backgroundColor(int new_color) {
	console.background_color = new_color;
	textbackground(console.background_color);
	gotoxy(1, 1);
	for (int row = 1; row <= console.height; row++) {
		for (int col = 1; col <= console.width; col++) {
			putch(' ');
		}
		gotoxy(1, row + 1);
	}
	gotoxy(1, 1);
}

void drawCursor(int x, int y, int cursor_color) {
	gotoxy(x, y);
	textcolor(cursor_color);
	textbackground(console.background_color);
	putch(CURSOR_CHAR);
}

void placeStone(int x, int y, int turn) {
	gotoxy(x, y);
	textcolor(turn == PLAYER_ONE ? WHITE : BLACK);
	textbackground(console.background_color);
	putch(STONE_CHAR);
}

void putBoardChar(int row, int col) {
	if (col == board.size * 2 - 1) {
		if (row == 1) putch(TOP_RIGHT_CORNER);
		else if (row == board.size) putch(BOTTOM_RIGHT_CORNER);
		else putch(RIGHT_BORDER);
	}
	else if (row == 1) {
		if (col == 1) putch(TOP_LEFT_CORNER);
		else if (col % 2) putch(TOP_BORDER);
		else putch(LINE);
	}
	else if (row == board.size) {
		if (col == 1) putch(BOTTOM_LEFT_CORNER);
		else if (col % 2) putch(BOTTOM_BORDER);
		else putch(LINE);
	}
	else if (col == 1) putch(LEFT_BORDER);
	else if (col % 2) putch(CROSS);
	else putch(LINE);
}

void printWhosTurnIsIt(struct game_state_values curr_state) {
	textcolor(TEXT_COLOR);
	textbackground(console.background_color);
	gotoxy(board.x_start, board.y_start + board.size + 1);
	cputs("Tura: ");
	curr_state.turn == PLAYER_ONE ? textcolor(WHITE) : textcolor(BLACK);
	putch(STONE_CHAR);
}

void newGameAlert() {
	int y_offset = 0;
	gotoxy(board.x_start, y_offset++);
	textcolor(ALERT_COLOR);
	textbackground(console.background_color);
	gotoxy(board.x_start, board.y_start + board.size + y_offset++);
	cputs("Za chwile rozpoczniesz nowa gre.            ");
	gotoxy(board.x_start, board.y_start + board.size + y_offset++);
	cputs("Wszystkie niezapisane dane zostana utracone.");
	gotoxy(board.x_start, board.y_start + board.size + y_offset++);
	cputs("Kontynuowac? TAK [ENTER] / NIE [ESCAPE]");
}

void gameAlert(const char message[]) {
	textcolor(ALERT_COLOR);
	textbackground(console.background_color);
	gotoxy(board.x_start, board.y_start + board.size + 3);
	cputs(message);
}

void clrSuecide() {
	textbackground(console.background_color);
	gotoxy(board.x_start, board.y_start + board.size + 3);
	cputs("                                            ");
}

void clrNewGameAlert() {
	int y_offset = 1;
	textbackground(console.background_color);
	gotoxy(board.x_start, board.y_start + board.size + y_offset++);
	cputs("                                ");
	gotoxy(board.x_start, board.y_start + board.size + y_offset++);
	cputs("                                            ");
	gotoxy(board.x_start, board.y_start + board.size + y_offset++);
	cputs("                                       ");
}

void colorSaveLine(int color) {
	gotoxy(1, console.height);
	textbackground(color);
	for (int i = 0; i < console.width; i++)
		putch(SPACE);
}

void clrPosition() {
	gotoxy(board.x_start, board.y_start - 2);
	for (int i = 0; i < 15; i++)
		putch(SPACE);
}

void lastLineAlert(int background_color, int text_color, const char *message) {
	colorSaveLine(background_color);
	gotoxy(1, console.height);
	textcolor(text_color);
	cputs(message);
}