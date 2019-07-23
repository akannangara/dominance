/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */

#include <string>
#include <iostream>
#include <fstream>

class statistics {
public:
	float number_moves_red;
	float number_possible_moves_red;
	int max_number_possible_moves_red;
	int min_number_possible_moves_red;
	float number_spawn_moves_red;
	float number_attack_moves_red;
	int min_move_count_red;
	int max_move_count_red;
	bool min_count_winning_red;
	bool max_count_winning_red;

	float number_moves_black;
	float number_possible_moves_black;
	int max_number_possible_moves_black;
	int min_number_possible_moves_black;
	float number_spawn_moves_black;
	float number_attack_moves_black;
	int min_move_count_black;
	int max_move_count_black;
	bool min_count_winning_black;
	bool max_count_winning_black;
	
	std::string filename;

	statistics(int c);

	void print_statstistics ();

	void find_averages (int nr_games);

	void add_move_size(int p_id, int a_id, int move_size, bool r_turn);
	void print_stats_to_doc(int p_id_r, int p_id_b, int w_r, int w_b);

	private:
	std::string bool2string(bool value);
	std::string find_player_info(int id);
	int stats2file;
};
