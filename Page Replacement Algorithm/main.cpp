// // 05
// // Edit by Michael
// //

#include <iostream>
#include <ctime>
#include <Windows.h>
#include <iomanip>

#include "seed.h"
#include "Page Replacement.h"

using namespace std;

int main() //NOLINT
{
	// ReSharper disable once CppInconsistentNaming
	int L;
	int m;

#ifdef _DEBUG
	m = 4;
	int debug_page_query[] = {4, 3, 2, 1, 4, 3, 5, 4, 3, 2, 1, 5};
	L = sizeof(debug_page_query) / sizeof(int);
#else
	cout << "Enter the Page Length:" << endl;
	cin >> L;
	cin.ignore();
	cout << "Enter the memory blocks: " << endl;
	cin >> m;
	cin.ignore();
#endif

	auto* lp = new int[L];

#ifndef _DEBUG
	auto start = clock();
	for (int i = 0; i < L; i ++)
	{
		*(lp + i) = rs::RandInt(static_cast<long long>(i), 0, 5);
	}
#endif

#ifdef _DEBUG
	for (int i = 0; i < L; i ++)
	{
		*(lp + i) = *(debug_page_query + i);
	}
#endif

	// undebug
	PageReplacement testLru(m, L, lp);

	double rateLru = testLru.GetPageLostRate("LRU");
	double rateFifo = testLru.GetPageLostRate("FIFO");


#ifndef _DEBUG
	cout.setf(ios::fixed);
	cout << setprecision(2) << endl;
	cout << "Page Lost Rate:" << endl;
	cout << "    FiFo: " << (rateFifo * 100) << "%" << endl;
	cout << "    LRU:  " << (rateLru * 100) << "%" << endl;
#endif

	system("pause");
	delete[] lp;
	return 0;
}
