// Unix Free Block Group Linking Method build in 2021.06.29
// file name: CGui.cpp
// Edit by @Michael Zhou
#include <iostream>

#include "header.h"

void ShowMenu()
{
	std::cout << "============= Welcome =============" << std::endl;
	std::cout << "*   1.Allocate The Free Blocks    *\n";
	std::cout << "*   2.Release The Free Blocks     *\n";
	std::cout << "*   3.Check Out The Files         *\n";
	std::cout << "*   4.Check Out The Free Blocks   *\n";
	std::cout << "*              5.Exit             *\n";
	std::cout << "* -- Please Enter An Operation -- *" << std::endl;
	std::cout << "========  (Enter 1 to 5)  =========" << std::endl;
}

