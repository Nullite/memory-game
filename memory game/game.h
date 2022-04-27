#pragma once
#include <iostream>
#include<windows.h>
#include"board.h"
#include "structs.h"
#include <fstream>

int getSquare(std::vector<int> squares, std::string board, std::vector<int>& repeats);
char showChoosedSquare(std::string& board, std::string& emptyBoard, int square);
bool record(int count, int& temp);
void game();