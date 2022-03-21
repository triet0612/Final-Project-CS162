#pragma once
#include "LogRegHandler.h"
class CourseSystem
{
private:
	LogRegHandler logRegHandler;
public:
	CourseSystem() {
	};

	void startProgram() {
		logRegHandler.logRegProc();
	}
};

