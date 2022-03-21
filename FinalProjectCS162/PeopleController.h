#pragma once
#include "GeneralPersonalInfo.h"
#include "SinglyLinkedList.h"
#include "SinglyLinkedList.h"
#include "InputRow.h"
#include "Button.h"
class PeopleController
{
public:

    void setupLoginInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {
        system("cls");
        for (int i = 0; i < 2; ++i) {
            inputList.push_back(InputRow(1, 4 * i + 1, 50, 3, 0, 15));
            pos.push_back(inputList.back().getInside());
            inputList.back().setTitleBoxWidth(12).setContentBoxWidth(30);
            inputList.back().setDefaultType();
        }

        inputList[0].setTitle("Username:").setContent("");
        inputList[1].getContentBox().setTxtEncoded(true);
        inputList[1].setTitle("Password:").setContent("");

        inputList[0].setCursorInside();
        buttonList.push_back(Button(2, 8, 10, 3));
        pos.push_back(buttonList.back().getInside());
        buttonList.back().setText("   OK");
        buttonList.back().setDefaultType();

        for (auto& elem : buttonList) elem.render();
        for (auto& elem : inputList) elem.update();
        for (auto& elem : inputList) elem.render();
    }

    void setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, pair<string, string>& res, bool& isOver) {
        target.setOnClick([&](Button& button) {
            res.first = inputList[0].getContentBox().getText();
            res.second = inputList[1].getContentBox().getText();
            isOver = true;
            });
    }

    void setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int> >& pos, ConsoleGraphics& graphics) {
        if (!inTxt && !inBtn) {
            if (x > 0 || y > 0) cur = (cur + 1) % pos.size();
            else if (x < 0 || y < 0) cur = (cur + pos.size() - 1) % pos.size();
            graphics.gotoXY(pos[cur].first, pos[cur].second, true);
        }
        else if (inTxt) graphics.gotoXY(c.X, c.Y);
    };

    void renderLogProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
        int cur = 0;
        ConsoleGraphics& graphics = ConsoleGraphics::getInstance();

        TextBox notice = TextBox(15, 8, 40, 3, false).setText("Press ESC for cancel");
        notice.render();

        graphics.loopBoolean([&](pair<int, int> input) {
            COORD c = graphics.GetConsoleCursorPosition();
            int x = 0, y = 0;
            bool inBtn = false, inTxt = false;
            if (input.first == INPUT_CODE::ESC) return false;
            graphics.getNextDirection(input, x, y);
            c.X += x; c.Y += y;

            for (auto& elem : inputList) if (elem.checkPosInsideContentBox(c)) inTxt = true;
            for (auto& elem : buttonList) if (elem.isPosInContainer(c)) inBtn = true;

            setValidPosition(c, x, y, cur, inTxt, inBtn, pos, graphics);

            for (auto& elem : inputList) elem.update(input);
            for (auto& elem : buttonList) elem.update(input);

            Sleep(60);

            for (auto& elem : inputList) elem.render();
            for (auto& elem : buttonList) elem.render();
            if (inBtn) graphics.hideCursor();
            else graphics.showCursor();
            graphics.color(0);
            return !isOver;
            });
    }

    pair<string, string> inputLoginProc() {
        sll<InputRow> inputList;
        sll<Button> buttonList;
        sll<pair<int, int> > pos;
        pair<string, string> res;
        bool isOver = false;

        setupLoginInputList(inputList, buttonList, pos);
        setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

        renderLogProc(inputList, buttonList, pos, isOver);

        return res;
    }


    virtual bool loginProc(string username, string password) = 0;

    virtual void regProc() = 0;

};
