#include "Page Replacement.h"
#include "PrExceptions.h"

#include <utility>
#include <iostream>
using namespace std;

PageReplacement::PageReplacement(const int memoryBlock, const int pageLength, int* lp): m_nLostPages(0)
{
	/// <summary>
	/// init page replacement algorithm.
	/// </summary>
	/// <param name="memoryBlock">refers to 'memery blocks'</param>
	/// <param name="pageLength">'page length'</param>
	/// <param name="lp">'page content'</param>
	/// <param name="algorithm">the algorithms Name</param>
	this->m_nMemBlockLen = memoryBlock;
	this->m_nPageLen = pageLength;
	this->page_query = vector<int>(lp, lp + pageLength);
	this->m_memBlocks.resize(memoryBlock, {-1, -1});
}

auto PageReplacement::GetPageLostRate(const string& algorithm) -> double
{
	/// <summary>
	/// get page lost rate.
	/// </summary>
	/// <param name="algorithm">method</param>
	/// <returns>rate</returns>
	m_nAlgorithm = EncodeAlgorithm(algorithm);
	if (m_nAlgorithm == 0)
	{
		Clean();
		DoFifoAlgorithm();
	}
	else if (m_nAlgorithm == 1)
	{
		Clean();
		DoLruAlgorithm();
	}
	double lostRage = static_cast<double>(m_nLostPages) / m_nPageLen;
#ifdef _DEBUG
	cout << "# from _Debug:\n\tlostRage: " << lostRage << endl;
#endif

	return lostRage;
}

auto PageReplacement::Clean() -> void
{
	m_nAlgorithm = -1;
	m_memBlocks = vector<MemBlock>(m_nMemBlockLen, {-1, -1});
	m_nLostPages = 0;
	priority = 0;
}

auto PageReplacement::EncodeAlgorithm(const std::string& algorithm) -> int
{
	int t = 0;
	if (algorithm == "FIFO")
	{
		t = 0;
	}
	else if (algorithm == "LRU")
	{
		t = 1;
	}
	else
	{
		cout << PrException::AlgorithmExceptions("\"" + algorithm + "\"" + " is not permitted!").What() << endl;
	}
	return t;
}

auto PageReplacement::DoLruAlgorithm() -> void
{
	for (int i = 0; i < static_cast<int>(page_query.size()); i ++, priority++)
	{
		int findSameInfoIndex = -1;
		if (i > 0)
		{
			findSameInfoIndex = FindSameInfo(i);
		}
		if (findSameInfoIndex == -1)
		{
			if (i < static_cast<int>(m_memBlocks.size()))
			{
				m_memBlocks[i].info = page_query[i];
				m_memBlocks[i].priority = priority;
				m_nLostPages++;
			}
			else
			{
				int lpi = FindLeastPriorityIndex();
				m_memBlocks[lpi].info = page_query[i];
				m_memBlocks[lpi].priority = priority;
				m_nLostPages++;
			}
		}
		else
		{
			m_memBlocks[FindSameInfo(i)].info = page_query[i];
			m_memBlocks[FindSameInfo(i)].priority = priority;
		}
	}
}

void PageReplacement::DoFifoAlgorithm()
{
	for (int i = 0; i < static_cast<int>(page_query.size()); i ++, priority++)
	{
		int findSameInfoIndex = -1;
		if (i > 0)
		{
			findSameInfoIndex = FindSameInfo(i);
		}
		if (findSameInfoIndex == -1)
		{
			if (i < static_cast<int>(m_memBlocks.size()))
			{
				m_memBlocks[i].info = page_query[i];
				m_memBlocks[i].priority = priority;
				m_nLostPages++;
			}
			else
			{
				int lpi = FindLeastPriorityIndex();
				m_memBlocks[lpi].info = page_query[i];
				m_memBlocks[lpi].priority = priority;
				m_nLostPages++;
			}
		}
		else
		{
		}
	}
}

int PageReplacement::FindLeastPriorityIndex()
{
	int min_index = 0;
	for (int j = 0; j < static_cast<int>(m_memBlocks.size()); j++)
	{
		if (m_memBlocks[j].priority < m_memBlocks[min_index].priority)
		{
			min_index = j;
		}
	}
	return min_index;
}

int PageReplacement::FindSameInfo(const int index)
{
	for (int i = 0; i < static_cast<int>(m_memBlocks.size()); i++)
	{
		if (page_query[index] == m_memBlocks[i].info)
		{
			return i;
		}
	}
	return -1;
}

ostream& operator<<(ostream& out, PageReplacement lru)
{
	return out;
}
