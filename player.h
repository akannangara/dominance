/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */

#include "manager.h"
#include "statistics.h"
#include "mcts_node.h"
#include <cstdlib>
#include <ctime>
#include <cmath>


class player {
	public:
		player(statistics* stats_holder, int q_id, int q_a, int q_b, int q_g, int q_d);
		game_board play(game_board game);

		int player_id;

		int calc_heuristiek(game_board game, std::list<game_board>* s_list);

		//temp statistics for player
		void reset_temp_stats();
		int temp_nr_possible_moves;
		int temp_number_spawn_moves;
		int temp_number_attack_moves;
		
		statistics* stats;

		manager man;

	private:
		
		void collect_stats_selected_move(int p_id, int a_id,
						game_move m, game_board g,
						std::list<game_board>* performed);
		void copy_performed_list(std::list<game_board>* src,
						std::list<game_board>* dst);

		//Random players
		game_board random(game_board game, std::list<game_board>* performed);
		game_board randomG(game_board game, std::list<game_board>* performed);
		game_move select_random_from_list (
					std::list<game_move> moves);
		game_move select_random_list (
					std::list<game_move> l1,
					std::list<game_move> l2,
					int v_l1, int v_l2);
		int alpha, beta, gamma, alpha1, beta1, gamma1; //working with ratios

		//human player
		game_board human(game_board game, std::list<game_board>* performed);

		//monte carlo players
		game_board monte_carlo(game_board game, std::list<game_board>* performed);
		game_board monte_carloF(game_board game);
		game_board monte_carloABG(game_board game, std::list<game_board>* performed);
		game_board monte_carlo1000(game_board game);
		int monte_nr;
		int monte_threshold;

		//negamax
		game_board negamax_select(game_board game, std::list<game_board>* performed);
		tree_node negamax(game_board game, int depth, std::list<game_board>* s_list);
		int negamax_search_depth;




		//MCTS --> some functions are unused....
		int mcts_Ni;
		int mcts_nr;
		double value_c;
		game_board mcts_select(game_board game, std::list<game_board>* s_list);
		mcts_node make_node(game_board game, mcts_node* p);
		void fill_child_list(mcts_node* node);
		void mcts_play(mcts_node* root);
		void backpropogate(bool won, mcts_node* node);
		mcts_node* selection(mcts_node* node);
		mcts_node* expansion(mcts_node* node);
		bool simulation(mcts_node* node);
		game_board to_return_game_board(mcts_node* node);
		game_move convert_to_game_move (game_board game, game_board new_game);
		
		void define_c (int o);

		
		void mcts_expand(mcts_node* root);
		
		int mcts_d;
		
		bool mcts_test_node (mcts_node node);
		bool mcts_children_not_visited (mcts_node* root);
		void mcts_fill_child_list(mcts_node* node);
		void calc_UTC(mcts_node* node);
		void print_mcts(mcts_node, int depth);
		
		

};
