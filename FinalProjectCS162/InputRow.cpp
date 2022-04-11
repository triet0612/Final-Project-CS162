#include "InputRow.h"

InputRow::InputRow() : Container() {
    this->titleBoxWidth = 10;
    this->contentBoxWidth = 10;
}

InputRow::InputRow(int x, int y, int width, int height, int bgColor, int textColor) : Container(x, y, width, height, false, bgColor, textColor) {
    this->titleBoxWidth = width / 2;
    this->contentBoxWidth = width / 2;
    this->textBoxes.push_back(TextBox(x, y, this->titleBoxWidth, height, true, bgColor, textColor).setText("i"));
    this->textBoxes.push_back(TextBox(x + this->titleBoxWidth, y, this->contentBoxWidth, height, true, bgColor, textColor).setText("e"));
}

InputRow& InputRow::setTitleBoxWidth(int width) {
    this->titleBoxWidth = width;
    this->textBoxes.front().setWidth(width);
    this->textBoxes.back().setX(this->x + width);
    return *this;
}

InputRow& InputRow::setContentBoxWidth(int width) {
    this->contentBoxWidth = width;
    this->textBoxes.back().setWidth(width);
    return *this;
}

InputRow& InputRow::setTitle(string title) {
    this->textBoxes.front().setText(title);
    return *this;
}

InputRow& InputRow::setContent(string content) {
    this->textBoxes.back().setText(content);
    return *this;
}

TextBox& InputRow::getTitleBox() {
    return this->textBoxes.front();
}

TextBox& InputRow::getContentBox() {
    return this->textBoxes.back();
}

void InputRow::setDefaultType0() {
    this->textBoxes.front().setIdleBgColor(IDLE_BG0);
    this->textBoxes.front().setHoverBgColor(IDLE_BG0 | BG_I);
    this->textBoxes.front().setIdleTextColor(IDLE_TEXT0);
    this->textBoxes.front().setHoverTextColor(IDLE_TEXT0);
    this->textBoxes.front().setIdleBorderColor(IDLE_BG0 | HOVER_TEXT0);
    this->textBoxes.front().setHoverBorderColor(IDLE_BG0 | HOVER_TEXT0);
    this->hover2Idle();
}

void InputRow::setDefaultType() {
    this->textBoxes.front().setIdleBgColor(IDLE_BG1);
    this->textBoxes.front().setHoverBgColor(IDLE_BG1);
    this->textBoxes.front().setIdleTextColor(IDLE_TEXT1);
    this->textBoxes.front().setHoverTextColor(IDLE_TEXT1);
    this->textBoxes.front().setIdleBorderColor(IDLE_BG1 | HOVER_TEXT1);
    this->textBoxes.front().setHoverBorderColor(IDLE_BG1 | HOVER_TEXT1);
    this->hover2Idle();
}

void InputRow::setDefaultType2() {
    this->textBoxes.front().setIdleBgColor(HOVER_BG1);
    this->textBoxes.front().setHoverBgColor(HOVER_BG1);
    this->textBoxes.front().setIdleTextColor(IDLE_TEXT);
    this->textBoxes.front().setHoverTextColor(IDLE_TEXT);
    this->textBoxes.front().setIdleBorderColor(0);
    this->textBoxes.front().setHoverBorderColor(0);
    this->hover2Idle();
}

void InputRow::setDefaultType3() {
    this->textBoxes.front().setIdleBgColor(IDLE_BG3);
    this->textBoxes.front().setHoverBgColor(IDLE_BG3);
    this->textBoxes.front().setIdleTextColor(IDLE_TEXT3);
    this->textBoxes.front().setHoverTextColor(IDLE_TEXT3);
    this->textBoxes.front().setIdleBorderColor(IDLE_BG3 | HOVER_TEXT3);
    this->textBoxes.front().setHoverBorderColor(IDLE_BG3 | HOVER_TEXT3);
    this->hover2Idle();
}

void InputRow::setDefaultType4() {
    this->textBoxes.front().setIdleBgColor(HOVER_BG3);
    this->textBoxes.front().setHoverBgColor(HOVER_BG3);
    this->textBoxes.front().setIdleTextColor(IDLE_TEXT2);
    this->textBoxes.front().setHoverTextColor(IDLE_TEXT2);
    this->textBoxes.front().setIdleBorderColor(0);
    this->textBoxes.front().setHoverBorderColor(0);
    this->hover2Idle();
}

bool InputRow::checkMouseInsideContentBox() {
    return this->getContentBox().isMouseInContainer();
}

bool InputRow::checkPosInsideContentBox(COORD c) {
    return this->getContentBox().isPosInContainer(c);
}

void InputRow::setCursorInside() {
    if (this->isHover == false) {
        this->textBoxes.back().setCursorInside();
        this->isHover = true;
        this->reRender = true;
        this->idle2Hover();
    }
}

pair<int, int> InputRow::getInside() {
    return Container::getInside();
}

void InputRow::hover2Idle() {
    Container::hover2Idle();
    this->textBoxes.front().hover2Idle();
}

void InputRow::idle2Hover() {
    Container::idle2Hover();
    this->textBoxes.front().idle2Hover();
}

void InputRow::update(pair<int, int> input) {
    if (this->isMouseInContainer()) {
        this->setCursorInside();
    }
    else {
        if (this->isHover == true) {
            this->isHover = false;
            this->reRender = true;
            this->textBoxes.back().setBorder(true);
            this->hover2Idle();
        }
    }
    this->textBoxes.back().update(input);
}

void InputRow::render() {
    if (this->reRender) {
        this->reRender = false;
        this->textBoxes.front().render();
    }
    this->textBoxes.back().render();
}
