#include "Button.h"

Button::Button() : TextBox() {
    this->onClick = [](Button& b) {};
}

Button::Button(int x, int y, int width, int height, function<void(Button&)> onClick, bool border, int idleBgColor, int idleTextColor, int idleBorderColor) : TextBox(x, y, width, height, border, idleBgColor, idleTextColor, idleBorderColor) {
    this->onClick = onClick;
}

void Button::setDefaultType0() {
    this->setIdleBgColor(IDLE_BG0);
    this->setIdleTextColor(IDLE_TEXT0);
    this->setHoverBgColor(HOVER_BG0);
    this->setHoverTextColor(HOVER_TEXT0 | 15);
    this->hover2Idle();
}

void Button::setDefaultType() {
    this->setIdleBgColor(IDLE_BG1);
    this->setIdleTextColor(IDLE_TEXT1);
    this->setHoverBgColor(HOVER_BG);
    this->setHoverTextColor(HOVER_TEXT | 15);
    this->hover2Idle();
}

void Button::setDefaultType2() {
    this->setIdleBgColor(IDLE_BG3);
    this->setIdleTextColor(IDLE_TEXT3);
    this->setHoverBgColor(HOVER_BG2);
    this->setHoverTextColor(HOVER_TEXT2);
    this->hover2Idle();
}

bool Button::update(pair<int, int> input) {
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

void Button::setOnClick(function<void(Button&)> onClick) {
    this->onClick = onClick;
}

void Button::render() {
    TextBox::render();
}
