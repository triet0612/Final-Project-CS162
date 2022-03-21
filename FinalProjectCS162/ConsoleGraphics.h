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
    BG_I = BACKGROUND_INTENSITY,
    FG_RED = FOREGROUND_RED,
    FG_BLUE = FOREGROUND_BLUE,
    FG_GREEN = FOREGROUND_GREEN,
    FG_WHITE = FG_BLUE | FG_GREEN | FG_RED,
    FG_I = FOREGROUND_INTENSITY,
};

enum DEFAULT_COLOR
{
    HOVER_BG = BG_BLUE | BG_I,
    HOVER_TEXT = BG_BLUE | BG_I,
    IDLE_BG = 0,
    IDLE_TEXT = FG_I | FG_BLUE,


    HOVER_BG1 = 0,
    HOVER_TEXT1 = FG_GREEN | FG_BLUE,
    IDLE_BG1 = BG_GREEN | BG_BLUE,
    IDLE_TEXT1 = BG_GREEN | BG_BLUE | 15,


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
    void releaseOverSize() {
        while (myQueue.size() > 100) myQueue.pop_front();
    }
public:

    ConsoleGraphics() {
        h = GetStdHandle(STD_OUTPUT_HANDLE);
        curPos = { 0, 0 };
    };

    static ConsoleGraphics& getInstance() {
        static ConsoleGraphics instance;
        return instance;
    }
    pair<int, int> getRowCol() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return { rows, columns };
    }

    HANDLE getHandle() {
        if (!h)  h = GetStdHandle(STD_OUTPUT_HANDLE);
        return h;
    }

    COORD GetConsoleCursorPosition()
    {
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        if (GetConsoleScreenBufferInfo(getHandle(), &cbsi))
        {
            return cbsi.dwCursorPosition;
        }
        else
        {
            COORD invalid = { 0, 0 };
            return invalid;
        }
    }

    bool GetColor(short& ret) {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
            return false;
        ret = info.wAttributes;
        return true;
    }

    void gotoXY(short x, short y, bool store = false)
    {
        if (store && (this->myQueue.size() == 0 || x != this->myQueue.back().X || y != this->myQueue.back().Y)) {
            this->myQueue.push_back(curPos);
            this->releaseOverSize();
            curPos = { x, y };
            gotoXY(x, y);
        }
        SetConsoleCursorPosition(getHandle(), { x, y });
    }


    COORD getLastPos() {
        return myQueue.back();
    }

    void gotoLast() {
        curPos = this->myQueue.back();
        if (myQueue.size() > 1) myQueue.pop_back();
        gotoXY(curPos.X, curPos.Y, false);
    }

    void moveHorizontal(short s, bool store = false)
    {
        COORD pos = GetConsoleCursorPosition();
        pos.X += s;

        gotoXY(pos.X, pos.Y, store);
    }


    void moveVertical(short s, bool store = false)
    {
        COORD pos = GetConsoleCursorPosition();
        pos.Y += s;
        gotoXY(pos.X, pos.Y, store);
    }

    void clearLine(int line)
    {
        gotoAndReturn([]() {
            cout << "                                                                                                                        ";
            }, 0, line);
    }

    void clearScreen()
    {
        for (int i = 0; i < 60; ++i)
            clearLine(i);
    }

    void color(int x)
    {
        SetConsoleTextAttribute(getHandle(), x);
    }

    void hideCursor() {
        this->isCursorHide = true;
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 10;
        info.bVisible = false;
        SetConsoleCursorInfo(getHandle(), &info);
    }

    void showCursor() {
        this->isCursorHide = false;
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 10;
        info.bVisible = true;
        SetConsoleCursorInfo(getHandle(), &info);
    }

    void hideAndShowCursor(function<void()> func = []() {}) {
        this->hideCursor();
        func();
        this->showCursor();
    }

    void gotoAndReturn(function<void()> func = []() {}, int goX = -1, int goY = -1, int retX = -1, int retY = -1) {
        hideAndShowCursor([&]() {
            auto c = GetConsoleCursorPosition();
            if (goX != -1 && goY != -1) gotoXY(goX, goY);
            func();
            if (retX != -1 && retY != -1) gotoXY(retX, retY);
            else gotoXY(c.X, c.Y);
            });
    }

    void clearLineV2(int line) {
        auto c = GetConsoleCursorPosition();
        gotoAndReturn([&]() {
            clearLine(line);
            }, 0, line, c.X, c.Y);
    }

    void getNextDirection(const pair<int, int>& input, int& x, int& y) {
        if (input.first == INPUT_CODE::DIRECTION) {
            switch (input.second)
            {
            case INPUT_CODE::UP: --y; break;
            case INPUT_CODE::DOWN: ++y; break;
            case INPUT_CODE::RIGHT: ++x; break;
            case INPUT_CODE::LEFT:  --x; break;

            default:
                break;
            }
        }
    }

    void loop(function<void(pair<int, int>)> func = [](pair<int, int>) {}, int keyEnd = ESC) {
        char ch = 1;
        while (ch != keyEnd)
        {
            pair<int, int> input = { -32, 0 };
            if (_kbhit())
            {

                ch = _getch();
                input.first = input.second = ch;
                if (ch == -32)
                {
                    ch = _getch();
                    input.second = ch;
                }

            }
            func(input);
        }
    }

    void loopBoolean(function<bool(pair<int, int>)> keepLooping = [](pair<int, int>) { return false; }) {
        char ch = 1;
        do {
            pair<int, int> input = { -32, 0 };
            if (_kbhit())
            {
                ch = _getch();
                input.first = input.second = ch;
                if (ch == -32)
                {
                    ch = _getch();
                    input.second = ch;
                }

            }
            if (!keepLooping(input)) break;
        } while (true);
    }


    void drawRect(int x, int y, int w, int h, bool border = true, int bgColor = 0, int borderColor = 15) {
        assert(w > 2 && h > 2);
        if (border) {
            auto c = GetConsoleCursorPosition();
            color(borderColor);
            gotoAndReturn([&]() {
                cout << char(ASCII::CORNER_TL);
                for (int i = 1; i < w - 1; ++i) {
                    cout << char(ASCII::DASH_TOP);
                }
                cout << char(ASCII::CORNER_TR);

                for (int i = 1; i < h - 1; i++)
                {
                    gotoXY(x, y + i);
                    cout << char(ASCII::DASH_VERTICAL);
                    gotoXY(x + w - 1, y + i);
                    cout << char(ASCII::DASH_VERTICAL);
                }

                gotoXY(x, y + h - 1);

                cout << char(ASCII::CORNER_BL);
                for (int i = 1; i < w - 1; ++i) {
                    cout << char(ASCII::DASH_TOP);
                }
                cout << char(ASCII::CORNER_BR);

                }, x, y, c.X, c.Y);
            color(0);
        }

    }

    void drawListOfRect(int x, int y, int w, int h, int tot, bool adjacent = false, bool border = true, int bgColor = 0, int borderColor = 15) {
        assert(w > 2 && h > 2);
        color(borderColor);
        for (int i = 0; i < tot; i++)
        {
            drawRect(x, y + i * (h - adjacent), w, h, border, bgColor, borderColor);
        }
        color(15);
    }

    void fillRect(int x, int y, int w, int h, int bgColor = 0) {
        gotoAndReturn([&]() {
            for (int i = 0; i < h - 2; i++)
            {
                gotoXY(x + 1, y + i + 1);
                for (int j = 0; j < w - 2; j++)
                {
                    cout << char(SPACE);
                }
            }
            });
    };
};

