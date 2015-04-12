/*
 * Filename: AI.h
 * Author: Aaron Schraner
 * Date: April 12, 2015
 * Purpose: Artificial intelligence (solver)
 * 	class definition for connect 4 program
 * CST 136
 */
#ifndef AI_H
#define AI_H
#include "Board.h"

//for logging moves
#ifdef LOGMOVES
#include "Move.h"
#include <vector>
#endif

class AI
{
	private:
		Board* board; //board to operate on
		int lastX, lastY; //hold last move
		const int8_t rtX[8]; 
		int randoff; //used to change random seed in less than clock resolution
		int travelDir; //keep track of travel direction
	public:
		AI(Board *b): 	board(b), //set board
				rtX{-1,0,1,-1,1,-1,0,1}, //init rtX
				travelDir(0) {}; //set initial travel direction to left
		void runAI(); //run AI on board

#ifdef LOGMOVES
		void runAI(std::vector<Move*> &v); //run AI on board and log move
#endif

		void NormalAI(); //AI when no one-move wins exist
		bool SpecialAI(char player); //AI when game can be won or saved in one move
		bool justWon(); //did I just win?
};
#endif
