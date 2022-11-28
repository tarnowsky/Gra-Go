#include "conio2.h"

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
#define ONE			0x31
#define TWO			0x32
#define THREE		0x33
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
} keyboard;

static struct game_state_values {
	int x =										1;
	int y =										1;
	int points_player_one =						0;
	int points_player_two =						0;
	int turn =									PLAYER_ONE;
	int board[BOARD_SIZE][BOARD_SIZE] =			{};
	int board_for_ko[BOARD_SIZE][BOARD_SIZE] =	{};
} game_state;

static struct Legend {
	int x_start = board.position == RIGHT_POS ? LEFT_POS_X_START : RIGHT_POS_X_START - 15;
	int y_start = Y_START - 1;
} legend;

// DO POPRAWY
static struct Saves { 
	int alert_to_clear = 0;
} saves;

static struct Breaths {
	int white = 4;
	int black = 4;
	int was_reduced_in_curr_turn = 0;
} breaths[BOARD_SIZE][BOARD_SIZE];

// draw board on chosen console side
void drawBoard(struct game_state_values curr_state);
void restoreChar(int x, int y, struct game_state_values curr_state);
void game(void);
void new_coord(char x_or_y);
void print_position(int x, int y);
void intToString(int num, char buff[]);
void keyboard_handle(void);
void new_game(void);
void printLegend(void);
void putBoardChar(int row, int col);
void backgroundColor(int new_color);
void drawCursor(int x, int y, int cursor_color);
void confirm(void);
void placeStone(int x, int y, int turn);
void changeTurn(void);
void updateBoard(int x, int y, UpdateBoard_actions action);
void putCorrectCharOnBoard(int row, int col, struct game_state_values curr_state);
int XYToBoardIndex(char x_or_y);
int stoneCanBePlaced(int x, int y);
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
void reduceBreaths(struct Breaths curr_breaths, int x_pos, int y_pos);
void correctStartBreaths(struct Breaths start_breaths[BOARD_SIZE][BOARD_SIZE]);
#endif 