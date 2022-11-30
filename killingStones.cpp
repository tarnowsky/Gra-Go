#include "graGo.h"

bool moveKills(
	int x,
	int y,
	struct game_state_values curr_state,
	struct board_opt curr_board,
	int surrounded[BOARD_SIZE * BOARD_SIZE / 2][2],
	int possible_kills[4][3]) {

    // sprawdŸ czy kamieñ jest w tablicy zbicia i zaznacz obecnosc
    for (int i = 0; i < 4; i++) {
        if (x == possible_kills[i][0] && y == possible_kills[i][1]) {
            possible_kills[i][2] = 1;
            break;
        }
    }

    // sprawdz kierunki w ktorych moga znajdowac sie inne kamienie
    int x_lewo = ((x - 1 >= 0) ? (x - 1) : -1);
    int x_prawo = ((x + 1 < curr_board.size) ? (x + 1) : -1);
    int y_gora = ((y - 1 >= 0) ? (y - 1) : -1);
    int y_dol = ((y + 1 < curr_board.size) ? (y + 1) : -1);
    

    // sprawdz czy kamien jest otoczony, jesli nie zwroc false
    if (x_lewo != -1)
        if (curr_state.board[y][x_lewo] == EMPTY)
            return false;
    if (x_prawo != -1)
        if (curr_state.board[y][x_prawo] == EMPTY)
            return false;
    if (y_gora != -1)
        if (curr_state.board[y_gora][x] == EMPTY)
            return false;
    if (y_dol != -1)
        if (curr_state.board[y_dol][x] == EMPTY)
            return false;


    // dodaj do otoczonych
    int index_otoczone;
    for (index_otoczone = 0; index_otoczone < (BOARD_SIZE*BOARD_SIZE/2) && surrounded[index_otoczone][0] != -1; index_otoczone++)
        ;
    surrounded[index_otoczone][0] = x;
    surrounded[index_otoczone][1] = y;

    // znajdz kolejny potencjalny element struktury
    if (y_gora != -1)
        if (curr_state.board[y_gora][x] == (curr_state.turn == PLAYER_ONE ? STONE_P2 : STONE_P1)) {
            bool kamien_byl_sprawdzany = false;
            for (int i = 0; i < (BOARD_SIZE*BOARD_SIZE/2) && surrounded[i][0] != -1; i++) {
                if (surrounded[i][0] == x && surrounded[i][1] == y_gora) {
                    kamien_byl_sprawdzany = true;
                    break;
                }
            }
            if (!kamien_byl_sprawdzany) {
                if (!moveKills(x, y_gora, curr_state, curr_board, surrounded, possible_kills))
                    return false;
            }
        }

    if (x_prawo != -1)
        if (curr_state.board[y][x_prawo] == (curr_state.turn == PLAYER_ONE ? STONE_P2 : STONE_P1)) {
            bool kamien_byl_sprawdzany = false;
            for (int i = 0; i < (BOARD_SIZE*BOARD_SIZE/2) && surrounded[i][0] != -1; i++) {
                if (surrounded[i][0] == x_prawo && surrounded[i][1] == y) {
                    kamien_byl_sprawdzany = true;
                    break;
                }
            }
            if (!kamien_byl_sprawdzany) {
                if (!moveKills(x_prawo, y, curr_state, curr_board, surrounded, possible_kills))
                    return false;
            }
        }

    if (y_dol != -1)
        if (curr_state.board[y_dol][x] == (curr_state.turn == PLAYER_ONE ? STONE_P2 : STONE_P1)) {
            bool kamien_byl_sprawdzany = false;
            for (int i = 0; i < (BOARD_SIZE*BOARD_SIZE/2) && surrounded[i][0] != -1; i++) {
                if (surrounded[i][0] == x && surrounded[i][1] == y_dol) {
                    kamien_byl_sprawdzany = true;
                    break;
                }
            }
            if (!kamien_byl_sprawdzany) {
                if (!moveKills(x, y_dol, curr_state, curr_board, surrounded, possible_kills))
                    return false;
            }
        }

    if (x_lewo != -1)
        if (curr_state.board[y][x_lewo] == (curr_state.turn == PLAYER_ONE ? STONE_P2 : STONE_P1)) {
            bool kamien_byl_sprawdzany = false;
            for (int i = 0; i < (BOARD_SIZE*BOARD_SIZE/2) && surrounded[i][0] != -1; i++) {
                if (surrounded[i][0] == x_lewo && surrounded[i][1] == y) {
                    kamien_byl_sprawdzany = true;
                    break;
                }
            }
            if (!kamien_byl_sprawdzany) {
                if (!moveKills(x_lewo, y, curr_state, curr_board, surrounded, possible_kills))
                    return false;
            }
        }

    return true;
}

bool moveCanKill(
    int x,
    int y,
    struct game_state_values curr_state,
    struct board_opt curr_board,
    int possible_kills[4][3]) {

    enum axis {
        GORA,
        DOL,
        PRAWO,
        LEWO
    };

    int x_lewo = ((x - 1 >= 0) ? (x - 1) : -1);
    int x_prawo = ((x + 1 < curr_board.size) ? (x + 1) : -1);
    int y_gora = ((y - 1 >= 0) ? (y - 1) : -1);
    int y_dol = ((y + 1 < curr_board.size) ? (y + 1) : -1);

    bool znaleziony_kamien = false;

    if (x_lewo != -1) {
        if (curr_state.board[y][x_lewo] == (curr_state.turn == PLAYER_ONE ? STONE_P2 : STONE_P1)) {
            znaleziony_kamien = true;
            possible_kills[LEWO][0] = x_lewo;
            possible_kills[LEWO][1] = y;
        }
    }

    if (x_prawo != -1) {
        if (curr_state.board[y][x_prawo] == (curr_state.turn == PLAYER_ONE ? STONE_P2 : STONE_P1)) {
            znaleziony_kamien = true;
            possible_kills[PRAWO][0] = x_prawo;
            possible_kills[PRAWO][1] = y;
        }
    }

    if (y_gora != -1) {
        if (curr_state.board[y_gora][x] == (curr_state.turn == PLAYER_ONE ? STONE_P2 : STONE_P1)) {
            znaleziony_kamien = true;
            possible_kills[GORA][0] = x;
            possible_kills[GORA][1] = y_gora;
        }
    }

    if (y_dol != -1) {
        if (curr_state.board[y_dol][x] == (curr_state.turn == PLAYER_ONE ? STONE_P2 : STONE_P1)) {
            znaleziony_kamien = true;
            possible_kills[DOL][0] = x;
            possible_kills[DOL][1] = y_dol;
        }
    }

    if (znaleziony_kamien) return true;
    else return false;
}