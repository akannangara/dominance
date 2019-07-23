/*
 *Part of bachelor thesis Comparing Strategic Agents for Dominance by
 *Aaron Kannangara.
 *Supervided by Koster and van Rijn of the Leiden Institute of Advanced
 *Computer Science
 */
#include "game_board.h"
#include <list>
#include <cmath>

struct mcts_node {
	game_board game;
	int ni;
	int wi;
	double utc;
	std::list<mcts_node> children;
	mcts_node* parent;
	bool frontier;
	std::list<game_board> performed_game_states;
	
	
	std::list<game_board> p_performed;
};
