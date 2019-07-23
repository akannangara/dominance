/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */
#ifndef GAME_BOARD_H
#define GAME_BOARD_H

class game_board {
	public:
		game_board() {
			for (int y = 0; y < 7; y++) {
				for (int x = 0; x < 7; x++) {
					if (y == 0 && x == 0) this->board[x][y] = 's';
					else if (y == 0 && x == 6) this->board [x][y] = 's';
					else if (y == 6 && x == 0) this->board [x][y] = 's';
					else if (y == 6 && x == 6) this->board [x][y] = 's';
					else if (y % 2 == 0 && x % 2 == 0) this->board [x][y] = '0';
					else if (y % 2 == 1 && x % 2 == 1) this->board [x][y] = '0';
					else this->board [x][y] = ' ';
				}
			}
			this->r_on = this->b_on = 0;
			this->r_off = this->b_off = 10;
			this->r_turn = true;
		}

		void count_on() {
			int r = 0, b = 0;
			for (int y=0; y < 7; y++) {
				for (int x=0; x < 7; x++) {
					if (this->board[x][y]=='r') r++;
					else if (this->board[x][y]=='b') b++;
				}
			}
			this->r_on = r; this->b_on = b;
		}

		char board [7][7];
		int r_on, r_off, b_on, b_off;
		bool r_turn;
};

#endif
