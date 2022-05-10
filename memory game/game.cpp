#include "game.h"

int getSquare(std::vector<int> squares, std::string board, std::vector<int>& repeats)
{
	int square = 0;
	std::string temp;
	while (!square)
	{
		system("cls");
		std::cout << board;
		std::cout << "Enter square number\n";
		std::getline(std::cin, temp);
		try
		{
			PlaySound(TEXT("./sound/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
			square = std::stoi(temp);
		}
		catch (std::exception&)
		{
			square = 0;
		}
		if (squares.size() == 16 && square > 0 && square < 17)
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
		else if (squares.size() == 36 && square > 0 && square < 37)
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
	emptyBoard.replace(square, 2, { smb, ' ' });
	std::cout << emptyBoard;
	return smb;
}

bool record(int count, int& temp, int boardSize)
{
	std::string tempStr1;
	std::string tempStr2;
	std::ifstream file("record.mg");
	if (!file.is_open())
	{
		std::ofstream createIfNoFile("record.mg");
		createIfNoFile.close();
		std::ifstream file("record.mg");
	}

	getline(file, tempStr1);
	getline(file, tempStr2);
	if (boardSize == 4)
	{
		try
		{
			temp = std::stoi(tempStr1);
		}
		catch (std::exception&)
		{
			temp = 0;
			tempStr1 = std::to_string(count);
		}
		
	}
	else
	{
		try
		{
			temp = std::stoi(tempStr2);
		}
		catch (std::exception&)
		{
			temp = 0;
			tempStr2 = std::to_string(count);
		}
	}
	
	if (!temp || count < temp)
	{
		file.close();
		std::ofstream rewrite("record.mg");

		if (boardSize == 4) tempStr1 = std::to_string(count);
		else tempStr2 = std::to_string(count);

		rewrite << tempStr1 << '\n' << tempStr2;
		rewrite.close();
		return true;
	}
	else file.close();
	return false;
}

int getBoardSize()
{
	char size = ' ';
	std::cout << "\x1b[33menter board size:\n1 for 4x4\n2 for 6x6\x1b[0m\n";
	while ((size != '1') && (size != '2'))
	{
		size = _getch();
	}
	return size == '1' ? 4 : 6;
	
}

bool isContinue()
{
	char cont = ' ';
	std::cout << "\x1b[33mDo you want to play again? y/n\t\x1b[0m";
	while (cont != 'y' && cont != 'n')
	{
		cont = _getch();
		if (cont == 'Y') cont = 'y';
		if (cont == 'N') cont = 'n';
	}
	return cont == 'y' ? true : false;
}

std::vector <int> partyTime(int seconds)
{
	int hours, minutes;
	hours = seconds / 3600;
	minutes = (seconds - hours * 3600) / 60;
	seconds = seconds - hours * 3600 - minutes * 60;
	std::vector <int> time;
	time.push_back(hours);
	time.push_back(minutes);
	time.push_back(seconds);
	return time;
}

void showPartyTime(std::vector<int> time)
{
	std::cout << "\x1b[31mPARTY TIME: " << time[0] << "h: " << time[1] << "m: " << time[2] << "s" <<"\x1b[0m";
}

void game()
{
	while (true)
	{
		time_t start, end;
		int boardSize = getBoardSize();
		int temp = 0;
		int count = 0;
		std::vector<int> tempRepeats ={};
		std::vector<int> repeats = {};
		srand(time(nullptr));
		std::string tempField;
		std::string emptyField = board(boardSize);
		std::string field = board(boardSize);

		if (boardSize == 4) squearsNumbering(emptyField, squares);
		else squearsNumbering(emptyField, squaresForBigField);

		if (boardSize == 4) fillBoard(field, squares, pics);
		else fillBoard(field, squaresForBigField, picsForBigField);

		char smb;
		char tempSmb;

		time(&start);
		
		while (emptyField != field)
		{
			tempRepeats = repeats;
			tempField = emptyField;
			if (boardSize == 4)
			{
				smb = showChoosedSquare(field, emptyField, getSquare(squares, emptyField, repeats));
				tempSmb = smb;
				smb = showChoosedSquare(field, emptyField, getSquare(squares, emptyField, repeats));
			}
			else
			{
				smb = showChoosedSquare(field, emptyField, getSquare(squaresForBigField, emptyField, repeats));
				tempSmb = smb;
				smb = showChoosedSquare(field, emptyField, getSquare(squaresForBigField, emptyField, repeats));
			}
			
			if (smb != tempSmb)
			{
				PlaySound(TEXT("./sound/missed.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(1000);
				emptyField = tempField;
				repeats = tempRepeats;
			}
			else
			{
				PlaySound(TEXT("./sound/ta-dam.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			count++;
		}

		time(&end);
		int seconds = difftime(end, start);
		std::vector <int> playTime = partyTime(seconds);
		std::cout << "\x1b[34mYOU WIN!!!!\x1b[0m\n\n";
		if (record(count, temp, boardSize))
		{
			PlaySound(TEXT("./sound/applause_if_record.wav"), NULL, SND_FILENAME | SND_ASYNC);
			std::cout << "\x1b[31mNEW RECORD!!!!!\x1b[0m\n\n";
		}
		else
		{
			PlaySound(TEXT("./sound/applause_standart.wav"), NULL, SND_FILENAME | SND_ASYNC);
			std::cout << "\x1b[32mRECORD: " << temp << " TRIES.\x1b[0m\n\n";
		}
		std::cout << "\x1b[33mYOUR COUNT OF TRIES: " << count << "\x1b[0m\n\n";
		showPartyTime(playTime);
		Sleep(5000);
		system("cls");
		if (!isContinue())
		{
			system("cls");
			break;
		}
		system("cls");
	}
	
}
