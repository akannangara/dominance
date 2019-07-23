/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */

#include "statistics.h"


statistics::statistics(int c) {
	number_moves_red = 0;
	number_possible_moves_red = 0;
	max_number_possible_moves_red = 0;
	min_number_possible_moves_red = 1000;
	number_spawn_moves_red = 0;
	number_attack_moves_red = 0;
	min_move_count_red = 1000;
	max_move_count_red = 0;
	min_count_winning_red = false;
	max_count_winning_red = false;

	number_moves_black = 0;
	number_possible_moves_black = 0;
	max_number_possible_moves_black = 0;
	min_number_possible_moves_black = 1000;
	number_spawn_moves_black = 0;
	number_attack_moves_black = 0;
	min_move_count_black = 1000;
	max_move_count_black = 0;
	min_count_winning_black = false;
	max_count_winning_black = false;
	//std::cout << "do you want stat file? 1=y;0=n" << std::endl;
	//std::cin >> stats2file;
	stats2file = 2;
	switch(stats2file) {
		case 1:
			std::cout << "enter stat file name" << std::endl;
			std::cin >> filename;
			break;
		case 2:
			if (c == 0) filename = "mcts_abgmc-1.txt"; //maar dan eigenlijk i *2!!!
			else if (c == 1) filename = "mcts_abgmc-2.txt";
			else if (c == 2) filename = "mcts_abgmc-3.txt";
			else if (c == 3) filename = "mcts_abgmc-4.txt";
			else if (c == 4) filename = "mcts_abgmc-5.txt";
			else if (c == 5) filename = "mcts_abgmc-6.txt";
			else if (c == 6) filename = "mcts_abgmc-7.txt";
			else if (c == 7) filename = "mcts_abgmc-8.txt";
			else if (c == 8) filename = "mcts_abgmc-9.txt";
			else if (c == 9) filename = "mcts_abgmc-10.txt";
			else if (c == 10) filename = "mcts_abgmc-11.txt";
			else if (c == 11) filename = "mcts_abgmc-12.txt";
			else if (c == 12) filename = "mcts_abgmc-13.txt";
			else if (c == 13) filename = "mcts_abgmc-14.txt";
			else if (c == 14) filename = "mcts_abgmc-15.txt";
			else if (c == 15) filename = "mcts_abgmc-16.txt";
			else if (c == 16) filename = "mcts_abgmc-17.txt";
			else if (c == 17) filename = "mcts_abgmc-18.txt";
			else if (c == 18) filename = "mcts_abgmc-19.txt";
			else if (c == 19) filename = "mcts_abgmc-20.txt";
			else if (c == 20) filename = "mcts_abgmc.txt";
			else if (c == 21) filename = "mcabg_mcts-3500.txt";
			else if (c == 22) filename = "mcabg_mcts-3750.txt";
			else if (c == 23) filename = "mcabg_mcts-4000.txt";
		default: break;
	}
}

void statistics::print_statstistics () {
	std::cout << "statistics for red player:" << std::endl;
	std::cout << "  number of performed moves: " << number_moves_red << std::endl;
	std::cout << "  number possible moves: " << number_possible_moves_red << std::endl;
	std::cout << "  max number possible moves: " << max_number_possible_moves_red << std::endl;
	std::cout << "  min number possible moves: " << min_number_possible_moves_red << std::endl;
	std::cout << "  number performed spawn: " << number_spawn_moves_red << std::endl;
	std::cout << "  number performed attack: " << number_attack_moves_red << std::endl;
	std::cout << "  min number moves performed: " << min_move_count_red << std::endl;
	if (min_count_winning_red) std::cout << "    and was won by me (red)" << std::endl;
	else std::cout << "    and was won by black" << std::endl;
	std::cout << "  max number moves performed: " << max_move_count_red << std::endl;
	if (max_count_winning_red) std::cout << "    and was won by me (red)" << std::endl;
	else std::cout << "    and was won by black" << std::endl;
	
	std::cout << std::endl;
	std::cout << "statistics for black player:" << std::endl;
	std::cout << "  number of performed moves: " << number_moves_black << std::endl;
	std::cout << "  number possible moves: " << number_possible_moves_black << std::endl;
	std::cout << "  max number possible moves: " << max_number_possible_moves_black << std::endl;
	std::cout << "  min number possible moves: " << min_number_possible_moves_black << std::endl;
	std::cout << "  number performed spawn: " << number_spawn_moves_black << std::endl;
	std::cout << "  number performed attack: " << number_attack_moves_black << std::endl;
	std::cout << "  min number moves performed: " << min_move_count_black << std::endl;
	if (min_count_winning_black) std::cout << "    and was won by me (black)" << std::endl;
	else std::cout << "    and was won by red" << std::endl;
	std::cout << "  max number moves performed: " << max_move_count_black << std::endl;
	if (max_count_winning_black) std::cout << "    and was won by me (black)" << std::endl;
	else std::cout << "    and was won by red" << std::endl;
	std::cout << std::endl << std::endl;
}

void statistics::find_averages (int nr_games) {
	number_moves_red /= nr_games;
	number_possible_moves_red /= nr_games;
	number_spawn_moves_red /= nr_games;
	number_attack_moves_red /= nr_games;
	number_moves_black /= nr_games;
	number_possible_moves_black /= nr_games;
	number_spawn_moves_black /= nr_games;
	number_attack_moves_black /= nr_games;
}

void statistics::add_move_size(int p_id, int a_id, int move_size, bool r_turn) {
	if (p_id == a_id && r_turn) {
		number_possible_moves_red += move_size;
		if ((move_size < min_number_possible_moves_red) && (move_size > 0))
		min_number_possible_moves_red = move_size;
		else if (move_size > max_number_possible_moves_red)
			max_number_possible_moves_red = move_size;
	} else if (p_id == a_id && !r_turn) {
		number_possible_moves_black += move_size;
		if ((move_size < min_number_possible_moves_black) && (move_size > 0))
			min_number_possible_moves_black = move_size;
		else if (move_size > max_number_possible_moves_black)
			max_number_possible_moves_black = move_size;
	}
}

std::string statistics::bool2string(bool value) {
	if (value) return "true";
	else return "false";
	return "false";
}

void statistics::print_stats_to_doc(int p_id_r, int p_id_b, int w_r, int w_b) {
	if (stats2file > 0) {
		std::cout << "printing stats to doc: " << filename << std::endl;
		std::string p_r = find_player_info(p_id_r);
		std::string p_b = find_player_info(p_id_b);
		std::ofstream fout (filename, std::ofstream::out);
		fout << "\\begin{table}[h] \n \\begin{tabular}{ |p{5cm}||p{4cm}|p{4cm}|} \\hline \\multicolumn{3}{|c|}{1000000 games} \\newline";
		fout <<"\\hline & "<<p_r<< "(red) & " <<p_b<<" (black) \\newline \\hline  \n";
		fout << "wins & "<< w_r << " & "<<w_b<<"\\\\ \n";
		fout <<" pref. moves & "<< number_moves_red <<" & " << number_moves_black <<" \\\\ \n";
		fout << "nr. pos. moves & "<< number_possible_moves_red <<" & " << number_possible_moves_black <<" \\\\ \n";
		fout << "max. nr. pos. moves & "<< max_number_possible_moves_red <<" & " << max_number_possible_moves_black <<" \\\\ \n";
		fout << "min. nr. pos. moves & "<<min_number_possible_moves_red <<" & " << min_number_possible_moves_black <<" \\\\ \n";
		fout << "nr. perf. spawn & "<< number_spawn_moves_red<<" & " << number_spawn_moves_black <<" \\\\ \n";
		fout << "nr. perf. attack & "<<number_attack_moves_red <<" & " << number_attack_moves_black<<" \\\\ \n";
		fout << "min. nr. perf. moves & "<< min_move_count_red<<" & " << min_move_count_black <<" \\\\ \n";
		std::string boolean_r = bool2string(min_count_winning_red);
		std::string boolean_b = bool2string(min_count_winning_black);
		fout <<"\\hookrightarrow Won? & "<< boolean_r <<" & " << boolean_b <<" \\\\ \n";
		fout <<"max. nr. perf. moves & "<< max_move_count_red <<" & " << max_move_count_black <<" \\\\ \n";
		boolean_r = bool2string(max_count_winning_red);
		boolean_b = bool2string(max_count_winning_black);
		fout <<"\\hookrightarrow Won? & "<< boolean_r <<" & " << boolean_b <<" \\\\ \n";
		fout <<"\\hline \\end{tabular} \\end{table} \n";
		fout.close();
	}
}

std::string statistics::find_player_info(int id) {
	switch (id) {
		case 1: return "Human"; break;
		case 2: return "Pure Random"; break;
		case 5: return "ABG-Random"; break;
		case 6: return "Monte Carlo (PR)"; break;
		case 8: return "Nega-max"; break;
		case 9: return "ABG-Monte Carlo"; break;
		case 11: return "MCTS"; break;
		default: exit(1); break;
	}
	return "error";
}

