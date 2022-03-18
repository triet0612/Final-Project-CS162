#pragma once
#include "Textbox.h"
class Button : public TextBox {

    function<void(Button&)> onClick;
    bool isClicked = false;

public:

    Button() : TextBox() {
        this->onClick = [](Button& b) {};
    }

    Button(int x, int y, int width, int height, function<void(Button&)> onClick, bool border = false, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15) : TextBox(x, y, width, height, border, idleBgColor, idleTextColor, idleBorderColor) {
        this->onClick = onClick;
    }

    void setDefaultType() {
        this->setIdleBgColor(IDLE_BG1);
        this->setIdleTextColor(IDLE_TEXT1);
        this->setHoverBgColor(HOVER_BG);
        this->setHoverTextColor(HOVER_TEXT | 15);
        this->hover2Idle();
    }

    bool update(pair<int, int> input) {
        if (this->isMouseInContainer()) {
            if (this->isHover == false) {
                this->isHover = true;
                this->reRender = true;
                this->idle2Hover();
            }

            if (input.first == INPUT_CODE::ENTER) {
                if (this->isClicked == false) {
                    this->onClick(*this);
                }
            }

            return true;
        }
        else {
            if (this->isHover == true) {
                this->isHover = false;
                this->reRender = true;
                this->hover2Idle();
            }

            return false;
        }
    }

    void render() {
        TextBox::render();
    }

};


