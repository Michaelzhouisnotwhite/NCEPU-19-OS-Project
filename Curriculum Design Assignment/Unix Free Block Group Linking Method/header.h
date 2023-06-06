// Unix Free Block Group Linking Method build in 2021.06.29
// file name: header.h
// Edit by @Michael Zhou
#pragma once
#include <vector>
#define EXIT_CODE (-1)
#define WRONG_CODE (-2)
#define SUCESS_CODE 1
#define UNSUCESS_CODE 0

void ShowMenu(); //UI
int GetInputNum();
void DeleteRowOfTwoDimensionalVector(std::vector<std::vector<int>>& target, int row_index);
