/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */
 /*
//////////////////////////////////////////////////////////////////////
////////////////////////////////MONTE CARLO///////////////////////////
/////////////////////////////////////////////////////////////////////
game_board player::monte_carlo(game_board game) {
	std::list<game_move> moves = man.find_moves(game);
	//statistics
	if (this->player_id == 6 && game.r_turn) {
		stats->number_possible_moves_red += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_red) && (moves.size() > 0))
			stats->min_number_possible_moves_red = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_red)
			stats->max_number_possible_moves_red = moves.size();
	} else if (this->player_id == 6 && !game.r_turn) {
		stats->number_possible_moves_black += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_black) && (moves.size() > 0))
			stats->min_number_possible_moves_black = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_black)
			stats->max_number_possible_moves_black = moves.size();
	}//end statistics
	int red_max_win = -1, black_max_win = -1;
	game_move select;
	game_board new_game;
	for (auto& m : moves) {
		int local_red_win = 0, local_black_win = 0;
		for (int i = 0; i < this->monte_nr; i++) {
			new_game = man.apply_move(m, game);
			while(!man.end_state(new_game)) {
				new_game = random(new_game);
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
	//statistics
	if (this->player_id == 6) {
		if (select.x_old == -1 && game.r_turn) stats->number_spawn_moves_red++;
		else if (select.x_old == -1 && !game.r_turn) stats->number_spawn_moves_black++;
		if (man.attacking_move(game, select) && game.r_turn) stats->number_attack_moves_red++;
		else if (man.attacking_move(game, select) && !game.r_turn) stats->number_attack_moves_black++;
	}//end statistics
	return man.apply_move(select, game);
}

game_board player::monte_carloF(game_board game) {
	std::list<game_move> moves = man.find_moves(game);
	//statistics
	if (this->player_id == 7 && game.r_turn) {
		stats->number_possible_moves_red += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_red) && (moves.size() > 0))
			stats->min_number_possible_moves_red = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_red)
			stats->max_number_possible_moves_red = moves.size();
	} else if (this->player_id == 7 && !game.r_turn) {
		stats->number_possible_moves_black += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_black) && (moves.size() > 0))
			stats->min_number_possible_moves_black = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_black)
			stats->max_number_possible_moves_black = moves.size();
	}//end statistics
	int red_max_win = -1, black_max_win = -1;
	game_move select_monte_normal, select_monte_fast;
	select_monte_fast.x_new = -2; select_monte_fast.y_new = -2;
	game_board new_game;
	int min_depth = 100000;

	for (auto& m : moves) {
		int local_red_win = 0, local_black_win = 0;
		int local_nr_moves = 10000;
		bool global_turn = game.r_turn;
		for (int g = 0; g < this->monte_nr; g++) {
			new_game = man.apply_move(m, game);
			int nr_moves = 0;
			while(!man.end_state(new_game)) {
				new_game = random(new_game);
				nr_moves++;
			}
			if (new_game.r_turn) local_black_win++;
			else local_red_win++;
			if (new_game.r_turn != global_turn && nr_moves < local_nr_moves)
				local_nr_moves = nr_moves;
		}

		if(!game.r_turn && local_black_win > black_max_win) {
			select_monte_normal = m;
			black_max_win = local_black_win;
		} else if (game.r_turn && local_red_win > red_max_win) {
			red_max_win = local_red_win;
			select_monte_normal = m;
		}
		if (game.r_turn && 
				(local_red_win>=this->monte_nr*this->monte_threshold*0.01)) {
			if (local_nr_moves < min_depth) {
				select_monte_fast = m;
				min_depth = local_nr_moves;
			}
		}
		if (!game.r_turn && 
				(local_black_win>=this->monte_nr*this->monte_threshold*0.01)){
			if (local_nr_moves < min_depth){
				min_depth = local_nr_moves;
				select_monte_fast = m;
			}
		}
	}
	if (select_monte_fast.x_new > -2 && select_monte_fast.y_new > -2) {
		//statistics
		if (this->player_id == 7) {
			if (select_monte_fast.x_old == -1 && game.r_turn) stats->number_spawn_moves_red++;
			else if (select_monte_fast.x_old == -1 && !game.r_turn) stats->number_spawn_moves_black++;
			if (man.attacking_move(game, select_monte_fast) && game.r_turn) stats->number_attack_moves_red++;
			else if (man.attacking_move(game, select_monte_fast) && !game.r_turn) stats->number_attack_moves_black++;
		}//end statistics
		return man.apply_move(select_monte_fast, game);
	}
	//statistics
	if (this->player_id == 7) {
		if (select_monte_normal.x_old == -1 && game.r_turn) stats->number_spawn_moves_red++;
		else if (select_monte_normal.x_old == -1 && !game.r_turn) stats->number_spawn_moves_black++;
		if (man.attacking_move(game, select_monte_normal) && game.r_turn) stats->number_attack_moves_red++;
		else if (man.attacking_move(game, select_monte_normal) && !game.r_turn) stats->number_attack_moves_black++;
	}//end statistics

	return man.apply_move(select_monte_normal, game);
}

game_board player::monte_carloABG(game_board game) {
	std::list<game_move> moves = man.find_moves(game);
	//statistics
	if (this->player_id == 9 && game.r_turn) {
		stats->number_possible_moves_red += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_red) && (moves.size() > 0))
			stats->min_number_possible_moves_red = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_red)
			stats->max_number_possible_moves_red = moves.size();
	} else if (this->player_id == 9 && !game.r_turn) {
		stats->number_possible_moves_black += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_black) && (moves.size() > 0))
			stats->min_number_possible_moves_black = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_black)
			stats->max_number_possible_moves_black = moves.size();
	}//end statistics
	int red_max_win = -1, black_max_win = -1;
	game_move select;
	game_board new_game;
	for (auto& m : moves) {
		int local_red_win = 0, local_black_win = 0;
		for (int i = 0; i < this->monte_nr; i++) {
			new_game = man.apply_move(m, game);
			while(!man.end_state(new_game)) {
				new_game = randomG(new_game);
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
	//statistics
	if (this->player_id == 9) {
		if (select.x_old == -1 && game.r_turn) {
			stats->number_spawn_moves_red++;
		}
		else if (select.x_old == -1 && !game.r_turn) {
			stats->number_spawn_moves_black++;
		}
		if (man.attacking_move(game, select) && game.r_turn) {
			stats->number_attack_moves_red++;
		}
		else if (man.attacking_move(game, select) && !game.r_turn) {
			stats->number_attack_moves_black++;
		}
	}//end statistics

	return man.apply_move(select, game);
}

game_board player::monte_carlo1000(game_board game) {
	std::list<game_move> moves = man.find_moves(game);
	//statistics
	if (this->player_id == 10 && game.r_turn) {
		stats->number_possible_moves_red += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_red) && (moves.size() > 0))
			stats->min_number_possible_moves_red = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_red)
			stats->max_number_possible_moves_red = moves.size();
	} else if (this->player_id == 10 && !game.r_turn) {
		stats->number_possible_moves_black += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_black) && (moves.size() > 0))
			stats->min_number_possible_moves_black = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_black)
			stats->max_number_possible_moves_black = moves.size();
	}//end statistics
	int red_max_win = -1, black_max_win = -1;
	game_move select;
	game_board new_game;
	this->monte_nr = 1000/moves.size();
	for (auto& m : moves) {
		int local_red_win = 0, local_black_win = 0;
		for (int i = 0; i < this->monte_nr; i++) {
			new_game = man.apply_move(m, game);
			while(!man.end_state(new_game)) {
				new_game = random(new_game);
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
	//statistics
	if (this->player_id == 10) {
		if (select.x_old == -1 && game.r_turn) stats->number_spawn_moves_red++;
		else if (select.x_old == -1 && !game.r_turn) stats->number_spawn_moves_black++;
		if (man.attacking_move(game, select) && game.r_turn) stats->number_attack_moves_red++;
		else if (man.attacking_move(game, select) && !game.r_turn) stats->number_attack_moves_black++;
	}//end statistics
	return man.apply_move(select, game);
}

game_board player::negamax_select (game_board game) {
	std::list<game_move> moves = man.find_moves(game);//list move control
	if (moves.empty()) {
		return game;
	} //list move control
	//statistics
	if (this->player_id == 8 && game.r_turn) {
		stats->number_possible_moves_red += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_red) && (moves.size() > 0))
			stats->min_number_possible_moves_red = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_red)
			stats->max_number_possible_moves_red = moves.size();
	} else if (this->player_id == 8 && !game.r_turn) {
		stats->number_possible_moves_black += moves.size();
		if (((int)moves.size() < (int)stats->min_number_possible_moves_black) && (moves.size() > 0))
			stats->min_number_possible_moves_black = moves.size();
		else if ((int)moves.size() > (int)stats->max_number_possible_moves_black)
			stats->max_number_possible_moves_black = moves.size();
	}//end statistics
	tree_node node = negamax(game, this->negamax_search_depth);
	game_move select = node.move;
	bool reset_moves_list = false;//list move control
	//statistics
	if (this->player_id == 8) {
		if (select.x_old == -1 && game.r_turn) {
			stats->number_spawn_moves_red++;
			reset_moves_list = true; //list move control
		}
		else if (select.x_old == -1 && !game.r_turn) {
			stats->number_spawn_moves_black++;
			reset_moves_list = true;//list move conrol
		}
		if (man.attacking_move(game, select) && game.r_turn) {
			stats->number_attack_moves_red++;
			reset_moves_list = true;//list move control
		}
		else if (man.attacking_move(game, select) && !game.r_turn) {
			stats->number_attack_moves_black++;
			reset_moves_list = true;//list move control
		}
	}//end statistics
	if (reset_moves_list) man.clear_performed_moves();//list move control
	else man.add_to_performed_moves(select);//list move control
	return man.apply_move(select, game);
}

tree_node player::negamax(game_board game, int depth) {
	tree_node node;
	if (man.end_state(game) || depth == 0) {
		node.heuristiek = calc_heuristiek(game);
		return node;
	}
	node.heuristiek = -1000000;
	std::list<game_move> moves = man.find_moves(game);
	if (depth == this->negamax_search_depth)
		moves = man.check_performed_moves(moves);
	if (moves.empty()) {node.heuristiek = calc_heuristiek(game);
		return node;}
	for (auto& m : moves) {
		game_board new_game = man.apply_move(m, game);
		tree_node temp = negamax(new_game, depth - 1);
		if (-temp.heuristiek > node.heuristiek) {
			node.heuristiek = -temp.heuristiek;
			node.move = m;
		}
	}
	return node;
}

int player::calc_heuristiek (game_board game) {
	int value = 0;
	if (man.end_state(game)) return -100000;
	if (game.r_turn) {
		value += game.r_on * 3;
		value += game.r_off * 2;
		value -= game.b_on *5;
	} else {
		value += game.b_on * 3;
		value += game.b_off * 2;
		value -= game.r_on*5;
	}
	return value;
}
*/

game_board player::monte_carloABG(game_board game) {
	std::list<game_move> moves = man.find_moves(game);
	man.check_possible_moves(&moves, game, &man.performed_game_states);
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
	collect_stats_selected_move(this->player_id, 6, select, game, &man.performed_game_states);
	game = man.apply_move(select, game);
	man.add_to_performed_states(game, &man.performed_game_states);
	return game;
}



