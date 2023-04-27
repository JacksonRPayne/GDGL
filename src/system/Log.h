#pragma once
#include <iostream>
#include <string>

class Log
{
public:

	static void LogMessage(const std::string &msg);
	static void LogError(const std::string &errorMsg);
	static void LogWarning(const std::string &warningMsg);

};

