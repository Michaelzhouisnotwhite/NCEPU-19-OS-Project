#include "PrExceptions.h"

PrException::AlgorithmExceptions::AlgorithmExceptions(const std::string& c)
{
	m_p = c;
}

std::string PrException::AlgorithmExceptions::What()
{
	std::cout << R"(The algorithm must be "FIFO"(First in first out) or "LRU"(Least recently used))" << std::endl;
	return m_p;
}
