// Unix Free Block Group Linking Method build in 2021.06.29
// file name: FreeBlock.h
// Edit by @Michael Zhou

#pragma once
#include <random>

class CAllocFreeBlockApp
{
	int** totalBlocksMat;

	int m_row;
	int m_col;
	int totalFreeBlockNums;
	int m_maxGroupBlocksNo;

	std::vector<int> vMainMemoryBlockList;
	std::vector<int> distributionList;
	std::vector<std::vector<int>> distributionMat;
	std::vector<int> releaseBlockList;

public:
	explicit CAllocFreeBlockApp(int maxGroupBlocks = 3, int lowTotalBlocks = 90, int highTotalBlocks = 120);
	CAllocFreeBlockApp(const CAllocFreeBlockApp& freeBlockApp);
	~CAllocFreeBlockApp();

	int** GetTotalBlocks() const;
	int RequestSpace(int space_size);
	int GetRemainBlocksNums() const;
	int ReleaseBlocks(int fileNo);

	void CopyColToMemory(int col);
	void CopyMemoryToCol(int col);
	int ShowRemainBlocks();
	int ShowDistributionMat() const;

	int GetDistributionMatRow() const;
	void ShowDistributionList() const;
	int GetDistributionListSize() const;
};
