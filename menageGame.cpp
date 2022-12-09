#include "graGo.h"

void game(struct GameSettings curr_g_opt) {
	curr_g_opt.settings_chosen = 1;
	if (keyboard.q != PRESSED) {
		printLegend();
		new_game(curr_g_opt);
		do {
			// obsluz zamkniecie programu
			if (keyboard.q == PRESSED) break;
			// zaaktualizuj punkty
			printPoints(game_state, curr_g_opt);
			// zaaktualizuj ture
			printWhosTurnIsIt(game_state);
			// obsluz polozenie kursora na planszy
			new_coord('x');
			new_coord('y');
			// wypisz pozycje na planszy
			print_position(game_state.x, game_state.y);
			// narysuj kursor
			if (game_state.board[XYToBoardIndex(game_state.y, 'y')][XYToBoardIndex(game_state.x, 'x')] != EMPTY) {
				drawCursor(game_state.x, game_state.y, CURSOR_ON_STONE);
			}
			else drawCursor(game_state.x, game_state.y, CURSOR_COLOR_NORMAL);
			// czekaj na wejscie
			keyboard = keyboard_handle();
			if (keyboard.n == PRESSED) {
				newGameAlert();
				confirm();
				if (keyboard.enter == PRESSED) {
					new_game(curr_g_opt);
				}
				if (curr_g_opt.handicup != 1) clrNewGameAlert();
			}
			if (keyboard.i == PRESSED) {
				if (stoneCanBePlaced(game_state.x, game_state.y)) {
					game_state.ko_coords[0] = -1;
					game_state.ko_coords[1] = -1;
					drawCursor(game_state.x, game_state.y, CURSOR_COLOR_ACTIVE);
					confirm();
					if (keyboard.enter == PRESSED) {
						placeStone(game_state.x, game_state.y, game_state.turn);
						updateBoard(game_state.x, game_state.y, PLACE_STONE, true);

						int possible_kills[4][3] = {
							{-1, -1, 0}, // góra
							{-1, -1, 0}, // prawo
							{-1, -1, 0}, // dó³
							{-1, -1, 0}, // lewo
						};

						int x = XYToBoardIndex(game_state.x, 'x');
						int y = XYToBoardIndex(game_state.y, 'y');
						
						if (moveCanKill(x, y, game_state, board, possible_kills)) {
							int points = 0;
							int surrounded[(BOARD_SIZE * BOARD_SIZE) / 2][2];
							for (int i = 0; i < 4; i++) {
								if (possible_kills[i][0] == -1 || possible_kills[i][2] == 1) continue;
								clrSurrounded(surrounded);
								if (moveKills(possible_kills[i][0], possible_kills[i][1], game_state, board, surrounded, possible_kills)) {
									for (int j = 0; surrounded[j][0] != -1; j++) {
										updateBoard(surrounded[j][0], surrounded[j][1], REMOVE_STONE, false);
										restoreChar(surrounded[j][0] * 2 + board.x_start, surrounded[j][1] + board.y_start, game_state);
										points++;
									}
									if (points == 1) {
										game_state.ko_coords[0] = surrounded[0][0];
										game_state.ko_coords[1] = surrounded[0][1];
									}
								}
							}

							game_state.turn == PLAYER_ONE ? game_state.points_player_one += points : game_state.points_player_two += points;
						}
						changeTurn();
					}
				}
			} 
			if (keyboard.s == PRESSED) {
				char file_name_save[MAX_FILE_NAME] = {};
				keyboard = getFileName(file_name_save, keyboard);
				if (keyboard.escape != PRESSED) {
					saveGame(file_name_save);
				}
			}
			if (keyboard.l == PRESSED) {
				char file_name_load[MAX_FILE_NAME] = {};
				keyboard = getFileName(file_name_load, keyboard);
				if (keyboard.escape != PRESSED) {
					loadGame(file_name_load, &game_state);
					drawBoard(game_state);
				}
			}
			if (keyboard.o == PRESSED) {
				curr_g_opt = chooseGameSettings(curr_g_opt);
				if (keyboard.q == PRESSED) break;
				if (curr_g_opt.save) {
					printLegend();
					new_game(curr_g_opt);
				}
				else {
					backgroundColor(console.background_color);
					printLegend();
					printPoints(game_state, curr_g_opt);
					drawBoard(game_state);
				}
			}
		} while (keyboard.q != PRESSED);
	}
	gotoxy(1, 28);
	textcolor(TEXT_COLOR);
}

void new_coord(char x_or_y) {
	if (x_or_y == 'y') {
		if (game_state.y < board.y_start) game_state.y = board.y_start;
		else if (game_state.y >= board.y_start + board.size) game_state.y = board.y_start + board.size - 1;
	}
	else if (x_or_y == 'x') {
		if (game_state.x < board.x_start) game_state.x = board.x_start;
		else if (game_state.x >= board.x_start + board.size * 2 - 1) game_state.x = board.x_start + board.size * 2 - 2;
	}
}

void intToString(int num, char buff[]) {
	int num_len = 0;
	do {
		buff[num_len++] = (num % 10) + '0';
		num /= 10;
	} while (num != 0);

	for (int i = 0; i < (num_len / 2); i++) {
		char temp = buff[num_len - 1 - i];
		buff[num_len - 1 - i] = buff[i];
		buff[i] = temp;
	}

	buff[num_len] = '\0';
}

struct keyboard_keys keyboard_handle() {
	int pressed_key;
	keyboard = { NOT_PRESSED };
	pressed_key = getch();
	if (saves.alert_to_clear) {
		colorSaveLine(console.background_color);
		saves.alert_to_clear = 0;
	}
	if (game_state.alert) {
		clrSuecide();
		game_state.alert = 0;
	}

	if (pressed_key == SPECIAL_CHARACTER) {
		pressed_key = getch();
		if (pressed_key == UP_ARROW || pressed_key == DOWN_ARROW
			|| pressed_key == RIGHT_ARROW || pressed_key == LEFT_ARROW) {
			restoreChar(game_state.x, game_state.y, game_state);
			switch (pressed_key) {
			case UP_ARROW:
				game_state.y--;
				break;
			case DOWN_ARROW:
				game_state.y++;
				break;
			case RIGHT_ARROW:
				game_state.x += 2;
				break;
			case LEFT_ARROW:
				game_state.x -= 2;
				break;
			default:
				break;
			}
			keyboard.arrows = PRESSED;
		}
	}
	switch (pressed_key) {
	case QUIT:
		keyboard.q = PRESSED;
		break;
	case NEW_GAME:
		keyboard.n = PRESSED;
		break;
	case SETTINGS:
		keyboard.o = PRESSED;
		break;
	case ONE:
		keyboard.one = PRESSED;
		break;
	case TWO:
		keyboard.two = PRESSED;
		break;
	case THREE:
		keyboard.three = PRESSED;
		break;
	case FOUR:
		keyboard.four = PRESSED;
		break;
	case HENDICAP:
		keyboard.h = PRESSED;
		break;
	case CLSC_GAME:
		keyboard.c = PRESSED;
		break;
	case END_GAME:
		keyboard.f = PRESSED;
		break;
	case INSERT_TILE:
		keyboard.i = PRESSED;
		break;
	case SAVE_GAME:
		keyboard.s = PRESSED;
		break;
	case LOAD_GAME:
		keyboard.l = PRESSED;
		break;
	case ENTER:
		keyboard.enter = PRESSED;
		break;
	case ESCAPE:
		keyboard.escape = PRESSED;
		break;
	default:
		break;
	}
	return keyboard;
}

void new_game(struct GameSettings curr_g_opt) {
	clrPosition();
	clrBoard();
	drawBoard(game_state);
	if (curr_g_opt.handicup == 1) {
		playHendicap(&game_state);
	}
	game_state.x = board.x_start;
	game_state.y = board.y_start;
	game_state.points_player_one = 0;
	game_state.points_player_two = 0;
	game_state.turn = PLAYER_ONE;
}

void confirm() {
	int pressed_key = getch();
	while (pressed_key != ENTER && pressed_key != ESCAPE && pressed_key != QUIT) pressed_key = getch();
	switch (pressed_key)
	{
	case ENTER:
		keyboard.enter = PRESSED;
		break;
	case ESCAPE:
		keyboard.escape = PRESSED;
		break;
	case QUIT:
		keyboard.q = PRESSED;
		break;
	default:
		break;
	}
}

void changeTurn() {
	game_state.turn = (game_state.turn == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
}

void updateBoard(int x, int y, UpdateBoard_actions action, bool is_position) {
	if (is_position) {
		x = XYToBoardIndex(x, 'x');
		y = XYToBoardIndex(y, 'y');
	}
	switch (action) {
	case PLACE_STONE:
		game_state.board[y][x] = game_state.turn == PLAYER_ONE ? STONE_P1 : STONE_P2;
		break;
	case REMOVE_STONE:
		game_state.board[y][x] = EMPTY;
		break;
	}
}

int XYToBoardIndex(int x_y, char x_or_y) {
	switch (x_or_y) {
	case 'x':
		return (x_y - board.x_start) / 2;
	case 'y':
		return (x_y - board.y_start);
	default:
		return -1;
	}
}

bool stoneCanBePlaced(int x, int y) {
	x = XYToBoardIndex(x, 'x');
	y = XYToBoardIndex(y, 'y');

	if (game_state.board[y][x] != EMPTY) {
		return false;
	}

	int possible_kills[4][3] = {
		{-1, -1, 0}, // góra
		{-1, -1, 0}, // prawo
		{-1, -1, 0}, // dó³
		{-1, -1, 0}, // lewo
	};

	int surrounded[(BOARD_SIZE * BOARD_SIZE) / 2][2];
	bool can_be = true;
	bool move_kills = false;
	game_state.board[y][x] = (game_state.turn == PLAYER_ONE ? STONE_P1 : STONE_P2);

	if (moveCanKill(x, y, game_state, board, possible_kills)) {
		int points = 0;
		for (int i = 0; i < 4; i++) {
			if (possible_kills[i][0] == -1 || possible_kills[i][2] == 1) continue;
			clrSurrounded(surrounded);
			if (moveKills(possible_kills[i][0], possible_kills[i][1], game_state, board, surrounded, possible_kills)) {
				move_kills = true;
				if (x == game_state.ko_coords[0] && y == game_state.ko_coords[1]) {
					gameAlert("Ruch niedozwolony zgodnie z zasada Ko.");
					game_state.alert = 1;
					can_be = false;
				}
				else can_be = true;
				
			}
		}
	}
	if (!move_kills) {
		clrSurrounded(surrounded);
		game_state.turn *= -1;
		if (moveKills(x, y, game_state, board, surrounded, possible_kills)) {
			gameAlert("Ruch niedozwolony. Samobojstwo.");
			game_state.alert = 1;
			can_be = false;
		}
		game_state.turn *= -1;
	}

	game_state.board[y][x] = EMPTY;
	
	if (can_be) {
		return true;
	}
	return false;
}

void clrBoard() {
	for (int row = 0; row < board.size; row++)
		for (int col = 0; col < board.size; col++) {	
			game_state.board[row][col] =		EMPTY;
		}
}

struct keyboard_keys getFileName(char file_name[MAX_FILE_NAME], struct keyboard_keys curr_kayboard_state) {
	colorSaveLine(CYAN);
	textcolor(WHITE);
	gotoxy(1, console.height);
	_setcursortype(_NORMALCURSOR);
	int c;
	int i = 0, x = 1;
	while ((c = getch()) != ENTER && c != ESCAPE) {
		if (c == UP_ARROW || c == DOWN_ARROW || c == RIGHT_ARROW || c == LEFT_ARROW) continue;
		if ((c == SPACE || c == BACKSPACE) && file_name[0] == '\0') continue;
		if (c == BACKSPACE && i > 0) {
			backspaceHandle(file_name, &x, &i);
			continue;
		}
		if (canBeInFileName(c)) {
			putch(c);
			x++;
			file_name[i++] = c;
		}
	}
	if (c == ESCAPE) {
		curr_kayboard_state.escape = PRESSED;
	}
	else if (i == 0) {
		colorSaveLine(RED);
		textcolor(WHITE);
		gotoxy(1, console.height);
		cputs("Blad zapisu. Nazwa pliku musi miec minimum jeden znak.");
		saves.alert_to_clear = 1;
		curr_kayboard_state.escape = PRESSED;
		_setcursortype(_NOCURSOR);
		return curr_kayboard_state;
	}
	else file_name[i] = '\0';
	colorSaveLine(console.background_color);
	_setcursortype(_NOCURSOR);
	return curr_kayboard_state;
}

void saveGame(char file_name[MAX_FILE_NAME]) {
	FILE* fp;
	FILE** fpp = &fp;
	fopen_s(fpp, file_name, "w");
	fprintf(fp, "%d ", game_state.x);
	fprintf(fp, "%d ", game_state.y);
	fprintf(fp, "%d ", game_state.points_player_one);
	fprintf(fp, "%d ", game_state.points_player_two);
	fprintf(fp, "%d ", game_state.turn);
	fprintf(fp, "%d ", game_state.ko_coords[0]);
	fprintf(fp, "%d ", game_state.ko_coords[1]);
	for (int i = 0; i < board.size; i++)
		for (int j = 0; j < board.size; j++)
			fprintf(fp, "%d ", game_state.board[i][j]);
	fclose(fp);
	lastLineAlert(GREEN, WHITE, "Gra zapisana pomyslnie.");
	saves.alert_to_clear = 1;
}

int canBeInFileName(int c) {
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		c == '.' ||
		c == '-' ||
		c == '_' ||
		c == SPACE) {
		return 1;
	} return 0;
}

void backspaceHandle(char file_name[MAX_FILE_NAME], int* x_pos, int* file_name_index) {
	(*x_pos)--;
	file_name[--(*file_name_index)] = '\0';
	gotoxy(*x_pos, console.height);
	putch(SPACE);
	gotoxy(*x_pos, console.height);
}

void loadGame(char file_name[MAX_FILE_NAME], struct game_state_values *curr_value) {
	FILE* fp;
	FILE** fpp = &fp;
	fopen_s(fpp, file_name, "r");
	if (*fpp) {
		fscanf_s(fp, "%d %d %d %d %d %d %d",
			&(curr_value->x),
			&(curr_value->y),
			&(curr_value->points_player_one),
			&(curr_value->points_player_two),
			&(curr_value->turn),
			&(curr_value->ko_coords[0]),
			&(curr_value->ko_coords[1]));
		for (int i = 0; i < board.size; i++)
			for (int j = 0; j < board.size; j++)
				fscanf_s(fp, "%d", &(curr_value->board[i][j]));
		lastLineAlert(GREEN, WHITE, "Zaladowano pomyslnie.");
		saves.alert_to_clear = 1;
		fclose(fp);
	}
	else {
		lastLineAlert(RED, WHITE, "Blad. Sprawdz czy plik o podanej nazwie istnieje.");
		saves.alert_to_clear = 1;
	}
}

void clrSurrounded(int surrounded[(BOARD_SIZE * BOARD_SIZE) / 2][2]) {
	for (int i = 0; i < (BOARD_SIZE * BOARD_SIZE) / 2; i++) {
		for (int j = 0; j < 2; j++) {
			surrounded[i][j] = -1;
		}
	}
}

void playHendicap(struct game_state_values* curr_state) {
	clrNewGameAlert();
	lastLineAlert(BLACK, WHITE, "=> HENDICAP. ABY ROZPOCZAC GRE WCISNIJ 'H' ");
	curr_state->turn = PLAYER_TWO;
	printWhosTurnIsIt(*curr_state);
	do {
		new_coord('x');
		new_coord('y');
		print_position(curr_state->x, curr_state->y);
		if (curr_state->board[XYToBoardIndex(curr_state->y, 'y')][XYToBoardIndex(curr_state->x, 'x')] != EMPTY) {
			drawCursor(curr_state->x, curr_state->y, CURSOR_ON_STONE);
		}
		else drawCursor(curr_state->x, curr_state->y, CURSOR_COLOR_NORMAL);
		keyboard_handle();
		if (keyboard.i == PRESSED) {
			if (stoneCanBePlaced(curr_state->x, curr_state->y)) {
				drawCursor(curr_state->x, curr_state->y, CURSOR_COLOR_ACTIVE);
				confirm();
				if (keyboard.enter == PRESSED) {
					placeStone(curr_state->x, curr_state->y, curr_state->turn);
					updateBoard(curr_state->x, curr_state->y, PLACE_STONE, true);
				}
			}
		}
	} while (keyboard.h != PRESSED && keyboard.q != PRESSED);
	colorSaveLine(console.background_color);
	restoreChar(curr_state->x, curr_state->y, *curr_state);
}