#pragma once
#include "Container.h"
#include "Textbox.h"
class InputRow : private Container {
private:
    SinglyLinkedList<TextBox> textBoxes;
    int titleBoxWidth, contentBoxWidth;
public:
    InputRow() : Container() {
        this->titleBoxWidth = 10;
        this->contentBoxWidth = 10;
    }

    InputRow(int x, int y, int width, int height, int bgColor, int textColor) : Container(x, y, width, height, false , bgColor, textColor) {
        this->titleBoxWidth = width / 2;
        this->contentBoxWidth = width / 2;
        this->textBoxes.push_back(TextBox(x, y, this->titleBoxWidth, height, true, bgColor, textColor).setText("i"));
        this->textBoxes.push_back(TextBox(x + this->titleBoxWidth, y, this->contentBoxWidth, height, true , bgColor, textColor).setText("e"));
    }

    InputRow& setTitleBoxWidth(int width) {
        this->titleBoxWidth = width;
        this->textBoxes.front().setWidth(width);
        this->textBoxes.back().setX(this->x + width);
        return *this;
    }

    InputRow& setContentBoxWidth(int width) {
        this->contentBoxWidth = width;
        this->textBoxes.back().setWidth(width);
        return *this;
    }

    InputRow& setTitle(string title) {
        this->textBoxes.front().setText(title);
        return *this;
    }

    InputRow& setContent(string content) {
        this->textBoxes.back().setText(content);
        return *this;
    }

    TextBox& getTitleBox() {
        return this->textBoxes.front();
    }

    TextBox& getContentBox() {
        return this->textBoxes.back();
    }

    void setDefaultType() {
        this->textBoxes.front().setIdleBgColor(IDLE_BG1);
        this->textBoxes.front().setHoverBgColor(IDLE_BG1);
        this->textBoxes.front().setIdleTextColor(IDLE_TEXT1);
        this->textBoxes.front().setHoverTextColor(IDLE_TEXT1);
        this->textBoxes.front().setIdleBorderColor(IDLE_BG1 | HOVER_TEXT1);
        this->textBoxes.front().setHoverBorderColor(IDLE_BG1 | HOVER_TEXT1);
        this->hover2Idle();
    }

    void setCursorInside() override {
        if (this->isHover == false) {
            this->textBoxes.back().setCursorInside();
            this->isHover = true;
            this->reRender = true;
            this->idle2Hover();
        }
    }

    pair<int, int> getInside() {
        return Container::getInside();
    }

    //override hover2Idle
    void hover2Idle() override {
        Container::hover2Idle();
        this->textBoxes.front().hover2Idle();
    }

    //override idle2Hover

    void idle2Hover() override {
        Container::idle2Hover();
        this->textBoxes.front().idle2Hover();
    }

    void update(pair<int, int> input = { -32 , 0 }) {
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

    void render() {
        if (this->reRender) {
            this->reRender = false;
            this->textBoxes.front().render();
        }
        this->textBoxes.back().render();
    }

};


