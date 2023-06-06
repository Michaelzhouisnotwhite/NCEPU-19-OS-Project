// Page Replacement Algorithm build in 2021.06.05
// file name: PageReplacement.h
// Edit by @Michael Zhou

// #pragma once
#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

#include <vector>
#include <string>

class PageReplacement //NOLINT
{
protected:
	struct MemBlock
	{
		int info;
		int priority;
	};

public:
	int priority = 0;
	std::vector<MemBlock> m_memBlocks;
	std::vector<int> page_query;
	int m_nAlgorithm{};
	int m_nMemBlockLen;
	int m_nPageLen;

	int m_nLostPages;

	PageReplacement() = default;
	PageReplacement(int memoryBlock, int pageLength, int* lp);
	~PageReplacement() = default;
	friend std::ostream& operator <<(std::ostream& out, PageReplacement lru);
	auto GetPageLostRate(const std::string& algorithm) -> double;

	auto Clean()->void;
protected:
	static auto EncodeAlgorithm(const std::string& algorithm) -> int;
private:
	auto DoLruAlgorithm()->void;
	void DoFifoAlgorithm();

	int FindLeastPriorityIndex();
	int FindSameInfo(int index);
};

#endif
// PAGE_REPLACEMENT_H
