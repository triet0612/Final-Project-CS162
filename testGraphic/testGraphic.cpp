#include "SinglyLinkedList.h"
#include "ConsoleGraphics.h"
#include "Textbox.h"
#include "RowContainer.h"
#include "Table.h"
#include <vector>
#include <string.h>
#include <string>
#include "InputRow.h"
#include "Button.h"
#include <fstream>
ConsoleGraphics& graphics = ConsoleGraphics::getInstance();
sll<pair<int, int>> pos;
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}
int testCnt = 0;
void tableProc(Table& table) {
    graphics.loopBoolean([&](pair<int, int> input) {
        int y = 0, x = 0;
        if (input.first == INPUT_CODE::ESC) return false;
        if (input.first == INPUT_CODE::ENTER) {
            table.defaultPressAnimation();
        } else if (input.first == INPUT_CODE::DIRECTION) {
            graphics.getNextDirection(input, x, y);

            table.switchPage(table.getCurPage() + x);
            table.focusRow(table.getCurRow() + y);
            
            graphics.hideCursor();
        }
        return true;
        });
}

void setTable(Table& table) {
    table = Table(1, 1, 10, true, 0, 15, 15);

    table.addTitleRow_back(20, 30, 40, 20);
    table.getRow(0).addText("STT", "MSSV", "Ho va ten", "Dia chi");

    for (int i = 0; i < 100; ++i) {
        table.addRow_back("dummyTxt");
        auto& elem = table.getRow(i + 1);
        for (int j = 0; j < 4; j++) elem.setBoxText(j, "adf " + to_string(i + 1) + " " + to_string(j + 1));
    }
    table.setDefaultType();
    table.render();
}

void setInputList(sll<InputRow>& inputList) {
    for (int i = 0; i < 5; ++i) {
        inputList.push_back(InputRow(0,  4 * i, 50, 3, 0, 15));
        inputList.back().setTitleBoxWidth(20).setContentBoxWidth(30);
        inputList.back().setDefaultType();
        pos.push_back(inputList.back().getInside());
    }

    inputList[0].setTitle("Course's name:").setContent("Enter here");
    inputList[1].setTitle("Teacher's name:").setContent("Enter here");

    
    inputList[0].setCursorInside();
    for (auto& elem : inputList) elem.update();
    for (auto& elem : inputList) elem.render();
    
}
int cntPress = 0;
void btnProc(Button&) {
    ++cntPress;
}

int main() {
    resizeConsole(1090, 600);
    int bg = 0;
    int txt = FG_BLUE | FG_I;
    COORD c = graphics.GetConsoleCursorPosition();
    system("cls");

    sll<InputRow> inputList;
    Table table;

   
    setInputList(inputList);

    Button button = Button(0, 22, 10, 4, btnProc);
    button.setText("  Afad");
    button.setDefaultType();
    button.render();
    pos.push_back({ 1, 23 });
    int cur = 0;
    graphics.loop([&](pair<int, int> input) {
        
        if (input.first == -32) {
            switch (input.second)
            {
            case INPUT_CODE::UP: --cur; graphics.gotoXY(pos[cur].first, pos[cur].second, true); break;
            case INPUT_CODE::DOWN: ++cur; graphics.gotoXY(pos[cur].first, pos[cur].second, true); break;
            case INPUT_CODE::RIGHT: graphics.moveHorizontal(1, true); break;
            case INPUT_CODE::LEFT: graphics.moveHorizontal(-1, true); break;
            default:
                break;
            }
        }
        else {
            //if (input.first == INPUT_CODE::ENTER) graphics.moveVertical(1, true);
        }

        for (auto& elem : inputList) elem.update(input);
        if (button.update(input)) {
            graphics.hideCursor();
        } else graphics.showCursor();
        Sleep(60);

        for (auto& elem : inputList) elem.render();
        button.render();
        graphics.color(0);
        });

    ofstream ofs("output.txt");
    ofs << cntPress;
    ofs.close();
    system("cls");
    return 0;

}
