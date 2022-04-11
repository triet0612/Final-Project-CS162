#include "ConsoleGraphics.h"

void ConsoleGraphics::releaseOverSize() {
    while (myQueue.size() > 100) myQueue.pop_front();
}

ConsoleGraphics::ConsoleGraphics() {
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    curPos = { 0, 0 };
}

ConsoleGraphics& ConsoleGraphics::getInstance() {
    static ConsoleGraphics instance;
    return instance;
}

pair<int, int> ConsoleGraphics::getRowCol() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return { rows, columns };
}

HANDLE ConsoleGraphics::getHandle() {
    if (!h)  h = GetStdHandle(STD_OUTPUT_HANDLE);
    return h;
}

COORD ConsoleGraphics::GetConsoleCursorPosition()
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

bool ConsoleGraphics::GetColor(short& ret) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))
        return false;
    ret = info.wAttributes;
    return true;
}

void ConsoleGraphics::gotoXY(short x, short y, bool store)
{
    if (store && (this->myQueue.size() == 0 || x != this->myQueue.back().X || y != this->myQueue.back().Y)) {
        this->myQueue.push_back(curPos);
        this->releaseOverSize();
        curPos = { x, y };
        gotoXY(x, y);
    }
    SetConsoleCursorPosition(getHandle(), { x, y });
}

COORD ConsoleGraphics::getLastPos() {
    return myQueue.back();
}

void ConsoleGraphics::gotoLast() {
    curPos = this->myQueue.back();
    if (myQueue.size() > 1) myQueue.pop_back();
    gotoXY(curPos.X, curPos.Y, false);
}

void ConsoleGraphics::moveHorizontal(short s, bool store)
{
    COORD pos = GetConsoleCursorPosition();
    pos.X += s;

    gotoXY(pos.X, pos.Y, store);
}

void ConsoleGraphics::moveVertical(short s, bool store)
{
    COORD pos = GetConsoleCursorPosition();
    pos.Y += s;
    gotoXY(pos.X, pos.Y, store);
}

void ConsoleGraphics::clearLine(int line)
{
    gotoAndReturn([]() {
        cout << "                                                                                                                        ";
        }, 0, line);
}

void ConsoleGraphics::clearScreen()
{
    for (int i = 0; i < 60; ++i)
        clearLine(i);
}

void ConsoleGraphics::color(int x)
{
    SetConsoleTextAttribute(getHandle(), x);
}

void ConsoleGraphics::hideCursor() {
    this->isCursorHide = true;
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 10;
    info.bVisible = false;
    SetConsoleCursorInfo(getHandle(), &info);
}

void ConsoleGraphics::showCursor() {
    this->isCursorHide = false;
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 10;
    info.bVisible = true;
    SetConsoleCursorInfo(getHandle(), &info);
}

void ConsoleGraphics::hideAndShowCursor(function<void()> func) {
    this->hideCursor();
    func();
    this->showCursor();
}

void ConsoleGraphics::gotoAndReturn(function<void()> func, int goX, int goY, int retX, int retY) {
    hideAndShowCursor([&]() {
        auto c = GetConsoleCursorPosition();
        if (goX != -1 && goY != -1) gotoXY(goX, goY);
        func();
        if (retX != -1 && retY != -1) gotoXY(retX, retY);
        else gotoXY(c.X, c.Y);
        });
}

void ConsoleGraphics::clearLineV2(int line) {
    auto c = GetConsoleCursorPosition();
    gotoAndReturn([&]() {
        clearLine(line);
        }, 0, line, c.X, c.Y);
}

void ConsoleGraphics::getNextDirection(const pair<int, int>& input, int& x, int& y) {
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

void ConsoleGraphics::loop(function<void(pair<int, int>)> func, int keyEnd) {
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

void ConsoleGraphics::loopBoolean(function<bool(pair<int, int>)> keepLooping) {
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

void ConsoleGraphics::drawRect(int x, int y, int w, int h, bool border, int bgColor, int borderColor) {
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

void ConsoleGraphics::drawListOfRect(int x, int y, int w, int h, int tot, bool adjacent, bool border, int bgColor, int borderColor) {
    assert(w > 2 && h > 2);
    color(borderColor);
    for (int i = 0; i < tot; i++)
    {
        drawRect(x, y + i * (h - adjacent), w, h, border, bgColor, borderColor);
    }
    color(15);
}

void ConsoleGraphics::fillRect(int x, int y, int w, int h, int bgColor) {
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
}
