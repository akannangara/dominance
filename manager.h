/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */
#include <iostream>
#include "tree_node.h"
#include "game_board.h"
#include <list>
#include <iterator>

#define PERFORMED_MOVES_NUMBER 6


class manager {
	public:
		manager();

////////////PRINT FUNCTIONS///////////////
		//print the given game_board onto the screen
		void print_board(game_board print);

		//print the given move onto the screen
		void print_move (game_move print);



//////////GENERATE POSSIBLE MOVES LIST//////////
		//returns a list of possible moves given the current game_board
		//situation
		std::list<game_move> find_moves_debug(game_board game);

		void list_add_move(std::list<game_move>& moves, int x_old, int y_old,
												int x_new, int y_new, char player, game_board game);

		std::list<game_move> find_moves(game_board game);



////////////////////APPLY GIVEN MOVE///////////////
//allies the given game_move to the given game_board
//the new game_board is returned
game_board apply_move(game_move move, game_board game);

void apply_dominance(game_board& game, game_move move);



//////////////CHECK POSSIBLE MOVES//////////////
//position on given game board is determined by variables x and y
//returns true if the postion is free to use or move onto
//returns false if the postion is dominated by and enemy or not availible
bool free_position (game_board game, char ally, char enemy, int x, int y);

//checks if the given move is an attacking move
//for the given board situation
bool attacking_move(game_board game, game_move move);

//checks if you can attack from new position
//returns true if you can attack from the new position
bool attacking (game_board game, char ally, char enemy, int x_new, int y_new, int x_old, int y_old);

//returns true if the given move is possible else will return false
bool possible_move(game_board game, char ally, char enemy, int x_new,
													int y_new, int x_old, int y_old);



/////////////////CHECK END STATE FUCNTION////////////
//returns true if the given game_board has reached an end state
bool end_state(game_board game, std::list<game_board>* perf);


///////////////COPY BOARD//////////////////////////
game_board copy_board(game_board copy);


		//to keep list of performed_moves
		/*
		game_move performed_moves [PERFORMED_MOVES_NUMBER];
		void clear_performed_moves();
		void add_to_performed_moves(game_move move);
		std::list<game_move> check_performed_moves(
																std::list<game_move> moves);
		bool same_moves(game_move m1, game_move m2);
		*/

		std::list<game_board> performed_game_states;
		void add_to_performed_states(game_board game, std::list<game_board>* s_list);
		void clear_performed_states(std::list<game_board>* performed);
		bool same_board_state(game_board g1, game_board g2);
		void check_possible_moves(std::list<game_move>* m, game_board g,
						std::list<game_board>* s_list);
		bool possible_move_to_perform(game_board game, game_move move,
						std::list<game_board>* s_list);
};
