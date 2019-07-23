/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */


#include <iostream>
#include "player.h"
#include <fstream>
#include <omp.h>

int dotDepth;

//statistics stats_0;
//player p0(&stats_0);
/*
void print_dot_board(game_board print, std::ofstream& fout) {
	fout <<" [label=\"";
	manager man;
	if (man.end_state(print)) fout << "END STATE \\l ";
	for (int y = 0 ; y < 7; y++){
		for (int x = 0; x < 7; x++) {
			fout << print.board [x][y] << " ";
		}
		fout << " \\l ";
	}
	fout << "\\l ";
	fout << "rOn:" << print.r_on << ";bOn" << print.b_on << " \\l ";
	fout << "rOff:" << print.r_off << ";bOff" << print.b_off << " \\l ";
	//fout << "h: " << p0.calc_heuristiek(print) << " \\l ";
	if (print.r_turn) fout << "red's turn" << " \"]; \n";
	else fout << "black's turn" << " \"]; \n";
	
}

void print_dot_edge(int parent, int child, game_move move, std::ofstream& fout) {
	fout << parent << " -> " << child;
	fout << " [label=\""<< move.x_old<<","<<move.y_old<<"; \\l "<<move.x_new<<","
				<< move.y_new<<" \"]; \n";
}


void print_dot_node(game_board print, game_move move, int parent, int& totalNodes,
										int depth, std::ofstream& fout) {
	totalNodes = totalNodes + 1;
	int child = totalNodes;
	fout << totalNodes;
	print_dot_board(print, fout);
	//std::cout << "looking at " << parent << " and " << totalNodes << " at " <<
	//							depth << std::endl;
	if (depth < dotDepth) print_dot_edge(parent, child, move, fout);
	manager man;
	if (depth > 0 && !man.end_state(print)) {
		std::list<game_move> moves = man.find_moves (print);
		game_board temp;
		int i = 0;
		for (auto& m : moves) {
			i++;
			//std::cout << i << std::endl;
			temp = man.apply_move (m, print);
			print_dot_node(temp, m, child, totalNodes, depth-1, fout);
		}
	}
}

void print_dot_tree(game_board starter) {
	std::cout << "In print tree in dot form" << std::endl;
	std::string fileName;
	std::cout << "Enter dotfile name: " << std::endl;
	std::cin >> fileName;
	std::ofstream fout (fileName, std::ofstream::out);
	int totalNodes = -1;
	std::cout << "enter depth:"<<std::endl;
	std::cin >> dotDepth;
	fout << "digraph T { \n node [fontname=Arial fontsize =5]; \n edge [fontsize=6]; \n";
	
	//fout << totalNodes;
	//printDotBoard (root, fout);
	game_move move;
	move.x_old = -1; move.y_old = -1;
	print_dot_node(starter, move, totalNodes, totalNodes, dotDepth, fout);

	fout <<"} \n";
	fout.close();
	
}
*/

game_board edit_root(game_board root) {
///*
	root.board[2][0] = 'b';
	root.board[6][0] = 'r';
	root.board[3][1] = 'b';
	root.board[1][3] = 'b';
	root.board[3][3] = 'b';
	root.board[2][4] = 'b';
	root.board[0][6] = 'r';
	root.r_on = 2;
	root.b_on = 5;
	root.r_off = 0;
	root.b_off = 0;
	root.r_turn = false;

//*/

	return root;
}


/*
void gameABG() {
	for (int g = 0; g < 6; g++) {
		std::string filename = "ABG_stats_g"+std::to_string(g)+".txt";
		std::ofstream fout (filename, std::ofstream::out);
		for (int a = 0; a < 6; a++) {
			for (int b = 0; b < 6; b++) {
				std::cout << "start set a="<<a<<";b="<<b<<";g="<<g<<"; p1=5;p2=6"<<std::endl;
				game_board root;
				manager man;
				statistics stats;
				player p1(&stats, 5, a, b, g, 0);
				player p2(&stats, 6, 0, 0, 0, 10);
				int nr_games = 10;

				int black_wins = 0, red_wins = 0;
				int qb = 0, qr = 0, qg = 0;
				for (int i = 0; i < nr_games; i++) {
					p1.reset_temp_stats();
					p2.reset_temp_stats();
					game_board game;
					game = root;
					int local_nr_moves_red =0, local_nr_moves_black = 0;
					int q = 0;
					//man.print_board(game);
					while(!man.end_state(game, &p1.man.performed_game_states)) {
						game = p1.play(game);
						stats.number_moves_red++;
						local_nr_moves_red++;
						q++;
						qr++;
						//man.print_board(game);
						if (man.end_state(game, &p2.man.performed_game_states))
							{break; }
						else {
							game = p2.play(game);
							stats.number_moves_black++;
							local_nr_moves_black++;
							q++;
							qb++;
						}
						//man.print_board(game);
					}
					qg += q;
					if (local_nr_moves_black > stats.max_move_count_black) {
						stats.max_move_count_black = local_nr_moves_black;
						if (game.r_turn) stats.max_count_winning_black = true;
						else stats.max_count_winning_red = false;
					}
					if (local_nr_moves_red > stats.max_move_count_red) {
						stats.max_move_count_red = local_nr_moves_red;
						if (!game.r_turn) stats.max_count_winning_red = true;
						else stats.max_count_winning_red = false;
					}

					if (local_nr_moves_black < stats.min_move_count_black) {
						stats.min_move_count_black = local_nr_moves_black;
						if (game.r_turn) stats.min_count_winning_black = true;
						else stats.min_count_winning_black = false;
					}
					if (local_nr_moves_red < stats.min_move_count_red) {
						stats.min_move_count_red = local_nr_moves_red;
						if (!game.r_turn) stats.min_count_winning_red = true;
						else stats.min_count_winning_red = false;
					}
					if (game.r_turn) black_wins++;
					else red_wins++;
					std::cout << "red wins: " << red_wins <<"; black wins: " << black_wins << ";"<< i << std::endl;
				}
				fout << a << " " << b << " " << red_wins << "\n";
			}
		}
		fout.close();
	}
}
*/

void gameMC_ABG() {
	#pragma omp parallel
	#pragma omp for
	for (int o = 0; o < 20; o++) {
		/*
		int mc_nr = 300;
		if (o == 1) mc_nr = 400;
		else if (o == 2) mc_nr = 500;
		else if (o == 3) mc_nr = 600;
		else if (o == 4) mc_nr = 700;
		else if (o == 5) mc_nr = 800;
		else if (o == 6) mc_nr = 900;
		else if (o == 7) mc_nr = 1000;red wins: 34; black wins: 3 in 0
red wins: 35; black wins: 3 in 0

		*/
		
		game_board root;
		//root = edit_root(root);
		manager man;
		statistics stats(o);
		//print_dot_tree(root);
		
		int p1_nr = 9; int p2_nr = 11; int a = 4; int b = 2; int g=0; int d1=100; int d2=o;
/*		if (o == 0) {
			p1_nr = 9;
			p2_nr = 11;
			d1 = 100;
			d2 = o;
		} else {
			p1_nr = 11;
			p2_nr = 9;
			d1 = o;
			d2 = 100;
		}*/

		std::cout << "player 1" << std::endl;
		player p1(&stats, p2_nr, a, b, g, d2);
		std::cout << "player 2" << std::endl;
		player p2(&stats, p1_nr, a, b, g, d1);
		std::cout << "enter number of games to be played" << std::endl;
		int nr_games = 50;
		//std::cin >> nr_games;

		int black_wins = 0, red_wins = 0;
		game_board game;
		int qb = 0, qr = 0, qg = 0;
		for (int i = 0; i < nr_games; i++) {
			p1.reset_temp_stats();
			p2.reset_temp_stats();
			game = root;
			int local_nr_moves_red =0, local_nr_moves_black = 0;
			int q = 0;
			//man.print_board(game);
			while(!man.end_state(game, &p1.man.performed_game_states)) {
				game = p1.play(game);
				stats.number_moves_red++;
				local_nr_moves_red++;
				q++;
				qr++;
				//man.print_board(game);
				if (man.end_state(game, &p2.man.performed_game_states))
					{break; }
				else {
					game = p2.play(game);
					stats.number_moves_black++;
					local_nr_moves_black++;
					q++;
					qb++;
				}
				//man.print_board(game);
			}
			qg += q;
			if (local_nr_moves_black > stats.max_move_count_black) {
				stats.max_move_count_black = local_nr_moves_black;
				if (game.r_turn) stats.max_count_winning_black = true;
				else stats.max_count_winning_red = false;
			}
			if (local_nr_moves_red > stats.max_move_count_red) {
				stats.max_move_count_red = local_nr_moves_red;
				if (!game.r_turn) stats.max_count_winning_red = true;
				else stats.max_count_winning_red = false;
			}

			if (local_nr_moves_black < stats.min_move_count_black) {
				stats.min_move_count_black = local_nr_moves_black;
				if (game.r_turn) stats.min_count_winning_black = true;
				else stats.min_count_winning_black = false;
			}
			if (local_nr_moves_red < stats.min_move_count_red) {
				stats.min_move_count_red = local_nr_moves_red;
				if (!game.r_turn) stats.min_count_winning_red = true;
				else stats.min_count_winning_red = false;
			}
			if (game.r_turn) black_wins++;
			else red_wins++;
			std::cout << "red wins: " << red_wins <<"; black wins: " << black_wins <<
			" in " << o << std::endl;
		}

	//	std::cout << "tot r perf: " << qr/nr_games << "; tot b perf: " << qb/nr_games << "; tot g perf: " << qg/nr_games << std::endl;
	//	std::cout<< std::endl <<"red wins: "<< red_wins <<"; black wins: "<< black_wins<<std::endl;

		stats.find_averages(nr_games);
		stats.print_statstistics();
		stats.print_stats_to_doc(p1.player_id, p2.player_id, red_wins, black_wins);
	}
}



void game() {
	game_board root;
	//root = edit_root(root);
	manager man;
	statistics stats(1);
	//print_dot_tree(root);

	std::cout << "player 1" << std::endl;
	player p1(&stats, 0, 0, 0, 0, 0);
	std::cout << "player 2" << std::endl;
	player p2(&stats, 0, 0, 0, 0, 0);
	std::cout << "enter number of games to be played" << std::endl;
	int nr_games;
	std::cin >> nr_games;

	int black_wins = 0, red_wins = 0;
	game_board game;
	int qb = 0, qr = 0, qg = 0;
	for (int i = 0; i < nr_games; i++) {
		p1.reset_temp_stats();
		p2.reset_temp_stats();
		game = root;
		int local_nr_moves_red =0, local_nr_moves_black = 0;
		int q = 0;
		//std::cout << "here" << std::endl;
		//man.print_board(game);
		while(!man.end_state(game, &p1.man.performed_game_states)) {
			game = p1.play(game);
			stats.number_moves_red++;
			local_nr_moves_red++;
			q++;
			qr++;
			//man.print_board(game);
			if (man.end_state(game, &p2.man.performed_game_states))
				{break; }
			else {
				game = p2.play(game);
				stats.number_moves_black++;
				local_nr_moves_black++;
				q++;
				qb++;
			}
			//man.print_board(game);
		}
		qg += q;
		if (local_nr_moves_black > stats.max_move_count_black) {
			stats.max_move_count_black = local_nr_moves_black;
			if (game.r_turn) stats.max_count_winning_black = true;
			else stats.max_count_winning_red = false;
		}
		if (local_nr_moves_red > stats.max_move_count_red) {
			stats.max_move_count_red = local_nr_moves_red;
			if (!game.r_turn) stats.max_count_winning_red = true;
			else stats.max_count_winning_red = false;
		}

		if (local_nr_moves_black < stats.min_move_count_black) {
			stats.min_move_count_black = local_nr_moves_black;
			if (game.r_turn) stats.min_count_winning_black = true;
			else stats.min_count_winning_black = false;
		}
		if (local_nr_moves_red < stats.min_move_count_red) {
			stats.min_move_count_red = local_nr_moves_red;
			if (!game.r_turn) stats.min_count_winning_red = true;
			else stats.min_count_winning_red = false;
		}
		if (game.r_turn) black_wins++;
		else red_wins++;
		std::cout << "red wins: " << red_wins <<"; black wins: " << black_wins << std::endl;
	}

//	std::cout << "tot r perf: " << qr/nr_games << "; tot b perf: " << qb/nr_games << "; tot g perf: " << qg/nr_games << std::endl;
//	std::cout<< std::endl <<"red wins: "<< red_wins <<"; black wins: "<< black_wins<<std::endl;

	stats.find_averages(nr_games);
	stats.print_statstistics();
	stats.print_stats_to_doc(p1.player_id, p2.player_id, red_wins, black_wins);
}

int main() {
	game();
	//gameMC_ABG();
	//gameABG();
	return 0;
}
