#pragma once
#include "SinglyLinkedList.h"
#include "Textbox.h"
class RowContainer : public Container {
private:
    SinglyLinkedList<TextBox> textBoxes;
    int columns;
public:

    RowContainer();

    RowContainer(int x, int y, int height, bool border = true, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15);

    template<class ... Args>
    void addTextBox_back(Args ... lenBoxes);

    template<class ... Args>
    void addText(Args ... txtCols);

    int getColumns();

    RowContainer& addColumn(TextBox& textBox);

    RowContainer& addColumn(TextBox&& textBox);

    void setBoxHoverTextColor(int index, int hoverTextColor);

    void setBoxHoverBgColor(int index, int hoverBgColor);

    void setBoxHoverBorderColor(int index, int hoverBorderColor);

    void setBoxText(int index, string text);

    void setBoxIdleTextColor(int index, int idleTextColor);

    void setBoxIdleBgColor(int index, int idleBgColor);

    void setBoxIdleBorderColor(int index, int idleBorderColor);

    void copyFormat(const RowContainer& rc);

    RowContainer& setHoverTextColor(int hoverTextColor);

    RowContainer& setHoverBgColor(int hoverBgColor);

    RowContainer& setHoverBorderColor(int hoverBorderColor);

    RowContainer& setIdleTextColor(int idleTextColor);

    RowContainer& setIdleBgColor(int idleBgColor);

    void idle2Hover() override;

    void hover2Idle() override;

    void update(pair<int, int> input = { -32 , 0 });;

    void drawBarriers();


    void render();;

};

template<class ...Args>
void RowContainer::addTextBox_back(Args ...lenBoxes) {
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

template<class ...Args>
void RowContainer::addText(Args ...txtCols) {
    int len = sizeof...(txtCols);
    assert(len <= this->columns);
    //if (len == 0) return;
    auto it = this->textBoxes.begin();
    for (string txt : { txtCols... }) {
        it->data.setText(txt);
        it++;
    }
}
