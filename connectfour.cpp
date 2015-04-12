/*
 * Filename: connectfour.cpp
 * Author: Aaron Schraner
 * Date: April 12, 2015
 * Purpose: connect 4 program implementation
 * CST 136
 */
#include <iostream>
#include <iomanip>

#include <stdlib.h>//
#include <time.h> // for rand()

#include "Board.h"
#include "AI.h"

//define LOGMOVES if you want to know who moved where at the end
#ifdef LOGMOVES
#include "Move.h"
#include <vector>
#endif

using namespace std;

void promptForSize(int& height, int& width)
{
	height=0;
	width=0;
	//initialize so we don't exit the loop due to garbage
	
	do
	{
		cout << "Enter the board height (must be greater than 3)\n> ";
		cin >> height;
	}
	while(height<4);

	do
	{
		cout << "Enter the board width (must be greater than 3)\n> ";
		cin >> width;
	}
	while(width<4);
	//prompt for and store width and height
}


int main()
{
#ifdef LOGMOVES
	cout << "Moves will be logged.\n";
#endif
	//size of board
	int height,width;

	//get size
	promptForSize(height,width);

	//create board
	Board board(height,width);

	cout << "Board created\n";

	int colToDrop; //column user wants to drop into
	bool cont=true; //continue

	AI myAI(&board); //create an AI 

	//if we are logging moves, make a vector to store them
#ifdef LOGMOVES
	vector<Move*> moves;
#endif	

	do
	{
		//user's turn
		board.print(); //print the board

		cout << "What column would you like to drop your piece into?\n> ";
		cin >> colToDrop;
		//prompt for and store desired column

		//we like to start at 0, not 1.
		colToDrop--;

		int res=board.drop(colToDrop, board.p1); //drop tile and store Y coordinate

		//log move if desired
#ifdef LOGMOVES
		moves.push_back(new Move(colToDrop, res, board.p1));
#endif

		//if that move won the game
		if(board.won(colToDrop, res, board.p1))
		{
			//say so and break
			cout << board.p1 << " wins!\n";
			cont=false;
			break;
		}

		if(board.full()) //if the board is full, break.
		{
			cout << "Board full! Nobody wins.\n";
			cont=false;
			break;
		}

		//if we're also logging the AI's moves
#ifdef LOGMOVES
		myAI.runAI(moves); //run the AI and log its moves
#else //otherwise
		myAI.runAI(); //just run the AI
#endif

		//if the AI just won
		if(myAI.justWon())
		{
			//say so and break
			cout << board.p2 << " wins!\n";
			cont=false;
			break;
		}


		//if the board is full, break.
		if(board.full())
		{
			cout << "Board full! Nobody wins.\n";
			cont=false;
			break;
		}


	} while(cont); 
	
	//when the game is over, print the final board.
	
	board.print();

	//and if desired, show all the game moves
#ifdef LOGMOVES
	cout << "Played with size " << width << "x" << height << endl;
	for(int i=0; i<moves.size(); i++)
	{
		moves[i]->print();
		delete moves[i];
	}
#endif

}

