// Unix Free Block Group Linking Method build in 2021.06.30
// file name: AppStartUp.h
// Edit by @Michael Zhou

#pragma once
#include "AllocFreeBlocksApp.h"
#include "header.h"

class AppStartUp : CAllocFreeBlockApp
{
	int maxGroupBlocks;
	int lowTotalFreeBlocks;
	int highTotalFreeBlocks;
public:
	explicit AppStartUp(int maxGroupBlocks=20, int lowTotalBlocks=90, int highTotalBlocks=120);
	~AppStartUp() = default;

	void AppStart() const;
};
