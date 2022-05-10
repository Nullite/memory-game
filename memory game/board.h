#pragma once
#include "variables.h"
#include <string>
#include<time.h>

std::string board(int size);
void squearsNumbering(std::string& board, std::vector <int> squears);
void fillBoard(std::string& board, std::vector<int>& squares, std::vector<char> pics);