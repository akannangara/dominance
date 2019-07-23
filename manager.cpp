/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */
#include "manager.h"


//constructor for manager. doet geen fuck
manager::manager() {}


//////////////////////////////////////////////////////////////////////
//PRINT FUNCTIONS
//////////////////////////////////////////////////////////////////////
//print the given game_board onto the screen
void manager::print_board(game_board print) {
	for (int y = 0; y < 7; y++) {
		for (int x = 0; x < 7; x++) {
			std::cout << print.board[x][y] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "r_on:" << print.r_on << ";b_on:" << print.b_on << std::endl;
	std::cout << "r_off:"<<print.r_off<<";b_off:"<<print.b_off<<std::endl;
	if (print.r_turn) std::cout << "red's turn" << std::endl << std::endl;
	else { std::cout << "black's turn" << std::endl << std::endl; }
}

//print the given game_move onto the screen
void manager::print_move (game_move print) {
	std::cout << "player " << print.player << "from " << print.x_old<< "," <<
						print.y_old << " to " << print.x_new << "," << print.y_new
						<< std::endl;
}
///////////////////////END PRINT FUNCTIONS////////////////////////////



/////////////////////////////////////////////////////////////////////
///////////////////////GENERATE POSSIBLE MOVES LIST /////////////////
/////////////////////////////////////////////////////////////////////
//returns list of possible moves for the given game_board
std::list<game_move> manager::find_moves (game_board game) {
	std::list<game_move> moves;
	char ally, enemy;
	if (game.r_turn) {ally = 'r'; enemy = 'b';}
	else {ally = 'b'; enemy = 'r';}
	for (int y = 0; y < 7; y++) {
		for (int x = 0; x < 7; x++) {
			if (game.board[x][y] == 's') {
				if(possible_move(game, ally, enemy, x, y, -1, -1)) {
					if ((game.r_turn && game.r_off > 0) || (!game.r_turn && game.b_off > 0))
						list_add_move(moves, -1, -1, x, y, ally, game);
				}//spawn from position x, y is possible
			}//(possible) spawn point has been found
			else if (game.board[x][y] == ally) {
				if ((y-2>-1)&&(game.board[x][y-2] == '0'||game.board[x][y-2] == 's')) { 
					if (possible_move(game, ally, enemy, x, y-2, x, y)) {
						list_add_move(moves, x, y, x, y-2, ally, game);
					}
				}//can move up
				if ((x-1>-1)&&(y-1>-1)&&(game.board[x-1][y-1] =='0' ||
						game.board[x-1][y-1] == 's')) {
					if (possible_move(game, ally, enemy, x-1, y-1, x, y)) {
						list_add_move(moves, x, y, x-1, y-1, ally, game);
					}
				}//left up
				if ((x+1<7)&&(y-1>-1)&&(game.board[x+1][y-1] == '0' ||
						game.board[x+1][y-1] == 's')) {
					if (possible_move(game, ally, enemy, x+1, y-1, x, y)) {
						list_add_move(moves, x, y, x+1, y-1, ally, game);
					}
				}//right up
				if ((x-2>-1)&&(game.board[x-2][y]=='0'||game.board[x-2][y]=='s')) {
					if (possible_move(game, ally, enemy, x-2, y, x, y)) {
						list_add_move(moves, x, y, x-2, y, ally, game);
					}
				}//move left
				if ((x+2<7)&&(game.board[x+2][y]=='0'||game.board[x+2][y]=='s')) {
					if (possible_move(game, ally, enemy, x+2, y, x, y)) {
						list_add_move(moves, x, y, x+2, y, ally, game);
					}
				}//move right
				if ((x-1>-1)&&(y+1<7) && (game.board[x-1][y+1]=='0' ||
						game.board[x-1][y+1] == 's')) {
					if (possible_move(game, ally, enemy, x-1, y+1, x, y)) {
						list_add_move(moves, x, y, x-1, y+1, ally, game);
					}
				}//left down
				if ((x+1<7) && (y+1<7) && (game.board[x+1][y+1] =='0' ||
						game.board[x+1][y+1] =='s')) {
					if (possible_move(game, ally, enemy, x+1, y+1, x, y)) {
						list_add_move(moves, x, y, x+1, y+1, ally, game);
					}
				}//right down
				if ((y+2<7)&&(game.board[x][y+2]=='0'||game.board[x][y+2]=='s')) {
					if (possible_move(game, ally, enemy, x, y+2, x, y)) {
						list_add_move(moves, x, y, x, y+2, ally, game);
					}
				}//down
			}//own piece has been found
		}
	}
	return moves;
}


void manager::list_add_move(std::list<game_move>& moves, int x_old, int y_old,
														int x_new, int y_new, char player,
														game_board game) {
	game_move move;
	move.x_new = x_new;
	move.y_new = y_new;
	move.x_old = x_old;
	move.y_old = y_old;
	move.player = player;
	moves.push_back(move);
}
/////////////////////////END GENERATE POSSIBLE MOVES LIST//////////////



////////////////////////////////////////////////////////////////////////////
/////////////////////////////////CHECK POSSIBLE MOVES//////////////////////
//////////////////////////////////////////////////////////////////////////
//position on given game board is determined by variables x and y
//returns true if the postion is free to use or move onto
bool manager::free_position (game_board game, char ally, char enemy, int x, int y) {
	if (game.board[x][y] == enemy || game.board[x][y] == ally) return false;
	
	if ((y-2>-1) && (game.board[x][y-2] == enemy)) {
		if ((x-1>-1) && (y-1>-1) && (game.board[x-1][y-1] == enemy)) return false;
		if ((x+1<7) && (y-1>-1) && (game.board[x+1][y-1] == enemy)) return false;
		if ((y+2<7) && (game.board[x][y+2] == enemy)) return false;
	}
	if ((x-1>-1) && (y-1>-1) && (game.board[x-1][y-1] == enemy)) {
		if ((x-2>-1) && (game.board[x-2][y] == enemy)) return false;
		if ((x+1<7) && (y+1<7) && (game.board[x+1][y+1] == enemy)) return false;
	}
	if ((x+1<7) && (y-1>-1) && (game.board[x+1][y-1] == enemy)) {
		if ((x+2<7) && (game.board[x+2][y] == enemy)) return false;
		if ((x-1>-1) && (y+1<7) && (game.board[x-1][y+1] == enemy)) return false;
	}
	if ((x-2>-1) && (game.board[x-2][y] == enemy))
		if ((x+2<7) && (game.board[x+2][y] == enemy)) return false;
	
	if ((x-1>-1) && (y+1<7) && (game.board[x-1][y+1] == enemy)) {
		if ((x-2>-1) && (game.board[x-2][y] == enemy)) return false;
		if ((y+2<7) && (game.board[x][y+2] == enemy)) return false;
	}
	if ((x+1<7) && (y+1<7) && (game.board[x+1][y+1] == enemy)) {
		if ((x+2<7) && (game.board[x+2][y] == enemy)) return false;
		if ((y+2<7) && (game.board[x][y+2] == enemy)) return false;
	}
	return true;
}

bool manager::attacking_move (game_board game, game_move move) {
	char ally = move.player;
	char enemy;
	if (ally == 'r') enemy = 'b';
	else enemy = 'r';
	return attacking (game, ally, enemy, move.x_new, move.y_new, move.x_old,
										move.y_old);
}

//returns true if you can attack from new position
bool manager::attacking (game_board game, char ally, char enemy, int x_new,
													int y_new, int x_old, int y_old) {
	int x = x_new, y=y_new;
	if (x_old != -1) game.board[x_old][y_old] = '0';
	if ((y-4>-1) && (game.board[x][y-4] == ally) && (game.board[x][y-2] == enemy))
		return true;
	if ((y+4<7) && (game.board[x][y+4] == ally) && (game.board[x][y+2] == enemy))
		return true;
	if ((x-4>-1) && (game.board[x-4][y] == ally) && (game.board[x-2][y] == enemy))
		return true;
	if ((x+4<7) && (game.board[x+4][y] == ally) && (game.board[x+2][y] == enemy))
		return true;

	if ((x-1>-1) && (y-1>-1) && (game.board[x-1][y-1] == ally)) {
		if ((y-2>-1) && (game.board[x][y-2] == enemy)) return true;
		if ((x+1<7) && (game.board[x+1][y-1] == enemy)) return true;
		if ((x-2>-1) && (game.board[x-2][y] == enemy)) return true;
		if ((y+1<7) && (game.board[x-1][y+1] == enemy)) return true;
	}//ally found directly left up
	if ((x+1<7) && (y-1>-1) && (game.board[x+1][y-1] == ally)) {
		if ((y-2>-1) && (game.board[x][y-2] == enemy)) return true;
		if ((x-1>-1) && (game.board[x-1][y-1] == enemy)) return true;
		if ((x+2<7) && (game.board[x+2][y] == enemy)) return true;
		if ((y+1<7) && (game.board[x+1][y+1] == enemy)) return true;
	}//ally found directly right up
	if ((x-1>-1) && (y+1<7) && (game.board[x-1][y+1] == ally)) {
		if ((y-1>-1) && (game.board[x-1][y-1] == enemy)) return true;
		if ((x-2>-1) && (game.board[x-2][y] == enemy)) return true;
		if ((x+1<7) && (game.board[x+1][y+1] == enemy)) return true;
		if ((y+2<7) && (game.board[x][y+2] == enemy)) return true; 
	}//ally found directly left down
	if ((x+1<7) && (y+1<7) && (game.board[x+1][y+1] == ally)) {
		if ((y-1>-1) && (game.board[x+1][y-1] == enemy)) return true;
		if ((x+2<7) && (game.board[x+2][y] == enemy)) return true;
		if ((x-1>-1) && (game.board[x-1][y+1] == enemy)) return true;
		if ((y+2<7) && (game.board[x][y+2] == enemy)) return true;
	}//ally found directly right down

	if ((x-2>-1) && (y-2>-1) && (game.board[x-2][y-2] == ally)) {
		if (game.board[x-1][y-1] == enemy) return true;
	}//ally found diagonally far left up
	if ((x+2<7) && (y-2>-1) && (game.board[x+2][y-2] == ally)) {
		if (game.board[x+1][y-1] == enemy) return true;
	}//ally found diagonally far right up
	if ((x-2>-1) && (y+2<7) && (game.board[x-2][y+2] == ally)) {
		if (game.board[x-1][y+1] == enemy) return true;
	}//ally found diagonally far left down
	if ((x+2<7) && (y+2<7) && (game.board[x+2][y+2] == ally)) {
		if (game.board[x+1][y+1] == enemy) return true;
	}//ally found diagonally far right down

	return false;
}

//returns true if the suggested move is possible
bool manager::possible_move(game_board game, char ally, char enemy, int x_new,
														int y_new, int x_old, int y_old) {
	if (free_position(game, ally, enemy, x_new, y_new)) return true;
	if (attacking(game, ally, enemy, x_new, y_new, x_old, y_old)) return true;
	return false;
}
////////////////////////END CHECK POSSIBLE MOVES//////////////////////







///////////////////////////////////////////////////////////////////////////
////////////////////////CHECK END STATE FUNCTION
//////////////////////////////////////////////////////////////////////////
//returns true if given game has reached an end state
bool manager::end_state(game_board game, std::list<game_board>* perf) {
	char ally, enemy;
	if (game.r_turn) {
		if (game.r_on < 2 && game.r_off < 1) return true;
		if (game.r_off < 2 && game.r_on < 1) return true;
		if (game.r_on + game.r_off < 2) return true;
		ally = 'r'; enemy = 'b';
	} else {
		if (game.b_on < 2 && game.b_off < 1) return true;
		if (game.b_off < 2 && game.b_on < 1) return true;
		if (game.b_on + game.b_off < 2) return true;
		ally = 'b'; enemy = 'r';
	}
	if ((((game.r_turn) && (game.r_on < 2)) || ((!game.r_turn) && (game.b_on < 2)))
		&& !possible_move(game, ally, enemy, 0, 0, -1, -1) &&
		!possible_move(game, ally, enemy, 0, 6, -1, -1) &&
		!possible_move(game, ally, enemy, 6, 0, -1, -1) &&
		!possible_move(game, ally, enemy, 6, 6, -1, -1) && game.board[0][0] != ally
		&& game.board[0][6] != ally && game.board[6][0] != ally &&
		game.board[6][6] != ally)
		return true;

	std::list<game_move> moves = find_moves(game);
	check_possible_moves(&moves, game, perf);
	if (moves.empty()) return true;
	if (moves.size() < 1) return true;
	return false;
}
/////////////////////END CHECKING END STATE FUNTION ///////////////////////



//////////////////////////////////////////////////////////////////////////
////////////////////////APPLY GIVEN MOVE//////////////////////////////////
/////////////////////////////////////////////////////////////////////////
game_board manager::apply_move(game_move move, game_board game) {
	if (move.x_old == -1) {
		if (move.player == 'r') {game.r_on++; game.r_off--;}
		else {game.b_on++; game.b_off--;}
	} else {game.board[move.x_old][move.y_old] = '0';}

	game.board[move.x_new][move.y_new] = move.player;
	
	apply_dominance(game, move);

	game.r_turn = !game.r_turn;
	if (game.board[0][0] == '0') game.board[0][0] = 's';
	if (game.board[6][0] == '0') game.board[6][0] = 's';
	if (game.board[0][6] == '0') game.board[0][6] = 's';
	if (game.board[6][6] == '0') game.board[6][6] = 's';
	return game;
}

void manager::apply_dominance(game_board& game, game_move move) {
	int x = move.x_new, y = move.y_new;
	char enemy, ally;
	if (move.player == 'r') {ally = 'r'; enemy = 'b';}
	else {ally = 'b'; enemy = 'r';}
	if ((y-4>-1)&&(game.board[x][y-4]==ally)&&(game.board[x][y-2]==enemy))
		game.board[x][y-2] = '0';
	if ((x-2>-1)&&(y-2>-1)&&(game.board[x-2][y-2]==ally)&&
			(game.board[x-1][y-1]==enemy))
		game.board[x-1][y-1]='0';

	if ((x+2<7)&&(y-2>-1)&&(game.board[x+2][y-2]==ally)&&
			(game.board[x+1][y-1]==enemy))
		game.board[x+1][y-1] = '0';

	if ((x-4>-1)&&(game.board[x-4][y] == ally)&&(game.board[x-2][y]==enemy))
		game.board[x-2][y]='0';
	if ((x+4<7)&&(game.board[x+4][y]==ally)&&(game.board[x+2][y]==enemy))
		game.board[x+2][y]='0';
	if ((x-2>-1)&&(y+2<7)&&(game.board[x-2][y+2]==ally)&&
			(game.board[x-1][y+1]==enemy))
		game.board[x-1][y-1]='0';
	if ((x+2<7)&&(y+2<7)&&(game.board[x+2][y+2]==ally)&&
			(game.board[x+1][y+1]==enemy))
		game.board[x+1][y+1]='0';
	if ((y+4<7)&&(game.board[x][y+4]==ally)&&(game.board[x][y+2]==enemy))
		game.board[x][y+2]='0';

	if ((x-1>-1)&&(y-1>-1)&&(game.board[x-1][y-1]==ally)) {
		if ((y-2>-1)&&(game.board[x][y-2]==enemy))game.board[x][y-2] = '0';
		if ((x+1<7)&&(y-1>-1)&&(game.board[x+1][y-1]==enemy))
			game.board[x+1][y-1] = '0';
		if ((x-2>-1)&&(game.board[x-1][y]==enemy)) game.board[x-2][y]='0';
		if ((x-1>-1)&&(y+1<7)&&(game.board[x-1][y+1]==enemy))
			game.board[x-1][y+1]='0';
	}
	
	if ((x+1<7)&&(y-1>-1)&&(game.board[x+1][y-1]==ally)) {
		if ((y-2>-1)&&(game.board[x][y-2]==enemy)) game.board[x][y-2]='0';
		if ((x-1>-1)&&(game.board[x-1][y-1]==enemy)) game.board[x-1][y-1]='0';
		if ((x+2<7)&&(game.board[x+2][y]==enemy)) game.board[x+2][y] = '0';
		if ((y+1<7)&&(game.board[x+1][y+1]==enemy)) game.board[x+1][y+1] = '0';
	}

	if ((x-1>-1)&&(y+1<7)&&(game.board[x-1][y+1]==ally)) {
		if ((y-1>-1)&&(game.board[x-1][y-1]==enemy)) game.board[x-1][y-1]='0';
		if ((x-2>-1)&&(game.board[x-2][y]==enemy)) game.board[x-2][y]='0';
		if ((x+1<7)&&(game.board[x+1][y+1]==enemy)) game.board[x+1][y+1]='0';
		if ((y+2<7)&&(game.board[x][y+2]==enemy)) game.board[x][y+2]='0';
	}

	if ((x+1<7)&&(y+1<7)&&(game.board[x+1][y+1]==ally)) {
		if ((y-1>-1)&&(game.board[x+1][y-1]==enemy))game.board[x+1][y-1]='0';
		if ((x+2<7)&&(game.board[x+2][y]==enemy))game.board[x+2][y]='0';
		if ((x-1>-1)&&(game.board[x-1][y+1]==enemy))game.board[x-1][y+1]='0';
		if ((y+2<7)&&(game.board[x][y+2]==enemy))game.board[x][y+2] = '0';
	}
	
	game.board[x][y] = '0';
	if (free_position(game, ally, enemy, x, y)) game.board[x][y]=ally;

	game.count_on();
}
///////////////////////////END APPLY GIVEN MOVE////////////////////////




///////////////////////////COPY BOARD//////////////////////////////////
game_board manager::copy_board(game_board copy) {
	game_board new_game;
	for (int y=0; y<7; y++) {
		for (int x=0; x<7; x++) {
			new_game.board[x][y] = copy.board[x][y];
		}
	}
	new_game.r_on = copy.r_on;
	new_game.r_off = copy.r_off;
	new_game.b_on = copy.b_on;
	new_game.b_off = copy.b_off;
	new_game.r_turn = copy.r_turn;
	return new_game;
}


/*
////////////////////////////////////////////////////
////////////////////check perf moves/////////////////
//////////////////////////////////////////////////
void manager::clear_performed_moves() {
	for (int i = 0; i < PERFORMED_MOVES_NUMBER; i++) {
		game_move clear;
		clear.x_old = clear.y_old = clear.x_new = clear.y_new = -2;
		clear.player = 'F';
		performed_moves[i] = clear;
	}
}

void manager::add_to_performed_moves(game_move move) {
	if (!(same_moves(performed_moves[0], move))) {
		if (performed_moves[1].x_old == -2) {}
		else if (!(same_moves(performed_moves[1], move))) 
			clear_performed_moves();
	}
	for (int i = 0; i < PERFORMED_MOVES_NUMBER; i++) {
		if (performed_moves[i].x_old == -2) {
			performed_moves[i] = move;
			i = PERFORMED_MOVES_NUMBER;
		}
	}
}

bool manager::same_moves(game_move m1, game_move m2) {
	if (m1.x_old == m2.x_old && m1.x_new == m2.x_new) {
		if (m1.y_old == m2.y_old && m1.y_new == m2.y_new)
			return true;
	}
	return false;
}


std::list<game_move> manager::check_performed_moves(
																		std::list<game_move> moves) {
	if (performed_moves[PERFORMED_MOVES_NUMBER-1].x_new != -2) {
		for (auto m = moves.begin(); m != moves.end();) {
			if (same_moves(*m, performed_moves[0])){
				m = moves.erase(m);
			} else ++m;
		}
	}
	return moves;
}
*/

void manager::add_to_performed_states(game_board game, std::list<game_board>* s_list) {
	s_list->push_back(game);
}

void manager::clear_performed_states(std::list<game_board>* performed) {
	performed->clear();
}

bool manager::same_board_state(game_board g1, game_board g2) {
	for (int y = 0; y < 7; y++) {
		for (int x = 0; x < 7; x++) {
			if (g1.board[x][y] != g2.board[x][y]) return false;
		}
	}
	return true;
}

bool manager::possible_move_to_perform(game_board game, game_move move, std::list<game_board>* s_list) {
	game = apply_move(move, game);
	for (std::list<game_board>::iterator it=s_list->begin();
				it != s_list->end(); ++it) {
		if (same_board_state(game, *it)) return false;
	}
	return true;
}

void manager::check_possible_moves(std::list<game_move>* m,
					game_board g, std::list<game_board>* s_list) {
	for(std::list<game_move>::iterator it = m->begin();
			it != m->end(); ++it) {
		if (!possible_move_to_perform(g, *it, s_list)) {
			it = m->erase(it);
			--it;
		}
	}

}




