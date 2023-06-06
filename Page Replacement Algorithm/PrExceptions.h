// Page Replacement Algorithm build in 2021.06.05
// file name: PrExceptions.h
// Edit by @Michael Zhou

#pragma once
#include <stdexcept>
#include <iostream>

namespace PrException
{
	class AlgorithmExceptions final :
		public std::exception
	{
	protected:	
		std::string m_p;

	public:
		explicit AlgorithmExceptions(const std::string& c);

		//what()函数返回错误信息
		virtual std::string What();
	};
}
