// Unix Free Block Group Linking Method build in 2021.06.29
// file name: function.cpp
// Edit by @Michael Zhou
#include <iostream>

#include "header.h"

int GetInputNum()
{
	auto input_string = new char[1024];
	std::cin.getline(input_string, 1024);
	std::cin.sync();
	for (int i = 1; i < static_cast<int>(strlen(input_string)); i++)
	{
		if (input_string[i] < '0' || input_string[i] > '9')
		{
			return WRONG_CODE;
		}
	}
	int input;
	if (input_string[0] != '-')
	{
		input = input_string[0] - '0';
		for (int i = 1; i < static_cast<int>(strlen(input_string)); i++)
		{
			input = input * 10 + input_string[i] - '0';
		}
	}
	else
	{
		input = input_string[1] - '0';
		for (int i = 2; i < static_cast<int>(strlen(input_string)); i++)
		{
			input = input * 10 + input_string[i] - '0';
		}
		input = input * -1;
	}
	return input;
}

void DeleteRowOfTwoDimensionalVector(std::vector<std::vector<int>>& target, const int row_index)
{
	std::vector<std::vector<int>> temp;
	for (int i = 0; i < target.size(); i++)
	{
		if (row_index == i)
		{
			continue;
		}
		temp.push_back(target[i]);
	}
	target = temp;
}
