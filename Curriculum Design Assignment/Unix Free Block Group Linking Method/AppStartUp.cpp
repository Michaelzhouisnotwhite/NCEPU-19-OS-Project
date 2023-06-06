#include "AppStartUp.h"

#include <Windows.h>
#include <iostream>

AppStartUp::AppStartUp(const int maxGroupBlocks, const int lowTotalBlocks, const int highTotalBlocks)
	: maxGroupBlocks(maxGroupBlocks), lowTotalFreeBlocks(lowTotalBlocks), highTotalFreeBlocks(highTotalBlocks)
{
	AppStart();
}

void AppStartUp::AppStart() const
{
	CAllocFreeBlockApp freeBlockApp(maxGroupBlocks, lowTotalFreeBlocks, highTotalFreeBlocks);
	while (true)
	{
		ShowMenu();
		std::cout << "Your Input: ";
		int input = GetInputNum();
		switch (input)
		{
		case 1:
			{
				std::cout << "The current allocation File index is:" << " " << freeBlockApp.GetDistributionMatRow() + 1
					<<
					std::endl;
				std::cout << "Enter the File size(blocks) (-1 to quit):";
				while (true)
				{
					int apply_num = GetInputNum();
					if (0 == apply_num)
					{
						std::cout << "Error:\nCan't apply for none spaces!!\nPlease enter again:";
					}
					else if (EXIT_CODE == apply_num)
					{
						break;
					}
					else if (apply_num >= 0)
					{
						int flag = freeBlockApp.RequestSpace(apply_num);
						if (UNSUCESS_CODE == flag)
						{
							std::cout << "Error:\nThere is not enough spaces!!\n";
							break;
						}
						if (SUCESS_CODE == flag)
						{
							std::cout << "Message:\nAssigned Successfully!!" << std::endl;
							std::cout << "The number of blocks allocated for File "
								<< freeBlockApp.GetDistributionMatRow()
								<< " is " << freeBlockApp.GetDistributionListSize()
								<< std::endl;
							std::cout << "Blocks number are:" << std::endl;
							freeBlockApp.ShowDistributionList();
							break;
						}
						break;
					}
					else
					{
						std::cout << "Error:\nWrong input!\nEnter again:";
					}
				}
				std::cout.put('\n');
			}
			break;
		case 2:
			{
				while (true)
				{
					std::cout << "Enter the file index you want to delete (-1 to quit):";
					int file_index = GetInputNum();
					if (WRONG_CODE == file_index)
					{
						std::cout << "Error:\nWrong input!\n";
						continue;
					}
					if (EXIT_CODE == file_index)
					{
						break;
					}
					int flag = freeBlockApp.ReleaseBlocks(file_index);
					if (SUCESS_CODE == flag)
					{
						std::cout << "Release Successful!!" << std::endl;
					}
					else if (UNSUCESS_CODE == flag)
					{
						std::cout << "Cannot Find The File Index!!" << std::endl;
					}
					std::cout.put('\n');
					break;
				}
			}
			break;
		case 3:
			{
				int flag = freeBlockApp.ShowDistributionMat();
				if (UNSUCESS_CODE == flag)
				{
					std::cout << "Empty!!" << std::endl;
				}
				std::cout.put('\n');
			}
			break;
		case 4:
			{
				std::cout << "The Free Blocks number are as Followed:" << std::endl;
				int flag = freeBlockApp.ShowRemainBlocks();
				if (UNSUCESS_CODE == flag)
				{
					std::cout << "Empty!!" << std::endl;
				}
				std::cout.put('\n');
			}
			break;

		case 5:
			std::cout << "Exiting";
			Sleep(100);
			std::cout << ".";
			Sleep(100);
			std::cout << "..";
			Sleep(100);
			std::cout << "...";
			Sleep(100);
			exit(EXIT_SUCCESS);
		default:
			std::cout << "Wrong Operation!!! Please Check Your Input Number!" << std::endl;
			std::cout.put('\n');
			break;
		}
	}
}
