#include "Container.h"


//set default color option

void Container::setDefaultColorOption() {
    this->hoverBgColor = idleBgColor;           this->bgColor = this->idleBgColor;
    this->hoverTextColor = idleTextColor;       this->textColor = this->idleTextColor;
    this->hoverBorderColor = idleBorderColor;   this->borderColor = this->idleBorderColor;
}

void Container::initGeometry() {
    this->cursor_x = x + 1;                     this->cursor_y = y + 1;
    this->cursor_x_max = x + width - 2;         this->cursor_y_max = y + height - 2;
    this->cursor_x_min = x + 1;                 this->cursor_y_min = y + 1;
}

void Container::initSecondaryVariables() {
    this->text = "";
    this->initGeometry();
    this->isClick = false;                      this->isHover = false;
    this->setDefaultColorOption();
    graphics = &ConsoleGraphics::getInstance();
    this->isMutable = true;
    this->reRender = true;
    this->txtEncoded = false;
}

Container::Container() {
    x = 0, y = 0;
    width = 3, height = 3;
    border = true;
    this->border = true;                  this->idleBgColor = 0;
    this->idleTextColor = 15;             this->idleBorderColor = 15;
    initSecondaryVariables();
}

Container::Container(int x, int y, int width, int height, bool border, int idleBgColor, int idleTextColor, int idleBorderColor) {
    assert(width > 2 && height > 2);
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->border = border;
    this->idleBgColor = idleBgColor;
    this->idleTextColor = idleTextColor;
    this->idleBorderColor = idleBorderColor;
    initSecondaryVariables();
}

void Container::setRerender() {
    this->reRender = true;
}

void Container::setX(int x) {
    this->x = x;
    this->initGeometry();
}

void Container::setY(int y) {
    this->y = y;
    this->initGeometry();
}

void Container::setXY(int x, int y) {
    this->x = x;
    this->y = y;
    this->initGeometry();
}

void Container::setWidth(int width) {
    this->width = width;
    this->initGeometry();
}

void Container::setHeight(int height) {
    this->height = height;
    this->initGeometry();
}

void Container::setBorder(bool flag) {
    this->border = flag;
}

void Container::setCursorInside() {
    graphics->gotoXY(this->cursor_x_min, this->cursor_y_min, true);
}

int Container::getInnerWidth() {
    return cursor_x_max - cursor_x_min + 1;
}

int Container::getInnerHeight() {
    return cursor_y_max - cursor_y_min + 1;
}

int Container::getX() {
    return x;
}

int Container::getY() {
    return y;
}

int Container::getWidth() {
    return width;
}

int Container::getHeight() {
    return height;
}

string Container::getText() {
    return this->text;
}

pair<int, int> Container::getInside() {
    return { this->cursor_x_min, this->cursor_y_min };
}

void Container::hover2Idle() {
    bgColor = idleBgColor;
    textColor = idleTextColor;
    borderColor = idleBorderColor;
    this->reRender = true;
}

void Container::idle2Hover() {
    bgColor = hoverBgColor;
    textColor = hoverTextColor;
    borderColor = hoverBorderColor;
    this->reRender = true;
}

void Container::outputText() {
    graphics->gotoAndReturn([&]() {
        //cout << text;
        cursor_x = this->cursor_x_min - 1;
        cursor_y = this->cursor_y_min;
        for (auto c : text) {
            if (c == '\n') {
                for (int i = cursor_x + 1; i <= cursor_x_max; i++) {
                    graphics->gotoXY(i, cursor_y);
                    graphics->color(bgColor);
                    cout << " ";
                }
                cursor_x = this->cursor_x_min - 1;
                cursor_y += 1;
            }
            else {
                if (cursor_x >= cursor_x_max) {
                    cursor_x = this->cursor_x_min;
                    cursor_y += 1;
                }
                else cursor_x++;
            }
            this->graphics->gotoXY(cursor_x, cursor_y);
            this->graphics->color(textColor);
            if (txtEncoded) cout << "*";
            else cout << c;
        }

        for (int i = cursor_x + 1; i <= cursor_x_max; i++) {
            graphics->gotoXY(i, cursor_y);
            graphics->color(bgColor);
            cout << " ";
        }

        for (int i = cursor_y + 1; i <= cursor_y_max; i++) {
            for (int j = cursor_x_min; j <= cursor_x_max; j++) {
                graphics->gotoXY(j, i);
                graphics->color(bgColor);
                cout << " ";
            }
        }
        });
}

bool Container::isPosInContainer(COORD c) {
    return (c.X <= cursor_x_max && c.X >= cursor_x_min && c.Y <= cursor_y_max && c.Y >= cursor_y_min);
}

bool Container::isMouseInContainer() {
    return isPosInContainer(graphics->GetConsoleCursorPosition());
}
