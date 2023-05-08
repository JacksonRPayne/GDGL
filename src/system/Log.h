#pragma once
#include <iostream>
#include <string>

#define NEWLINE(b) (b ? '\n' : ' ')

class Log
{
public:

	static void LogMessage(const std::string &msg, bool newLine = true);
	static void LogError(const std::string &errorMsg, bool newLine = true);
	static void LogWarning(const std::string &warningMsg, bool newLine = true);
	
	static void LogFPS(float dt, int framesPerLog, bool newLine = true);

	// TODO: make it flush instead of calling every time (lol)

private:

	static float timeTracker;
	static int frameTracker;
};

