/*
 * Filename: Board.h
 * Author: Aaron Schraner
 * Date: April 12, 2015
 * Purpose: Board class for connect 4 program
 * CST 136
 */
#ifndef BOARD_H
#define BOARD_H
#define WIN 4 //want to play connect 5?

#include <iostream>
#include <iomanip>

class Board
{
	public:
		Board(int r, int c); //constructor (rows,columns)
		~Board(); //destructor
		void print(); //display board
		void clear(); //erase board
		bool place(int x, int y, char pc); //place a tile
		char p1; //player 1 (Human / X)
		char p2; //player 2 (Computer / O)
		bool won(int x, int y, char pc); //did this move win?
		int drop(int col, char pc); //drop a piece at specified column
		int getWidth() const; //return width
		int getHeight() const; //return height
		bool full(); //is the board full?
		friend class AI; //so AI can access board and relTo
	private:
		char** board;
		int height;
		int width;
		char relTo(int x, int y, int op, int d);
};


#endif
