/*
 * Filename: Board.cpp
 * Author: Aaron Schraner
 * Date: April 12, 2015
 * Purpose: Board member functions for connect 4 program
 * CST 136
 */
#include <iostream>
#include "Board.h"

using std::cout;
using std::endl;
using std::setw;
using std::left;

void Board::print()
{
	//print number heading 1-width
	for(int x=0;x<width;x++)
		cout << "| " << setw(2) << left << x+1;
	cout << "|" << endl;

	//print divider line
	for(int x=0;x<width;x++)
		cout << "----";
	cout << "-\n";

	//print each row
	for(int y=0;y<height;y++)
	{
		cout  << "| ";
		for(int x=0;x<width;x++)
			cout << board[y][x] << " | ";
		cout << "\n";
		for(int x=0;x<width;x++)
			cout << "----";
		cout << "-\n";
	}
}

void Board::clear()
{
	for(int y=0;y<height;y++)
		for(int x=0;x<width;x++)
			board[y][x]=' ';
	//reset entire board to spaces
}

Board::Board(int r, int c):height(r),width(c)
{
	//allocate board
	board  = new char* [height];
	for(int i = 0; i < height; i++)
		board[i]=new char [width];
	clear();
	p1='X';
	p2='O';
	//access board with board[Y][X] for coordinate (X,Y)
}

Board::~Board()
{
	//de-allocate board
	for(int i=0; i<height; i++)
		delete[] board[i];
	delete board;
}

bool Board::place(int x, int y, char pc)
{
	//attempt to place a tile at given coordinates
	if(board[y][x]==' ')
	{
		board[y][x]=pc;
		return true;
	}
	return false;
}

//returns the character relative to a point [x,y] in direction [op] 
//that is [d] steps away (d=0 returns board[y][x])
char Board::relTo(int x, int y, int op, int d)
{
	// |  op directions 
	//\|/
	//0 1 2
	//3 X 4
	//5 6 7
	
	if(x<0||y<0||x>=width||y>=height)
		return 0;
	//if it's out of range, do nothing and fail
	
	if(d<0)
	{
		//if distance is negative, make it positive and flip direction
		op=(op+4)%4;
		d=-d;
	}
	if(op>3)
	{
		//if op>3, use mathemagics to make it between 0 and 3
		op=op%4;
		d=-d;
	}

	if(d==0)
		return board[y][x]; //if distance is 0

	switch(op)
	{
		case 0: //up and left
			if( y-d >= 0 && y-d < height && x-d >= 0 && x-d < width )
				return board[y-d][x-d];
			return 0;
		case 1: //up and center
			if(y-d>=0&&y-d<height)
				return board[y-d][x];
			return 0;
		case 2: //up and right
			if( y-d >= 0 && y-d < height && x+d >= 0 && x+d < width )
				return board[y-d][x+d];
			return 0;
		case 3: //center and left
			if(x-d>=0&&x-d<width)
				return board[y][x-d];
			return 0;
	}
}

bool Board::won(int x, int y, char pc)
{
	int depth=0;
	int inDir[4]={0}; //how many pieces in a row:
	//0: diagonally TL->BR
	//1: vertically
	//2: diagonally TR->BL
	//3: horizontally
	
	//first iterate through all 8 adjacent tiles
	for(int i=0; i<8; i++)
		//add the number of adjacent pieces in some direction
		//to the proper inDir direction
		for(int d=1;(d<WIN)&&(relTo(x,y,i,d)==pc);d++)
			inDir[i%4]++;

	//if some direction has more or greater than WIN-1 (usually 3) tiles, we have won
	for(int i=0;i<4;i++)
		if(inDir[i]>=WIN-1)
			return true;

	return false;
	//otherwise, we have not.
}

//drop a piece in some column
int Board::drop(int col, char pc)
{
	//if the column is full, fail.
	if(board[0][col]!=' ')
		return -1;

	int i;
	for(i=0;i<height&&board[i][col]==' ';i++);
	board[--i][col]=pc; //otherwise put (pc) in the lowest empty spot
	return i; 

	// ---IMPORTANT---
	//returns the Y coordinate of where the tile was placed
}

int Board::getHeight() const
{
	return height;
}

int Board::getWidth() const
{
	return width;
}

//is the board full?
bool Board::full()
{
	for(int x=0; x<width; x++)
		for(int y=0;y<height;y++)
			if(board[y][x]==' ')
				return false;
				//if any blank spaces are found, it can't be full
	return true; //if none are found, it is full.
}
