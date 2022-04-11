#include "RowContainer.h"

RowContainer::RowContainer() : Container() {
    columns = 1;
    width = 1;
}

RowContainer::RowContainer(int x, int y, int height, bool border, int idleBgColor, int idleTextColor, int idleBorderColor)
    : Container(x, y, 3, height, border, idleBgColor, idleTextColor, idleBorderColor) {
    columns = 0;
    width = 1;
}

int RowContainer::getColumns() {
    return columns;
}

RowContainer& RowContainer::addColumn(TextBox& textBox) {
    textBoxes.push_back(textBox);
    ++columns;
    return *this;
}

RowContainer& RowContainer::addColumn(TextBox&& textBox) {
    textBoxes.push_back(textBox);
    ++columns;
    return *this;
}

void RowContainer::setBoxHoverTextColor(int index, int hoverTextColor) {
    textBoxes[index].setHoverTextColor(hoverTextColor);
}

void RowContainer::setBoxHoverBgColor(int index, int hoverBgColor) {
    textBoxes[index].setHoverBgColor(hoverBgColor);
}

void RowContainer::setBoxHoverBorderColor(int index, int hoverBorderColor) {
    textBoxes[index].setHoverBorderColor(hoverBorderColor);
}

void RowContainer::setBoxText(int index, string text) {
    textBoxes[index].setText(text);
}

void RowContainer::setBoxIdleTextColor(int index, int idleTextColor) {
    textBoxes[index].setIdleTextColor(idleTextColor);
}

void RowContainer::setBoxIdleBgColor(int index, int idleBgColor) {
    textBoxes[index].setIdleBgColor(idleBgColor);
}

void RowContainer::setBoxIdleBorderColor(int index, int idleBorderColor) {
    textBoxes[index].setIdleBorderColor(idleBorderColor);
}

void RowContainer::copyFormat(const RowContainer& rc) {

    this->textBoxes = rc.textBoxes;
    this->width = rc.width;
    this->height = rc.height;
    this->columns = rc.columns;
    this->initSecondaryVariables();
}

RowContainer& RowContainer::setHoverTextColor(int hoverTextColor) {
    this->hoverTextColor = hoverTextColor;
    return *this;
}

RowContainer& RowContainer::setHoverBgColor(int hoverBgColor) {
    this->hoverBgColor = hoverBgColor;
    return *this;
}

RowContainer& RowContainer::setHoverBorderColor(int hoverBorderColor) {
    this->hoverBorderColor = hoverBorderColor;
    return *this;
}

RowContainer& RowContainer::setIdleTextColor(int idleTextColor) {
    this->idleTextColor = idleTextColor;
    return *this;
}

RowContainer& RowContainer::setIdleBgColor(int idleBgColor) {
    this->idleBgColor = idleBgColor;
    return *this;
}

void RowContainer::idle2Hover() {
    Container::idle2Hover();
    for (auto& textBox : textBoxes) {
        textBox.idle2Hover();
    }

}

void RowContainer::hover2Idle() {
    Container::hover2Idle();
    for (auto& textBox : textBoxes) {
        textBox.hover2Idle();
    }

}

void RowContainer::update(pair<int, int> input) {
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
}

void RowContainer::drawBarriers() {
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

void RowContainer::render() {
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

}
