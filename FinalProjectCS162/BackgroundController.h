#pragma once
#include <fstream>
#include <string>
#include "ConsoleGraphics.h"

static class BackgroundController {
public:
	static void drawPicFromPath(const string& path, int x, int y, int color);

	static void beginInterface();

	static void simpleBackground(int type);

	static void loginInterface(int type);
};

