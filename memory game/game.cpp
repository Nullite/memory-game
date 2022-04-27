#include "game.h"

int getSquare(std::vector<int> squares, std::string board, std::vector<int>& repeats)
{
	int square = 0;
	std::string temp;
	while (!square)
	{
		system("cls");
		std::cout << board;
		std::cout << "Enter square number (from 1 to 16)\n";
		std::getline(std::cin, temp);
		try
		{
			square = std::stoi(temp);
		}
		catch (std::exception&)
		{
			square = 0;
		}
		if (square > 0 && square < 17)
		{
			for (size_t i = 0; i < repeats.size(); i++)
			{
				if (repeats[i] == square)
				{
					square = 0;
					break;
				}
			}
		}
		else
		square = 0;
	}
	repeats.push_back(square);
	return squares[square - 1];
}

char showChoosedSquare(std::string& board, std::string& emptyBoard, int square)
{
	system("cls");
	char smb = board.at(square);
	emptyBoard.replace(square, 1, 1, smb);
	std::cout << emptyBoard;
	return smb;
}

bool record(int count, int& temp)
{
	
	
	std::ifstream file("record.mg");
	if (!file.is_open())
	{
		std::ofstream createIfNoFile("record.mg");
		createIfNoFile.close();
		std::ifstream file("record.mg");
	}
	file >> temp;
	if (!temp || count < temp)
	{
		file.close();
		std::ofstream rewrite("record.mg");
		rewrite << count;
		file.close();
		return true;
	}
	file.close();
	return false;
}

void game()
{
	while (true)
	{
		int temp = 0;
		int count = 1;
		std::vector<int> tempRepeats ={};
		std::vector<int> repeats = {};
		srand(time(nullptr));
		std::string tempField;
		std::string emptyField = board();
		std::string field = board();
		fillBoard(field, squares, pics);
		char smb;
		char tempSmb;
		while (emptyField != field)
		{
			tempRepeats = repeats;
			tempField = emptyField;
			smb = showChoosedSquare(field, emptyField, getSquare(squares, emptyField, repeats));
			tempSmb = smb;
			smb = showChoosedSquare(field, emptyField, getSquare(squares, emptyField, repeats));
			if (smb != tempSmb)
			{
				Sleep(1000);
				emptyField = tempField;
				repeats = tempRepeats;
			}
			count++;
		}

		std::cout << "\x1b[34mYOU WIN!!!!\x1b[0m\n\n";
		if (record(count, temp))
		{
			std::cout << "\x1b[31mNEW RECORD!!!!!\x1b[0m\n\n";
		}
		else
		{
			std::cout << "\x1b[32mRECORD: " << temp << " TRIES.\x1b[0m\n\n";
		}
		std::cout << "\x1b[33m" << count << " TRIES.\x1b[0m\n\n";
		Sleep(5000);
	}
	
}
