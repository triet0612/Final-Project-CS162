#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <functional>
#include <assert.h>
#include "SinglyLinkedList.h"
using namespace std;

enum ASCII
{
    DASH_TOP = 196,
    DASH_BOTTOM = 95,
    DASH_VERTICAL = 179,
    CORNER_BL = 192,
    CORNER_BR = 217,
    CORNER_TL = 218,
    CORNER_TR = 191,
};

enum MYCOLOR
{
    BG_RED = BACKGROUND_RED,
    BG_BLUE = BACKGROUND_BLUE,
    BG_GREEN = BACKGROUND_GREEN,
    BG_WHITE = BG_RED | BG_BLUE | BG_GREEN,
    BG_I = BACKGROUND_INTENSITY,
    FG_RED = FOREGROUND_RED,
    FG_BLUE = FOREGROUND_BLUE,
    FG_GREEN = FOREGROUND_GREEN,
    FG_WHITE = FG_BLUE | FG_GREEN | FG_RED,
    FG_I = FOREGROUND_INTENSITY,
};

enum DEFAULT_COLOR
{
    HOVER_BG0 = BG_WHITE | BG_I,
    HOVER_TEXT0 = BG_WHITE| BG_I,
    IDLE_BG0 = 0,
    IDLE_TEXT0 = FG_I | FG_WHITE,

    HOVER_BG = BG_BLUE | BG_I,
    HOVER_TEXT = BG_BLUE | BG_I,
    IDLE_BG = 0,
    IDLE_TEXT = FG_I | FG_BLUE,


    HOVER_BG1 = 0,
    HOVER_TEXT1 = FG_GREEN | FG_BLUE,
    IDLE_BG1 = BG_GREEN | BG_BLUE,
    IDLE_TEXT1 = BG_GREEN | BG_BLUE | 15,

    HOVER_BG2 = BG_GREEN | BG_I,
    HOVER_TEXT2 = BG_GREEN | BG_I,
    IDLE_BG2 = 0,
    IDLE_TEXT2 = FG_I | FG_GREEN,

    HOVER_BG3 = 0,
    HOVER_TEXT3 = FG_GREEN | FG_I,
    IDLE_BG3 = BG_GREEN,
    IDLE_TEXT3 = BG_GREEN,


};

enum INPUT_CODE
{
    RIGHT = 77, LEFT = 75, UP = 72, DOWN = 80, BACKSPACE = 8, ENTER = 13, ESC = 27, TAB = 9, SPACE = 32, WRD = 257, DIRECTION = -32
};


class ConsoleGraphics
{
private:
    HANDLE h = nullptr;
    SinglyLinkedList<COORD> myQueue;
    COORD curPos;
    bool isCursorHide = false;
    void releaseOverSize();
public:

    ConsoleGraphics();;

    static ConsoleGraphics& getInstance();

    pair<int, int> getRowCol();

    HANDLE getHandle();

    COORD GetConsoleCursorPosition();

    bool GetColor(short& ret);

    void gotoXY(short x, short y, bool store = false);


    COORD getLastPos();

    void gotoLast();

    void moveHorizontal(short s, bool store = false);

    void moveVertical(short s, bool store = false);

    void clearLine(int line);

    void clearScreen();

    void color(int x);

    void hideCursor();

    void showCursor();

    void hideAndShowCursor(function<void()> func = []() {});

    void gotoAndReturn(function<void()> func = []() {}, int goX = -1, int goY = -1, int retX = -1, int retY = -1);

    void clearLineV2(int line);

    void getNextDirection(const pair<int, int>& input, int& x, int& y);

    void loop(function<void(pair<int, int>)> func = [](pair<int, int>) {}, int keyEnd = ESC);

    void loopBoolean(function<bool(pair<int, int>)> keepLooping = [](pair<int, int>) { return false; });


    void drawRect(int x, int y, int w, int h, bool border = true, int bgColor = 0, int borderColor = 15);

    void drawListOfRect(int x, int y, int w, int h, int tot, bool adjacent = false, bool border = true, int bgColor = 0, int borderColor = 15);

    void fillRect(int x, int y, int w, int h, int bgColor = 0);;
};

