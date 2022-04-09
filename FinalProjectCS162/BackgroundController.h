#pragma once
#include <fstream>
#include <string>
#include "ConsoleGraphics.h"
static class BackgroundController
{
public:
	static void drawPicFromPath(string path, int x, int y, int color) {
		ifstream ifs(path);
		if (ifs.is_open()) {
			string tmp;
			int row = 0;
			ConsoleGraphics::getInstance().color(color);
			while (!ifs.eof()) {
				getline(ifs, tmp);
				if (tmp == "") break;
				ConsoleGraphics::getInstance().gotoXY(x, y + row++);
				cout << tmp;
			}
		}
		ConsoleGraphics::getInstance().color(0);
	}

	static void beginInterface() {
		drawPicFromPath("Patterns/House.txt", 50, 10, FG_WHITE);
		drawPicFromPath("Patterns/House.txt", 150, 20, FG_WHITE);
		drawPicFromPath("Patterns/Name.txt", 80, 10, FG_WHITE);
		drawPicFromPath("Patterns/Pattern 5.txt", 0, 33, FG_WHITE);
	}

	static void simpleBackground(int type) {
		int color;
		if (type == 1) {
			color = FG_BLUE | FG_GREEN | FG_I;
		}
		else {
			color = FG_GREEN;
		}
		drawPicFromPath("Patterns/House.txt", 50, 10, color);
		drawPicFromPath("Patterns/House.txt", 150, 20, color);
		drawPicFromPath("Patterns/Trees.txt", 140, 0, color);
		drawPicFromPath("Patterns/Trees.txt", 0, 25, color);
	}

	static void loginInterface(int type) {
		int color;
		if (type == 1) {
			color = FG_BLUE | FG_GREEN | FG_I;
		}
		else {
			color = FG_GREEN | FG_I;
		}
		drawPicFromPath("Patterns/Login.txt", 90, 10, color);
		simpleBackground(type);
	}
};

