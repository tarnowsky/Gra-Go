#include "graGo.h"

void printSettings(struct GameSettings curr_g_opt);
void printNewSettings(int option, struct GameSettings curr_g_opt);
void switchOffBoardSize(struct GameSettings* curr_g_opt);

struct GameSettings chooseGameSettings(struct GameSettings curr_g_opt) {
	curr_g_opt.save = 0;
	GameSettings temp_g_opt = curr_g_opt;
	printSettings(curr_g_opt);
	
	do {
		keyboard = keyboard_handle();
		if (keyboard.enter == PRESSED) {
			curr_g_opt.save = 1;
			break;
		}
		if (curr_g_opt.settings_chosen == 1 && keyboard.escape == PRESSED) {
			backgroundColor(LIGHTGRAY);
			return temp_g_opt;
		}
		if (keyboard.h == PRESSED) {
			curr_g_opt.handicup = 1;
			curr_g_opt.classic = 0;
			printNewSettings(0, curr_g_opt);
		}
		if (keyboard.c == PRESSED) {
			curr_g_opt.handicup = 0;
			curr_g_opt.classic = 1;
			printNewSettings(0, curr_g_opt);
		}
		if (keyboard.one == PRESSED) {
			switchOffBoardSize(&curr_g_opt);
			curr_g_opt.boardSize1 = 1;
			printNewSettings(1, curr_g_opt);
		}
		if (keyboard.two == PRESSED) {
			switchOffBoardSize(&curr_g_opt);
			curr_g_opt.boardSize2 = 1;
			printNewSettings(2, curr_g_opt);
		}
		if (keyboard.three == PRESSED) {
			switchOffBoardSize(&curr_g_opt);
			curr_g_opt.boardSize3 = 1;
			printNewSettings(3, curr_g_opt);
		}
		if (keyboard.four == PRESSED) {
			switchOffBoardSize(&curr_g_opt);
			curr_g_opt.boardSize4 = 1;
			printNewSettings(4, curr_g_opt);
		}
	} while (keyboard.q != PRESSED);

	backgroundColor(LIGHTGRAY);
	return curr_g_opt;
}

void printSettings(struct GameSettings curr_g_opt) {
	backgroundColor(LIGHTGRAY);
	textcolor(TEXT_COLOR);
	int x = 30;
	int y = 9;
	int y_offset = 2;
	gotoxy(x, y); 
	cputs("== OPCJE GRY ==");//  30, 9
	gotoxy(x, y + y_offset++); 
	curr_g_opt.handicup == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
	cputs("h - gra z handicapem");//  30, 11
	gotoxy(x, y + y_offset++);
	curr_g_opt.classic == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
	cputs("c - gra klasyczna");//  30, 12
	y_offset = 2;
	x = console.width - 50;
	gotoxy(x, y);
	textcolor(TEXT_COLOR);
	cputs("== PLANSZA ==");//  console.width-50, 9
	gotoxy(x, y + y_offset++);
	curr_g_opt.boardSize1 == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
	cputs("1 - 19 x 19");//  console.width-50, 11
	gotoxy(x, y + y_offset++);
	curr_g_opt.boardSize2 == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
	cputs("2 - 13 x 13");//  console.width-50, 12
	gotoxy(x, y + y_offset++);
	curr_g_opt.boardSize3 == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
	cputs("3 - 9 x 9");//  console.width-50, 13
	gotoxy(x, y + y_offset++);
	curr_g_opt.boardSize4 == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
	cputs("4 - wlasne wymiary");//  console.width-50, 14
	x = 45;
	y = 22;
	y_offset = 1;
	gotoxy(x, y);
	cputs("enter - zapisz i rozpocznij nowa gre");
	if (curr_g_opt.settings_chosen == 1) {
		gotoxy(x, y + y_offset++);
		cputs("esc - wroc");
	}
	gotoxy(x, y + y_offset++);
	cputs("q - zamknij program");
}

void printNewSettings(int option, struct GameSettings curr_g_opt) {
	switch (option) {
	case 0:
		gotoxy(30, 11);
		cputs("                   ");
		curr_g_opt.handicup == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
		gotoxy(30, 11);
		cputs("h - gra z handicapem");
		gotoxy(30, 12);
		cputs("                   ");
		curr_g_opt.classic == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
		gotoxy(30, 12);
		cputs("c - gra klasyczna");
		break;
	case 1:
		gotoxy(console.width - 50, 11);
		cputs("           ");
		curr_g_opt.boardSize1 == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
		gotoxy(console.width - 50, 11);
		cputs("1 - 19 x 19");
		break;
	case 2:
		gotoxy(console.width - 50, 12);
		cputs("           ");
		curr_g_opt.boardSize2 == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
		gotoxy(console.width - 50, 12);
		cputs("2 - 13 x 13");
		break;
	case 3:
		gotoxy(console.width - 50, 13);
		cputs("           ");
		curr_g_opt.boardSize3 == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
		gotoxy(console.width - 50, 13);
		cputs("3 - 9 x 9");
		break;
	case 4:
		gotoxy(console.width - 50, 14);
		cputs("           ");
		curr_g_opt.boardSize4 == 1 ? textcolor(RED) : textcolor(TEXT_COLOR);
		gotoxy(console.width - 50, 14);
		cputs("4 - wlasne wymiary");
		break;
	}
}

void switchOffBoardSize(struct GameSettings* curr_g_opt) {
	if (curr_g_opt->boardSize1 == 1) {
		curr_g_opt->boardSize1 = 0;
		printNewSettings(1, *curr_g_opt);
	}
	else if (curr_g_opt->boardSize2 == 1) {
		curr_g_opt->boardSize2 = 0;
		printNewSettings(2, *curr_g_opt);
	}
	else if (curr_g_opt->boardSize3 == 1) {
		curr_g_opt->boardSize3 = 0;
		printNewSettings(3, *curr_g_opt);
	}
	else if (curr_g_opt->boardSize4 == 1) {
		curr_g_opt->boardSize4 = 0;
		printNewSettings(4, *curr_g_opt);
	}

}
