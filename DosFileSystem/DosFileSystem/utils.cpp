#include <chrono>
#include <cstdio>
#include <string>
#include <ctime>
#include <cctype>
#include <algorithm>

auto GetCurrentSystemTime() -> char*
{
	auto tt = std::chrono::system_clock::to_time_t
		(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = {0};
	sprintf(date, "%d/%02d/%02d %02d:%02d",
	        1900 + static_cast<int>(ptm->tm_year), static_cast<int>(ptm->tm_mon) + 1, static_cast<int>(ptm->tm_mday),
	        static_cast<int>(ptm->tm_hour), static_cast<int>(ptm->tm_min));
	return date;
}

auto ToUppercase(char* cmd) -> const char*
{
	std::string s = cmd;
	std::transform(s.begin(), s.end(), s.begin(), toupper);
	const auto tmp = new char(sizeof(strlen(cmd) + 1));
	strcpy(tmp, s.c_str());
	return tmp;
}
