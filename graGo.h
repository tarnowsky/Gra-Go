#include "conio2.h"
#include <iostream>
using namespace std;

#ifndef GRAGO_H
#define GRAGO_H

#define RIGHT_POS	0
#define LEFT_POS	1

#define RIGHT_POS_X_START	75
#define LEFT_POS_X_START	10
#define Y_START				5

#define BOARD_SIZE 19

#define CONSOLE_WIDTH	120
#define CONSOLE_HEIGHT	30

#define UP_ARROW	0x48
#define DOWN_ARROW	0x50
#define LEFT_ARROW	0x4b
#define RIGHT_ARROW 0x4d
#define ESCAPE		0x1b
#define ENTER		0x0d
#define QUIT		'q'
#define NEW_GAME	'n'
#define INSERT_TILE	'i'
#define SAVE_GAME	's'
#define LOAD_GAME	'l'
#define END_GAME	'f'
#define HENDICAP	'h'
#define CLSC_GAME	'c'
#define SETTINGS	'o'
#define ONE			0x31
#define TWO			0x32
#define THREE		0x33
#define FOUR		0x34
#define BACKSPACE	0x08
#define SPACE		0x20

#define SPECIAL_CHARACTER 0

#define PRESSED		1
#define NOT_PRESSED 0

#define BOARD_COLOR			DARKGRAY
#define CURSOR_COLOR_NORMAL	BLUE
#define CURSOR_COLOR_ACTIVE	RED
#define TEXT_COLOR			BLACK
#define ALERT_COLOR			RED

#define PLAYER_ONE 1
#define PLAYER_TWO -1

#define CROSS				197
#define LINE				196
#define TOP_BORDER			194
#define BOTTOM_BORDER		193
#define RIGHT_BORDER		180
#define LEFT_BORDER			195
#define TOP_LEFT_CORNER		218
#define TOP_RIGHT_CORNER	191
#define BOTTOM_RIGHT_CORNER 217
#define BOTTOM_LEFT_CORNER	192

#define STONE_CHAR	254
#define CURSOR_CHAR 254

#define MAX_FILE_NAME 30

static struct GameSettings {
	int boardSize1 = 1;
	int boardSize2 = 0;
	int boardSize3 = 0;
	int boardSize4 = 0;
	int handicup = 0;
	int classic = 1;
	int settings_chosen = 0;
	int save = 0;
} g_opt;

static enum UpdateBoard_actions {
	PLACE_STONE,
	REMOVE_STONE,
	PLACE_CURSOR,
};

static enum BoardElements {
	EMPTY,
	STONE_P1,
	STONE_P2
};

static struct board_opt {
	int size =		BOARD_SIZE;
	int position =	RIGHT_POS;
	int color =		BOARD_COLOR;
	int x_start =	position == RIGHT_POS ? RIGHT_POS_X_START : LEFT_POS_X_START;
	int y_start =	Y_START;
} board;

static struct Console
{
	int width =				CONSOLE_WIDTH;
	int height =			CONSOLE_HEIGHT;
	int background_color =	LIGHTGRAY;
} console;

static struct keyboard_keys {
	int enter =		NOT_PRESSED; // potwierdŸ wybór, zakoñcz turê
	int arrows =	NOT_PRESSED; // poruszanie (góra, dó³, lewo, prawo)
	int q =			NOT_PRESSED; // zamknij program
	int n =			NOT_PRESSED; // nowa gra
	int escape =	NOT_PRESSED; // anuluj obecn¹ akcjê
	int i =			NOT_PRESSED; // po³ó¿ kamieñ na planszy
	int s =			NOT_PRESSED; // zapisz stan gry
	int l =			NOT_PRESSED; // zapisz stan gry
	int f =			NOT_PRESSED; // zakoñcz grê
	int h =			NOT_PRESSED; // gra z handicapem
	int c =			NOT_PRESSED; // gra klasyczne
	int o =			NOT_PRESSED; // opcje
	int one =		NOT_PRESSED; // opcja 1
	int two =		NOT_PRESSED; // opcja 2
	int three =		NOT_PRESSED; // opcja 3
	int four =		NOT_PRESSED; // opcja 4
} keyboard;

static struct game_state_values {
	int x =										1;
	int y =										1;
	int points_player_one =						0;
	int points_player_two =						0;
	int turn =									PLAYER_ONE;
	int board[BOARD_SIZE][BOARD_SIZE] =			{0};
	int ko_coords[2] =							{-1,-1};
	int suecide =								0;

} game_state;

static struct Legend {
	int x_start = board.position == RIGHT_POS ? LEFT_POS_X_START : RIGHT_POS_X_START - 15;
	int y_start = Y_START - 1;
} legend;



// DO POPRAWY
static struct Saves { 
	int alert_to_clear = 0;
} saves;

// draw board on chosen console side
void drawBoard(struct game_state_values curr_state);
void restoreChar(int x, int y, struct game_state_values curr_state);
void game(struct GameSettings g_opt);
void new_coord(char x_or_y);
void print_position(int x, int y);
void intToString(int num, char buff[]);
struct keyboard_keys keyboard_handle(void);
void new_game(struct GameSettings g_opt);
void printLegend(void);
void putBoardChar(int row, int col);
void backgroundColor(int new_color);
void drawCursor(int x, int y, int cursor_color);
void confirm(void);
void placeStone(int x, int y, int turn);
void changeTurn(void);
void updateBoard(int x, int y, UpdateBoard_actions action, bool is_position);
void putCorrectCharOnBoard(int row, int col, struct game_state_values curr_state);
int XYToBoardIndex(int x_y, char x_or_y);
bool stoneCanBePlaced(int x, int y);
void printWhosTurnIsIt(struct game_state_values curr_state);
void newGameAlert(void);
void clrBoard(void);
void clrNewGameAlert(void);
struct keyboard_keys getFileName(char file_name[30], struct keyboard_keys curr_keyboard_state);
void saveGame(char file_name[30]);
void colorSaveLine(int color);
int canBeInFileName(int c);
void backspaceHandle(char file_name[30], int* x_pos, int* file_name_index);
void clrPosition(void);
void loadGame(char file_name[MAX_FILE_NAME], struct game_state_values *curr_value);
void lastLineAlert(int background_color, int text_color, const char* message);
void printPoints(struct game_state_values curr_state, struct GameSettings curr_g_opt);
bool moveCanKill(
	int x,
	int y,
	struct game_state_values curr_state,
	struct board_opt curr_board,
	int possible_kills[4][3]);
bool moveKills(
	int x,
	int y,
	struct game_state_values curr_state,
	struct board_opt curr_board,
	int surrounded[BOARD_SIZE * BOARD_SIZE / 2][2],
	int possible_kills[4][3]);
void clrSurrounded(int surrounded[(BOARD_SIZE * BOARD_SIZE) / 2][2]);
void suecideAlert(void);
void clrSuecide(void);
struct GameSettings chooseGameSettings(struct GameSettings g_opt);
void playHendicap(struct game_state_values* curr_value);;
#endif 