/*
 * Filename: AI.cpp
 * Author: Aaron Schraner
 * Date: April 12, 2015
 * Purpose: Artificial Intelligence member functions for connect 4 program
 * CST 136
 */
#include "AI.h"
#include "Board.h"


//pick a spot and drop AI tile
void AI::runAI()
{
	//try to find one-move wins first
	if( (!SpecialAI(board->p2)) && (!SpecialAI(board->p1)))
		NormalAI();
		//if none are found, put a tile close to the last one

}

//log moves if desired
#ifdef LOGMOVES
void AI::runAI(std::vector<Move*> &v)
{
	runAI();
	v.push_back(new Move(lastX, lastY, board->p2));
}
#endif

//AI for cases where nobody can win in 1 move
void AI::NormalAI()
{
	//if this isn't the first move
	if(lastX>=0&&lastY>=0)
	{
		for(int i=travelDir;i<8;i++)
		{
			//try all directions adjacent to this tile, starting with
			//the last successful direction

			//if the spot I want is blank
			if(board->relTo(lastX, lastY, i, 1)==' ')
			{
				//put a tile there and save the coordinates
				lastX+=rtX[i];
				lastY=board->drop(lastX, board->p2);

				//save the direction
				travelDir=i;

				//exit the function
				return;
			}
		}
	}
	//if a successful match wasn't found
	{

		do
		{
			//put it somewhere random, keep trying until either success
			//or board fills up
			
			srand(time(NULL)-randoff);
			randoff++;
			
			lastX = rand() % ( board->getWidth() );

		} while(
				(lastY=board->drop(lastX, board->p2)) == -1 && //repeat if placing fails
				!board->full() ); //break if board is full
	}
}


//AI for cases in which <player> can win in one move
bool AI::SpecialAI(char player)
{
	Board bcopy(board->getHeight(), board->getWidth());
	//create another board
	
	//iterate through all columns
	for(int x=0; x<board->getWidth(); x++)
	{
		for(int a=0; a<board->getWidth(); a++)
			for(int b=0; b<board->getHeight(); b++)
				bcopy.board[b][a]=board->board[b][a];
				//copy the original board into the new one

		int z=bcopy.drop(x,player); //try placing a tile in column i

		if(bcopy.won(x,z,player)) //if that beat the game
		{
			board->drop(x,board->p2); //put my piece there
			lastX=x;
			lastY=z; //and save the coords
			return true; //and exit
		}
		bcopy.clear();
	}
	return false; //if nothing beat the game in one move, return false
}

//did the AI just win?
bool AI::justWon()
{
	return board->won(lastX, lastY, board->p2);
}
