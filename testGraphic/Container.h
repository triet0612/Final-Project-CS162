#pragma once
#include "ConsoleGraphics.h"
#include <assert.h>
class Container {
protected:
    int x, y, width, height;
    string text;
    bool border, reRender;

    int cursor_x, cursor_y;
    int cursor_x_max, cursor_y_max;
    int cursor_x_min, cursor_y_min;
    ConsoleGraphics* graphics;
    int bgColor, textColor, borderColor;
    int hoverBgColor, hoverTextColor, hoverBorderColor;
    int idleBgColor, idleTextColor, idleBorderColor;
    bool isClick, isHover, isMutable;

    //set default color option
    void setDefaultColorOption() {
        this->hoverBgColor = idleBgColor;           this->bgColor = this->idleBgColor;
        this->hoverTextColor = idleTextColor;       this->textColor = this->idleTextColor;
        this->hoverBorderColor = idleBorderColor;   this->borderColor = this->idleBorderColor;
    };

    void initGeometry() {
        this->cursor_x = x + 1;                     this->cursor_y = y + 1;
        this->cursor_x_max = x + width - 2;         this->cursor_y_max = y + height - 2;
        this->cursor_x_min = x + 1;                 this->cursor_y_min = y + 1;
    }

    void initSecondaryVariables() {
        this->text = "";
        this->initGeometry();
        this->isClick = false;                      this->isHover = false;
        this->setDefaultColorOption();
        graphics = &ConsoleGraphics::getInstance();
        this->isMutable = true;
        this->reRender = true;
    };
public:
    Container() {
        x = 0, y = 0;
        width = 3, height = 3;
        border = true;
        this->border = true;                  this->idleBgColor = 0;
        this->idleTextColor = 15;             this->idleBorderColor = 15;
        initSecondaryVariables();
    };

    Container(int x, int y, int width, int height, bool border = true, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15) {
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
    };

    void setRerender() {
        this->reRender = true;
    }

    void setX(int x) {
        this->x = x;
        this->initGeometry();
    }

    void setY(int y) {
        this->y = y;
        this->initGeometry();
    }

    void setXY(int x, int y) {
        this->x = x;
        this->y = y;
        this->initGeometry();
    }

    void setWidth(int width) {
        this->width = width;
        this->initGeometry();
    }

    void setHeight(int height) {
        this->height = height;
        this->initGeometry();
    }

    void setBorder(bool flag) {
        this->border = flag;
    }

    virtual void setCursorInside() {
        graphics->gotoXY(this->cursor_x_min, this->cursor_y_min, true);
    }

    int getInnerWidth() {
        return cursor_x_max - cursor_x_min + 1;
    };

    int getInnerHeight() {
        return cursor_y_max - cursor_y_min + 1;
    };

    int getX() {
        return x;
    };
    int getY() {
        return y;
    };
    int getWidth() {
        return width;
    };
    int getHeight() {
        return height;
    };
    pair<int, int> getInside() {
        return { this->cursor_x_min, this->cursor_y_min };
    }

    virtual void hover2Idle() {
        bgColor = idleBgColor;
        textColor = idleTextColor;
        borderColor = idleBorderColor;
        this->reRender = true;
    }

    virtual void idle2Hover() {
        bgColor = hoverBgColor;
        textColor = hoverTextColor;
        borderColor = hoverBorderColor;
        this->reRender = true;
    }

    void outputText() {
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
                    cursor_x = this->cursor_x_min;
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
                cout << c;
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
    };

    bool isMouseInContainer() {
        COORD c = graphics->GetConsoleCursorPosition();
        return (c.X <= cursor_x_max && c.X >= cursor_x_min && c.Y <= cursor_y_max && c.Y >= cursor_y_min);
    };
};
