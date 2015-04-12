CC=g++
CFLAGS=-std=c++11 -DLOGMOVES

default:Connect4

Connect4:connectfour.cpp Board.h Board.cpp AI.h AI.cpp
	$(CC) $(CFLAGS) -o Connect4 connectfour.cpp Board.cpp AI.cpp

run:Connect4
	./Connect4

clean:
	rm Connect4 
