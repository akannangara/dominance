/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */
 
#include "player.h"


player::player(statistics* stats_holder, int q_id, int q_a, int q_b, int q_g, int q_d) {
	stats = stats_holder;
	reset_temp_stats();
	srand(time(NULL));
	if (q_id == 0) {
		std::cout << "Please select player type" << std::endl;
		std::cout << "1. human"<< std::endl;
		std::cout << "2. puur random" << std::endl;
		std::cout << "5. general random" << std::endl;
		std::cout << "6. monte carlo" << std::endl;
		std::cout << "8. negamax" << std::endl;
		std::cout << "9. monte carlo with ABG"<< std::endl;
		std::cout << "10. monte carlo 1000" << std::endl;
		std::cout << "11. mcts" << std::endl;
		int id;
		std::cin >> id;
		switch (id) {
			case 1: player_id = 1; break;
			case 2: player_id = 2; break;
			case 5: player_id = 5;
					std::cout << "enter alpha (attack): " << std::endl; std::cin>>alpha;
					std::cout << "enter beta (spawn): " << std::endl; std::cin>>beta;
					std::cout << "enter gamma (movement): " << std::endl; std::cin>>gamma;
					break;
			case 6: std::cout << "select nr of game search for monte" << std::endl;
					std::cin >> monte_nr;
					player_id = 6; break;
			case 8: std::cout << "enter search depth for negamax" << std::endl;
					std::cin >> negamax_search_depth;
					player_id = 8; break;
			case 9: player_id = 9;
					std::cout << "enter alpha (attack): " << std::endl; std::cin>>alpha;
					std::cout << "enter beta (spawn): " << std::endl; std::cin>>beta;
					std::cout << "enter gamma (movement): " << std::endl; std::cin>>gamma;
					std::cout << "select nr of game search for monte" << std::endl;
					std::cin >> monte_nr; break;
			case 10: player_id = 10;
					monte_nr = 0; break;

			case 11: player_id = 11;
					std::cout << "enter monte nr:"<<std::endl;	
					std::cin >> mcts_nr;
					std::cout << "enter value c: " << std::endl;
					std::cin >> value_c;
					//value_c = sqrt(2);
					//negamax_search_depth = 3;
					break;

			default: return;
		}
	} else {
		player_id = q_id;
		switch(player_id) {
			case 2: break;
			case 5:
			case 6:
			case 9:
				alpha = q_a;
				beta = q_b;
				gamma = q_g;
				monte_nr = q_d;
				break;
			case 8:
				negamax_search_depth = q_d;
				break;
			case 11:
				//monte_nr = 10;
				//mcts_nr = 1600;
				//negamax_search_depth = 3;
				mcts_nr = 1800;
				value_c = 0.2;
				mcts_d = (q_d + 1)*2;
				//define_c (q_d);
				alpha = q_a;
				beta = q_b;
				gamma = q_g;
				break;
			default:
				std::cout << "error, no player entered" << std::endl;
				exit(1); break;
		}
	}
}

void player::define_c (int o) {
	if (o == 0) value_c = 0.1;//0.1;
	else if (o == 1) value_c = 0.2;//0.2;
	else if (o == 2) value_c = 0.3;//0.3;
	else if (o == 3) value_c = 0.4;//0.4;
	else if (o == 4) value_c = 0.5;//0.5;
	else if (o == 5) value_c = 0.6;//0.6;
	else if (o == 6) value_c = 0.7;//0.7;
	else if (o == 7) value_c = 0.8;//0.8;
	else if (o == 8) value_c = 0.9;//0.9;
	else if (o == 9) value_c = 1.0;//1.0;
	else if (o == 10) value_c = 1.1;//1.1;
	else if (o == 11) value_c = 1.2;//1.2;
	else if (o == 12) value_c = 1.3;//1.3;
	else if (o == 13) value_c = 1.4;//1.4;
	else if (o == 14) value_c = 1.5;//1.5;
	else if (o == 15) value_c = 1.6;//1.6;
	else if (o == 16) value_c = 1.7;//1.7;
	else if (o == 17) value_c = 1.8;//1.8;
	else if (o == 18) value_c = 1.9;//1.9;for our Monte Carlo agents
	else if (o == 19) value_c = 2.0;//2.0;
	else if (o == 20) mcts_nr = 3250;//0.01;
	else if (o == 21) mcts_nr = 3500;//0.01;
	else if (o == 22) mcts_nr = 3750;//0.01;
	else if (o == 23) mcts_nr = 4000;//0.01;
}

game_board player::play(game_board game) {
	switch (this->player_id) {
		case 1: game = human(game, &man.performed_game_states); break;
		case 2: game = random(game, &man.performed_game_states); break;
		case 5: game = randomG(game, &man.performed_game_states); break;
		case 6: game = monte_carlo(game, &man.performed_game_states); break;
//		case 7: game = monte_carloF(game); break;
		case 8: game = negamax_select(game, &man.performed_game_states); break;
		case 9: game = monte_carloABG(game, &man.performed_game_states); break;
//		case 10: game = monte_carlo1000(game); break;*/
		case 11: game = mcts_select (game, &man.performed_game_states);
				//exit(1);
				break;

		default: break;
	}
	return game;
}

void player::reset_temp_stats() {
	temp_nr_possible_moves = 0;
	temp_number_spawn_moves = 0;
	temp_number_attack_moves = 0;
}

void player::collect_stats_selected_move(int p_id, int a_id, game_move m,
				game_board g, std::list<game_board>* performed) {
	bool reset_moves_list = false;
	if (p_id == a_id) {
		if (m.x_old == -1 && g.r_turn) {
			stats->number_spawn_moves_red++;
			temp_number_spawn_moves++;
			reset_moves_list = true;
		}
		else if (m.x_old == -1 && !g.r_turn) {
			stats->number_spawn_moves_black++;
			temp_number_spawn_moves++;
			reset_moves_list = true;
		}
		if (man.attacking_move(g, m) && g.r_turn) {
			stats->number_attack_moves_red++;
			temp_number_attack_moves++;
			reset_moves_list = true;
		}
		else if (man.attacking_move(g, m) && !g.r_turn) {
			stats->number_attack_moves_black++;
			temp_number_attack_moves++;
			reset_moves_list = true;
		}
	}
	if (reset_moves_list) man.clear_performed_states(performed);
}

void player::copy_performed_list(std::list<game_board>* src,
				std::list<game_board>* dst) {
	for (std::list<game_board>::iterator it = src->begin(); it!= src->end(); it++) {
		dst->push_back(*it);
	}
}

////////////////////////////////////////////////////////////
////////////////////RANDOM AGENTS//////////////////////////
///////////////////////////////////////////////////////////
game_board player::random(game_board game,
				std::list<game_board>*performed) {
	std::list<game_move> moves = man.find_moves(game);
	man.check_possible_moves(&moves, game, performed);
	game_move select;
	if (moves.empty()) {
		return game;
	} //list move control
	int counter = rand() % moves.size();
	//stats collection
	stats->add_move_size(this->player_id, 2, moves.size(), game.r_turn);
	temp_nr_possible_moves += moves.size();
	for (auto& m : moves) {
		if (counter == 0) select = m;
		counter--;
	}
	collect_stats_selected_move(this->player_id, 2, select, game, performed);
	game = man.apply_move(select, game);
	man.add_to_performed_states(game, performed);
	return game;
}

game_board player::randomG(game_board game,
										std::list<game_board>* performed) {
	game_move select;
	std::list<game_move> moves = man.find_moves(game);
	man.check_possible_moves(&moves, game, performed);
	if (moves.empty()) {
		return game;
	}
	stats->add_move_size(this->player_id, 5, moves.size(), game.r_turn);
	temp_nr_possible_moves += moves.size();
	std::list<game_move> attack, spawn, movement;
	for (auto& m : moves) {
		if (m.x_old == -1) {
			spawn.push_back(m);
			if (man.attacking_move(game, m)) {
				attack.push_back(m);
			}
		} else {
			movement.push_back(m);
			if (man.attacking_move(game, m)) {
				attack.push_back(m);
			}
		}
	}
	moves.clear();
	int counter;
	if (!attack.empty() && !spawn.empty() && !movement.empty()) {
		if (alpha+beta+gamma < 1) {alpha1 = 1; beta1 = 1; gamma1=1;}
		else {alpha1 = alpha; beta1 = beta; gamma1 = gamma;}
		counter = rand() % (alpha1+beta1+gamma1);
		if (counter < alpha1) {
			select = select_random_from_list(attack);
		} else if (counter < alpha1+beta1) {select = select_random_from_list(spawn);}
		else select = select_random_from_list(spawn);
	}
	else if (attack.empty() && !spawn.empty() && !movement.empty()) {
		alpha1 = 0; beta1 = beta; gamma1 = gamma;
		select = select_random_list(spawn, movement, beta1, gamma1);
	} else if (!attack.empty() && spawn.empty() && !movement.empty()) {
		beta1 = 0; alpha1 = alpha; gamma1 = gamma;
		select = select_random_list (attack, movement, alpha1, gamma1);
	} else if (!attack.empty() && !spawn.empty() && movement.empty()) {
		gamma1 = 0; alpha1 = alpha; beta1 = beta;
		select = select_random_list(attack, spawn, alpha1, beta1);
	}
	else if (!attack.empty() && spawn.empty() && movement.empty()) {
		beta1 = 0; gamma1 = 0; alpha1 = alpha;
		select = select_random_from_list (attack);
	} else if (attack.empty() && !spawn.empty() && movement.empty()) {
		alpha1 = 0; gamma1 = 0; beta1 = beta;
		select = select_random_from_list (spawn);
	} else if (attack.empty() && spawn.empty() && !movement.empty()) {
		alpha1 = 0; beta1 = 0; gamma1 = gamma;
		select = select_random_from_list (movement);
	}
	else {
		std::cout << "error in selecting move random general" << std::endl;
		man.print_board(game);
		exit(1);
	}
	collect_stats_selected_move(this->player_id, 5, select, game,
								performed);
	game = man.apply_move(select, game);
	man.add_to_performed_states(game, performed);
	return game;
}

game_move player::select_random_from_list (std::list<game_move> moves) {
	int counter = rand()% moves.size();
	for (auto& m : moves) {
		if (counter == 0) {
			return m;
		}
		counter--;
	}
	game_move select;
	std::cout << "error in choosing move from random list" << std::endl;
	exit(1);
	return select;
}


game_move player::select_random_list(std::list<game_move> l1,
																		std::list<game_move>l2,
																		int v_l1, int v_l2) {
	int s1 = v_l1;
	if (v_l1 + v_l2 == 0) {v_l1 = 1; v_l2 = 1; s1 = 1;}
	int counter = rand() % (v_l1 + v_l2);
	if (counter < s1) {
		if (l1.empty()) return select_random_from_list(l2);
		else return select_random_from_list(l1);
	}
	else {
		if (l2.empty()) return select_random_from_list(l1);
		else return select_random_from_list(l2);
	}
	game_move select;
	std::cout << "error in choosing list from random lists" << std::endl;
	exit(1);
	return select;
}
/////////////////////////////END RANDOM MOVES////////////////////




game_board player::human(game_board game,
										std::list<game_board>* performed) {
	std::list<game_move> moves = man.find_moves(game);
	man.check_possible_moves(&moves, game, performed);
	temp_nr_possible_moves += moves.size();
	stats->add_move_size(this->player_id, 1, moves.size(), game.r_turn);
	std::cout << "please select move" << std::endl;
	int count = 0;
	if (moves.size() == 0) return game;
	for (auto& m : moves) {
		count++;
		std::cout << count << " ";
		man.print_move(m);
	}
	std::cout << std::endl << "select: " << std::endl;
	int i; std::cin >> i;
	game_move select;
	for (auto& m : moves) {
		if (i == 1) select = m;
		i--;
	}
	collect_stats_selected_move(this->player_id, 1, select, game,
								performed);
	game = man.apply_move(select, game);
	man.add_to_performed_states(game, performed);
	return game;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////MONTE CARLO/////////////////////////
//////////////////////////////////////////////////////////////////
game_board player::monte_carlo(game_board game, std::list<game_board>* performed) {
	std::list<game_move> moves = man.find_moves(game);
	man.check_possible_moves(&moves, game, performed);
	temp_nr_possible_moves += moves.size();
	stats->add_move_size(this->player_id, 6, moves.size(), game.r_turn);
	if (moves.size() == 0) return game;
	int red_max_win = -1, black_max_win = -1;
	game_move select;
	game_board new_game;
	for (auto& m : moves) {
		int local_red_win = 0, local_black_win = 0;
		for (int i = 0; i < this->monte_nr; i++) {
			std::list<game_board> performed;
			copy_performed_list(&man.performed_game_states, &performed);
			new_game = man.apply_move(m, game);
			while(!man.end_state(new_game, &performed)) {
				new_game = random(new_game, &performed);
			}
			if (new_game.r_turn) local_black_win++;
			else local_red_win++;
		}
		if(!game.r_turn && local_black_win > black_max_win) {
			select = m;
			black_max_win = local_black_win;
		} else if (game.r_turn && local_red_win > red_max_win) {
			red_max_win = local_red_win;
			select = m;
		}
	}
	collect_stats_selected_move(this->player_id, 6, select, game,
															performed);
	game = man.apply_move(select, game);
	man.add_to_performed_states(game, performed);
	return game;
}

game_board player::monte_carloABG(game_board game, std::list<game_board>* performed) {
	std::list<game_move> moves = man.find_moves(game);
	man.check_possible_moves(&moves, game, performed);
	if (moves.empty()) return game;
	temp_nr_possible_moves += moves.size();
	stats->add_move_size(this->player_id, 9, moves.size(), game.r_turn);
	int red_max_win = -1, black_max_win = -1;
	game_move select;
	game_board new_game;
	for (auto& m : moves) {
		int local_red_win = 0, local_black_win = 0;
		for (int i = 0; i < this->monte_nr; i++) {
			new_game = man.apply_move(m, game);
			std::list<game_board> performed;
			copy_performed_list(&man.performed_game_states, &performed);
			while(!man.end_state(new_game, &performed)) {
				new_game = randomG(new_game, &performed);
			}
			if (new_game.r_turn) local_black_win++;
			else local_red_win++;
		}
		if(!game.r_turn && local_black_win > black_max_win) {
			select = m;
			black_max_win = local_black_win;
		} else if (game.r_turn && local_red_win > red_max_win) {
			red_max_win = local_red_win;
			select = m;
		}
	}
	collect_stats_selected_move(this->player_id, 9, select, game, performed);
	game = man.apply_move(select, game);
	man.add_to_performed_states(game, performed);
	return game;
}
////////////////////////////////END MONTE CARLO//////////////////







//////////////////////////////////////////////////////////////////////
///////////////////////////NEGAMAX PLAYER////////////////////////////
////////////////////////////////////////////////////////////////////
game_board player::negamax_select (game_board game, std::list<game_board>* performed) {
	std::list<game_move> moves = man.find_moves(game);
	man.check_possible_moves(&moves, game, performed);
	if (moves.empty()) {
		return game;
	} //list move control
	temp_nr_possible_moves += moves.size();
	stats->add_move_size(this->player_id, 8, moves.size(), game.r_turn);
	tree_node node = negamax(game, this->negamax_search_depth,
		&man.performed_game_states);
	game_move select = node.move;
	collect_stats_selected_move(this->player_id, 8, select, game, performed);
	game = man.apply_move(select, game);
	man.add_to_performed_states(game, performed);
	return game;
}

tree_node player::negamax(game_board game, int depth,
								std::list<game_board>* s_list) {
	tree_node node;
	if (man.end_state(game, s_list) || depth == 0) {
		node.heuristiek = calc_heuristiek(game, s_list);
		return node;
	}
	node.heuristiek = -1000000;
	std::list<game_move> moves = man.find_moves(game);
	man.check_possible_moves(&moves, game, s_list);
//	if (depth == this->negamax_search_depth)
//		moves = man.check_performed_moves(moves);
	if (moves.empty()) {node.heuristiek = calc_heuristiek(game,s_list);
		return node;}
	for (auto& m : moves) {
		std::list<game_board> new_performed;
		copy_performed_list(s_list, &new_performed);
		if (m.x_old == -1 || man.attacking_move(game, m))
			man.clear_performed_states(&new_performed);
		game_board new_game = man.apply_move(m, game);
		man.add_to_performed_states(new_game, &new_performed);
		tree_node temp = negamax(new_game, depth - 1, &new_performed);
		if (-temp.heuristiek > node.heuristiek) {
			node.heuristiek = -temp.heuristiek;
			node.move = m;
		}
	}
	return node;
}

int player::calc_heuristiek (game_board game, std::list<game_board>* s_list) {
	int value = 0;
	if (man.end_state(game, s_list)) return -100000;
	if (game.r_turn) {
		value += game.r_on * 3;
		value += game.r_off;//*2
		value -= game.b_on *5;
	} else {
		value += game.b_on * 3;
		value += game.b_off;//*2
		value -= game.r_on*5;
	}
	return value;
}






/////////////////////////////////////////////////////////////////////////
///////////////////////////////MCTS/////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void player::calc_UTC(mcts_node* node) {
	node->utc =
		((double)node->wi/(double)node->ni)+(double)value_c*sqrt(log((double)mcts_Ni)/(((double)node->ni)));
}

void player::print_mcts(mcts_node node, int depth) {
	std::cout << "d:"<<depth<<"; wi:"<<node.wi<<"; ni:"<<node.ni<< " " << node.utc <<std::endl;
	man.print_board(node.game);
	if (!node.frontier) {
		for (auto& c : node.children) {
			if (depth > 0) break; //TODO REMOVE
			print_mcts(c, depth+1);
		}
	}
}

void player::fill_child_list(mcts_node* node) {
	std::list<game_move> moves = man.find_moves(node->game);
	man.check_possible_moves(&moves, node->game, &node->performed_game_states);
	for (auto& m : moves) {
		game_board temp = man.apply_move(m, node->game);
		mcts_node temp_n = make_node(temp, node);
		node->children.push_back(temp_n);
		copy_performed_list(&temp_n.performed_game_states,
												&node->performed_game_states);
		man.add_to_performed_states (temp, &temp_n.performed_game_states);
	}
}

mcts_node player::make_node (game_board game, mcts_node* p) {
	mcts_node node;
	node.game = game;
	node.ni = 0;
	node.wi = 0;
	node.utc = 100000;
	node.frontier = true;
	node.parent = p;
	return node;for our Monte Carlo agents
}

//goes down mcts tree till frontier is reached
//returns pointer to the leaf node that should be expanded
mcts_node* player::selection(mcts_node* node) {
	//std::cout << "in selection" << std::endl;
	mcts_node* select = NULL;
	if (node->frontier || man.end_state(node->game, &node->performed_game_states)) {
		select = node;
	} else { //node is not a frontier/leaf node
		double utc_select = -1000;//max utc value
		std::list<mcts_node*> select_options;
		for (auto& c : node->children) {
			if (c.ni>0) calc_UTC(&c);
			if ((double)c.utc == utc_select) {
				select_options.push_back(&c);
			}	else if ((double)(c.utc) > utc_select) {//selecting move which maximizes my win rate
				utc_select = (double)c.utc;
				select_options.clear();
				select_options.push_back(&c);
			}
		}
		int random = 0;
		if (select_options.size() > 1) random = rand() % select_options.size();
		else if (select_options.size() == 1) random = 0;
		else {select = node;}
		for (auto& s : select_options) {
			if (random == 0) {
				select = selection(s);
				break;
			}
			random--;
		}
	}
	return select;
}

//expands the node given as argument. child list is
//filled and a rondom child is given to perform
//a simulation with
mcts_node* player::expansion(mcts_node* node) {
	//std::cout << "in expansion" << std::endl;
	mcts_node* select = NULL;
	if (man.end_state(node->game, &node->performed_game_states))
		select = node;
	else if (node->children.empty()) fill_child_list(node);
	//node->frontier = false;
	if (node->children.empty()) select = node;
	if (select != NULL) return select;
	int random = rand() % node->children.size();
	for (auto& c : node->children) {
		if (random == 0) {
			select = &c;
			break;
		}
		random--;
	}
	return select;
}

bool player::simulation(mcts_node* node) {
	//std::cout << "in simulation" << std::endl;
	game_board game = node->game;
	bool p_turn = node->game.r_turn;
	int counter = 0;
	while(!man.end_state(game, &node->performed_game_states)) {
		game = randomG(game, &node->performed_game_states);
		counter++;
		if (counter == mcts_d) break;
	}
	if (man.end_state(game, &node->performed_game_states)) {
		if (game.r_turn == p_turn) {
			return false;
		} else return true;
	} else {
		if (calc_heuristiek (game, &node->performed_game_states) > 0 &&
				game.r_turn == p_turn) {
			return true;
		} else if (
				calc_heuristiek (game, &node->performed_game_states) > 0 &&
				game.r_turn != p_turn) {
			return false;
		} else if (
				calc_heuristiek (game, &node->performed_game_states) <= 0 &&
				game.r_turn == p_turn) {
			return false;
		} else if (
				calc_heuristiek (game, &node->performed_game_states) <= 0 &&
				game.r_turn != p_turn) {
			return true;
		}
	}
	std::cout << "error in simulation" << std::endl;
	exit(1);
	return 1;
}

void player::backpropogate (bool won, mcts_node* node) {
	//std::cout << "in backpropogate" << std::endl;
	node->ni++;
	if (won) node->wi++;
	calc_UTC(node);
	if (node->parent != NULL) backpropogate (!won, node->parent);
}

void player::mcts_play(mcts_node* node) {
	for (int i = 0; i < mcts_nr; i++) {
		//std::cout << "play called " << std::endl;
		mcts_node* to_play = selection(node);
		if (to_play == node) backpropogate(true, to_play);
		if (man.end_state(to_play->game, &to_play->performed_game_states)) {
			backpropogate(true, to_play);
			continue;
		}
		to_play->frontier = false;
		mcts_node* new_to_play = expansion (to_play);
		if (new_to_play == to_play) {backpropogate(true, to_play); continue;}
		to_play = new_to_play;
		if (man.end_state(to_play->game, &to_play->performed_game_states)) {
			backpropogate(true, to_play);
			continue;
		}
		bool won = simulation(to_play);
		backpropogate(!won, to_play);
		mcts_Ni++;
	}
}

game_board player::to_return_game_board(mcts_node* node) {
	float w_rate = -1000;
	mcts_node* select = NULL;
	for (auto& c : node->children) {
		if (c.ni == 0) continue;
		if (((float)c.wi/(float)c.ni) > w_rate) {
			//std::cout << "select" << std::endl;
			select = &c;
			w_rate = (float)((float)c.wi/(float)c.ni);
		}
	}
	//man.print_board(select->game);
	return select->game;
}

game_move player::convert_to_game_move(game_board game, game_board new_game) {
	std::list<game_move> moves = man.find_moves(game);
	game_move to_return;
	to_return.x_old = -100;
	for (auto& m : moves) {
		game_board temp = man.apply_move(m, game);
		if (man.same_board_state(temp, new_game)) to_return = m;
	}
	if (to_return.x_old == -100) {
		std::cout <<"error in conversion to find game_move" << std::endl;
		exit(1);
	}
	return to_return;
}

game_board player::mcts_select(game_board game, std::list<game_board>* s_list) {

	mcts_node root = make_node(game, NULL);
	copy_performed_list(&root.performed_game_states,
											s_list);

	//print_mcts(root, 0);
	mcts_play(&root);
	//print_mcts(root, 0);
	//stats collection
	//std::cout << "h1" << std::endl;
	stats->add_move_size(this->player_id, 11, root.children.size(), game.r_turn);
	temp_nr_possible_moves += root.children.size();
	//std::cout << "h5" << std::endl;
	game_board select_game = to_return_game_board(&root);

	//std::cout << "h3" << std::endl;

	//man.print_board(select_game);
	//man.print_board(game);
	//exit(1);
	game_move select_move = convert_to_game_move(game, select_game);
	//std::cout << "h4" << std::endl;
	collect_stats_selected_move(this->player_id, 11, select_move, game, s_list);

	man.add_to_performed_states(select_game, s_list);
	//std::cout << "h2" << std::endl;
	return select_game;
}

