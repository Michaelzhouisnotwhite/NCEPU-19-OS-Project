#include "AllocFreeBlocksApp.h"
#include "header.h"
#include <iostream>
#include <ctime>

CAllocFreeBlockApp::CAllocFreeBlockApp(const int maxGroupBlocks, const int lowTotalBlocks, const int highTotalBlocks)
	: m_maxGroupBlocksNo(maxGroupBlocks)
{
	srand(static_cast<unsigned>(time(nullptr))); // NOLINT(cert-msc51-cpp)
	totalFreeBlockNums = rand() % (highTotalBlocks - lowTotalBlocks) + lowTotalBlocks;

	// --debug
	// totalFreeBlockNums = 10;
	// --debug

	if (0 == totalFreeBlockNums % (m_maxGroupBlocksNo - 1))
	{
		m_col = totalFreeBlockNums / (m_maxGroupBlocksNo - 1);
	}
	else
	{
		m_col = 1 + totalFreeBlockNums / (m_maxGroupBlocksNo - 1);
	}
	m_row = m_maxGroupBlocksNo + 1;

	// allocate
	totalBlocksMat = new int*[m_row];
	for (int i = 0; i < m_row; i ++)
	{
		totalBlocksMat[i] = new int[m_col];
		if (0 == i)
		{
			for (int j = 0; j < m_col; j++)
			{
				totalBlocksMat[i][j] = m_maxGroupBlocksNo;
			}
		}
	}

	// --tmp
	for (int i = 0, k = 1; i < m_col - 1; i++, k++)
	{
		totalBlocksMat[1][i] = k;
	}

	// init the first group
	totalBlocksMat[1][m_col - 1] = 0;
	// --tmp
	int tmp = 1;
	for (int i = m_col - 1; i >= 0; i--)
	{
		for (int j = 2; j < m_row; j++)
		{
			totalBlocksMat[j][i] = tmp++;
		}
	}

	if (totalFreeBlockNums % (m_maxGroupBlocksNo - 1) > 0)
	{
		totalBlocksMat[0][0] = totalFreeBlockNums % (m_maxGroupBlocksNo - 1) + 1;
	}
	CopyColToMemory(0);
}

CAllocFreeBlockApp::~CAllocFreeBlockApp()
{
	for (int i = 0; i < m_row; i++)
	{
		delete[] totalBlocksMat[i];
	}
	delete[] totalBlocksMat;
}

CAllocFreeBlockApp::CAllocFreeBlockApp(const CAllocFreeBlockApp& freeBlockApp)
{
	// deepcopy
	this->m_col = freeBlockApp.m_col;
	this->m_row = freeBlockApp.m_row;
	this->totalFreeBlockNums = freeBlockApp.totalFreeBlockNums;

	this->m_maxGroupBlocksNo = freeBlockApp.m_maxGroupBlocksNo;
	// reallocate
	totalBlocksMat = new int*[m_row];
	for (int i = 0; i < m_row; i ++)
	{
		totalBlocksMat[i] = new int[m_col];
	}
}

int** CAllocFreeBlockApp::GetTotalBlocks() const
{
	return totalBlocksMat;
}

void CAllocFreeBlockApp::CopyColToMemory(const int col)
{
	vMainMemoryBlockList.clear();
	for (int i = 0; i < m_row; i++)
	{
		vMainMemoryBlockList.push_back(totalBlocksMat[i][col]);
	}
}

void CAllocFreeBlockApp::CopyMemoryToCol(const int col)
{
	for (int i = 0; i < m_row; i++)
	{
		totalBlocksMat[i][col] = vMainMemoryBlockList[i];
	}
}

int CAllocFreeBlockApp::RequestSpace(const int space_size)
{
	distributionList.clear();
	if (space_size > GetRemainBlocksNums())
	{
		return UNSUCESS_CODE;
	}

	int space_size_copy = space_size;
	while (0 < space_size_copy)
	{
		if (vMainMemoryBlockList[0] > 1)
		{
			distributionList.push_back(vMainMemoryBlockList[vMainMemoryBlockList[0]]);
			vMainMemoryBlockList[0]--;
			space_size_copy --;
		}
		else if (vMainMemoryBlockList[0] <= 1)
		{
			CopyColToMemory(vMainMemoryBlockList[1]);
		}
	}
	distributionMat.push_back(distributionList);
	return SUCESS_CODE;
}


int CAllocFreeBlockApp::GetRemainBlocksNums() const
{
	int nRemainBlocks = vMainMemoryBlockList[0] - 1;
	if (0 == vMainMemoryBlockList[1])
	{
		return nRemainBlocks;
	}
	for (int i = vMainMemoryBlockList[1]; i < m_col; i++)
	{
		nRemainBlocks += (totalBlocksMat[0][i] - 1);
	}
	return nRemainBlocks;
}

int CAllocFreeBlockApp::ShowRemainBlocks()
{
	
	if (0 == vMainMemoryBlockList[1] && vMainMemoryBlockList[0] > 1)
	{
		std::cout << "Group 1:" << std::endl;
		for (int i = vMainMemoryBlockList[0]; i >=2 ; i--)
		{
			std::cout << vMainMemoryBlockList[i];
			std::cout << " ";
		}
		std::cout.put('\n');
	}
	else if (vMainMemoryBlockList[1] > 0)
	{
		int group_no = 1;
		for (int c = m_col - 1; c >= vMainMemoryBlockList[1]; c--)
		{
			std::cout << "Group " << group_no << ":" << std::endl;
			for (int r = m_row - 1; r >= 2; r--)
			{
				std::cout << totalBlocksMat[r][c];
				std::cout << " ";
			}
			group_no++;
			std::cout.put('\n');
		}
		if (vMainMemoryBlockList[0] > 1)
		{
			std::cout << "Group " << group_no << ":" << std::endl;
			for (int i = vMainMemoryBlockList[0]; i >=2 ; i--)
			{
				std::cout << vMainMemoryBlockList[i];
				std::cout << " ";
			}
			std::cout.put('\n');
		}
	}
	else if (0 == vMainMemoryBlockList[1] && vMainMemoryBlockList[0] == 1)
	{
		return UNSUCESS_CODE;
	}
	return SUCESS_CODE;
}

int CAllocFreeBlockApp::ShowDistributionMat() const
{
	int index = 1;
	if (distributionMat.empty())
	{
		return UNSUCESS_CODE;
	}
	for (const auto& dl : distributionMat)
	{
		std::cout << "File " << index << " blocks No:" << std::endl;
		for (auto d : dl)
		{
			std::cout << d;
			std::cout << " ";
		}
		std::cout.put('\n');
		std::cout.put('\n');
		index++;
	}
	return SUCESS_CODE;
}

int CAllocFreeBlockApp::GetDistributionMatRow() const
{
	return distributionMat.size();
}

void CAllocFreeBlockApp::ShowDistributionList() const
{
	for (auto i : distributionList)
	{
		std::cout << i;
		std::cout << " ";
	}
	std::cout << "\n";
}

int CAllocFreeBlockApp::GetDistributionListSize() const
{
	return distributionList.size();
}

int CAllocFreeBlockApp::ReleaseBlocks(const int fileNo)
{
	if (fileNo > static_cast<int>(distributionMat.size()) || fileNo < 1)
	{
		return WRONG_CODE;
	}
	int file_index = fileNo - 1;
	for (int i = static_cast<int>(distributionMat[file_index].size()) - 1; i >= 0;)
	{
		if (vMainMemoryBlockList[1] != 0)
		{
			if (vMainMemoryBlockList[0] < totalBlocksMat[0][vMainMemoryBlockList[1] - 1])
			{
				vMainMemoryBlockList[0]++;
				vMainMemoryBlockList[vMainMemoryBlockList[0]] = distributionMat[file_index][i];
				i--;
			}
			else
			{
				CopyMemoryToCol(vMainMemoryBlockList[1] - 1);
				CopyColToMemory(vMainMemoryBlockList[1] - 2);
				vMainMemoryBlockList[0] = 1;
			}
		}
		else
		{
			if (vMainMemoryBlockList[0] < totalBlocksMat[0][m_col - 1])
			{
				vMainMemoryBlockList[0]++;
				vMainMemoryBlockList[vMainMemoryBlockList[0]] = distributionMat[file_index][i];
				i--;
			}
			else
			{
				CopyMemoryToCol(m_col - 1);
				CopyColToMemory(m_col - 2);
				vMainMemoryBlockList[0] = 1;
			}
		}
	}
	DeleteRowOfTwoDimensionalVector(distributionMat, file_index);
	return SUCESS_CODE;
}
