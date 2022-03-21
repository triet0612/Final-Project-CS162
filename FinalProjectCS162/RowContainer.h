#pragma once
#include "SinglyLinkedList.h"
#include "Textbox.h"
class RowContainer : public Container {
private:
    SinglyLinkedList<TextBox> textBoxes;
    int columns;
public:

    RowContainer() : Container() {
        columns = 1;
        width = 1;
    }

    RowContainer(int x, int y, int height, bool border = true, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15)
        : Container(x, y, 3, height, border, idleBgColor, idleTextColor, idleBorderColor) {
        columns = 0;
        width = 1;
    }

    template<class ... Args>
    void addTextBox_back(Args ... lenBoxes) {
        int len = sizeof...(lenBoxes);
        int x = this->textBoxes.size() == 0 ? this->getX() : this->textBoxes.back().getX() + this->textBoxes.back().getWidth() - 1;
        int y = this->textBoxes.size() == 0 ? this->getY() : this->textBoxes.back().getY();
        for (auto len : { lenBoxes... }) {
            TextBox tb(x, y, len, this->height, false, this->idleBgColor, this->idleTextColor, this->idleBorderColor);
            this->textBoxes.push_back(tb);
            x += len - 1;
            width += len - 1;
            columns++;
        }
        this->initSecondaryVariables();
    }

    template<class ... Args>
    void addText(Args ... txtCols) {
        int len = sizeof...(txtCols);
        assert(len <= this->columns);
        //if (len == 0) return;
        auto it = this->textBoxes.begin();
        for (auto txt : { txtCols... }) {
            it->data.setText(txt);
            it++;
        }
    }

    int getColumns() {
        return columns;
    }

    RowContainer& addColumn(TextBox& textBox) {
        textBoxes.push_back(textBox);
        ++columns;
        return *this;
    }

    RowContainer& addColumn(TextBox&& textBox) {
        textBoxes.push_back(textBox);
        ++columns;
        return *this;
    }

    void setBoxHoverTextColor(int index, int hoverTextColor) {
        textBoxes[index].setHoverTextColor(hoverTextColor);
    }

    void setBoxHoverBgColor(int index, int hoverBgColor) {
        textBoxes[index].setHoverBgColor(hoverBgColor);
    }

    void setBoxHoverBorderColor(int index, int hoverBorderColor) {
        textBoxes[index].setHoverBorderColor(hoverBorderColor);
    }

    void setBoxText(int index, string text) {
        textBoxes[index].setText(text);
    }

    void setBoxIdleTextColor(int index, int idleTextColor) {
        textBoxes[index].setIdleTextColor(idleTextColor);
    }

    void setBoxIdleBgColor(int index, int idleBgColor) {
        textBoxes[index].setIdleBgColor(idleBgColor);
    }

    void setBoxIdleBorderColor(int index, int idleBorderColor) {
        textBoxes[index].setIdleBorderColor(idleBorderColor);
    }

    void copyFormat(const RowContainer& rc) {

        this->textBoxes = rc.textBoxes;
        this->width = rc.width;
        this->height = rc.height;
        this->columns = rc.columns;
        this->initSecondaryVariables();
    }

    RowContainer& setHoverTextColor(int hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        return *this;
    }

    RowContainer& setHoverBgColor(int hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        return *this;
    }

    RowContainer& setHoverBorderColor(int hoverBorderColor) {
        this->hoverBorderColor = hoverBorderColor;
        return *this;
    }

    RowContainer& setIdleTextColor(int idleTextColor) {
        this->idleTextColor = idleTextColor;
        return *this;
    }

    RowContainer& setIdleBgColor(int idleBgColor) {
        this->idleBgColor = idleBgColor;
        return *this;
    }

    void idle2Hover() override {
        Container::idle2Hover();
        for (auto& textBox : textBoxes) {
            textBox.idle2Hover();
        }

    }

    void hover2Idle() override {
        Container::hover2Idle();
        for (auto& textBox : textBoxes) {
            textBox.hover2Idle();
        }

    }

    void update(pair<int, int> input = { -32 , 0 }) {
        if (this->isMouseInContainer()) {

            if (this->isHover == false) {
                this->isHover = true;
                this->reRender = true;
                idle2Hover();
            }
            if (!this->isMutable) return;
            for (auto& x : this->textBoxes) x.update(input);

        }
        else {
            if (this->isHover == true) {
                this->isHover = false;
                this->reRender = true;
                hover2Idle();
            }
            if (!this->isMutable) return;
            for (auto& x : this->textBoxes) x.update(input);

        }
    };

    void drawBarriers() {
        for (auto it = textBoxes.begin() + 1; it != textBoxes.end(); ++it) {
            graphics->gotoAndReturn([&]() {
                for (int i = 0; i < this->getHeight() - 2; ++i) {
                    graphics->gotoXY(it->data.getX(), it->data.getY() + i + 1);
                    graphics->color(this->textColor);
                    cout << char(ASCII::DASH_VERTICAL);
                }

                });
        }
    }


    void render() {
        if (this->reRender) {
            this->reRender = false;
            graphics->drawRect(x, y, width, height, border, bgColor, borderColor);
            graphics->fillRect(x, y, width, height, bgColor);
            drawBarriers();
            for (auto& x : this->textBoxes) {
                x.setRerender();
            }
        }

        for (auto& x : this->textBoxes) {
            x.render();
        }

    };

};


