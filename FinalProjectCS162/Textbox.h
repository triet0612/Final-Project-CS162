#pragma once
#include "Container.h"
class TextBox : public Container {
private:
    bool numberMode;

public:

    TextBox();

    TextBox(int x, int y, int width, int height, bool border = true, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15);

    COORD findTextEnding();

    //setter builder pattern
    TextBox& setText(string text);

    TextBox& setIdleBgColor(int idleBgColor);

    TextBox& setIdleTextColor(int idleTextColor);

    TextBox& setIdleBorderColor(int idleBorderColor);

    TextBox& setHoverTextColor(int hoverTextColor);

    TextBox& setHoverBgColor(int hoverBgColor);

    TextBox& setHoverBorderColor(int hoverBorderColor);

    TextBox& setTxtEncoded(bool isEncoded);

    TextBox& setNumberMode(bool isNumber);

    void deleteText();

    void addChar(char ch);

    void render();;

    void update(pair<int, int> input = { -32 , 0 });;

};



