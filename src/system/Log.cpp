#include "Log.h"

int Log::frameTracker = 0;
float Log::timeTracker = 0.0f;

void Log::LogMessage(const std::string &msg, bool newLine) {
	std::cout << msg << NEWLINE(newLine);
}

void Log::LogError(const std::string &errorMsg, bool newLine) {
	std::cout << "ERROR: " << errorMsg << NEWLINE(newLine);
}

void Log::LogWarning(const std::string &warningMsg, bool newLine) {
	std::cout << "WARNING: " << warningMsg << NEWLINE(newLine);
}

void Log::LogFPS(float dt, int framesPerLog, bool newLine) {
	timeTracker += dt;

	if (frameTracker >= framesPerLog) {
		float fps = 1.0f / (timeTracker / frameTracker);
		std::cout << "FPS: " << fps << NEWLINE(newLine);
		frameTracker = 0;
		timeTracker = 0.0f;
		return;
	}

	frameTracker++;
}