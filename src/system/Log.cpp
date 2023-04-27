#include "Log.h"

void Log::LogMessage(const std::string &msg) {
	std::cout << msg << '\n';
}

void Log::LogError(const std::string &errorMsg) {
	std::cout << "ERROR: " << errorMsg << '\n';
}

void Log::LogWarning(const std::string &warningMsg) {
	std::cout << "WARNING: " << warningMsg << '\n';
}