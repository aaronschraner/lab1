/*
 * Filename: Move.h (optional for connect4)
 * Author: Aaron Schraner
 * Date: April 12, 2015
 * Purpose: Move class for connect 4 program move logging (useful for contests)
 * CST 136
 */
#ifndef MOVE_H
#define MOVE_H
#include <iostream>

using std::cout;
using std::endl;

//Move class
//for keeping track of player and computer moves
class Move
{
	private:
		int x,y;
		char piece;
	public:
		Move(int X, int Y, char P): x(X), y(Y), piece(P) {}
		//construct move

		//display move
		void print()
		{
			cout << "[" << piece << "] (" << x << ", " << y << ")" << endl;
		}
};


#endif
