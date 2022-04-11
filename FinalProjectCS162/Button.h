#pragma once
#include "Textbox.h"
class Button : public TextBox {

    function<void(Button&)> onClick;
    bool isClicked = false;

public:

    Button();

    Button(int x, int y, int width, int height, function<void(Button&)> onClick = [](Button&) {}, bool border = false, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15);

    void setDefaultType0();

    void setDefaultType();

    void setDefaultType2();

    bool update(pair<int, int> input);

    void setOnClick(function<void(Button&)> onClick);

    void render();

};


