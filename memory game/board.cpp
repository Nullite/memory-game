#include "board.h"

std::string board()
{
	std::string temp = "+-----+-----+-----+-----+\n+     +     +     +     +\n+     +     +     +     +\n+     +     +     +     +\n";
	std::string board;
	for (size_t i = 0; i < 4; i++)
	{
		board += temp;
	}
	board += "+-----+-----+-----+-----+\n";
	return board;
}

void fillBoard(std::string& board, std::vector<int>& squares, std::vector<char> pics)
{
	std::vector<char> picsCopy = pics;
	int temp = 0;
	int rnd;
	while (pics.size() || picsCopy.size())
	{
		if (!pics.size())
		{
			int random = rand() % picsCopy.size();
			board[squares[temp++]] = picsCopy[random];
			picsCopy.erase(picsCopy.begin() + random);
			continue;
		}
		if (!picsCopy.size())
		{
			int random = rand() % pics.size();
			board[squares[temp++]] = pics[random];
			pics.erase(pics.begin() + random);
			continue;
		}

		rnd = rand() % 2;
		if (!rnd)
		{
			int random = rand() % pics.size();
			board[squares[temp++]] = pics[random];
			pics.erase(pics.begin() + random);
			continue;
		}
		else
		{
			int random = rand() % picsCopy.size();
			board[squares[temp++]] = picsCopy[random];
			picsCopy.erase(picsCopy.begin() + random);
			continue;
		}
		
	}
	
}
