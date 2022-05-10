#pragma once
#include <iostream>
#include<windows.h>
#include"board.h"
#include "variables.h"
#include <fstream>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>

#pragma comment (lib, "Winmm.lib")

int getSquare(std::vector<int> squares, std::string board, std::vector<int>& repeats);
char showChoosedSquare(std::string& board, std::string& emptyBoard, int square);
bool record(int count, int& temp, int boardSize);
void game();
int getBoardSize();
bool isContinue();
std::vector <int> partyTime(int seconds);