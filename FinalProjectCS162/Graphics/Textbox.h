#pragma once
#include "Container.h"
class TextBox : public Container {
public:

    TextBox() : Container() {
        txtEncoded = false;
    }

    TextBox(int x, int y, int width, int height, bool border = true, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15)
        : Container(x, y, width, height, border, idleBgColor, idleTextColor, idleBorderColor) {
        txtEncoded = false;
    }

    COORD findTextEnding() {
        int i = 0;
        //reset cursor
        cursor_x = this->cursor_x_min;
        cursor_y = this->cursor_y_min;
        for (auto c : text) {
            if (c == '\n') {
                cursor_x = x + 1;
                cursor_y += 1;
            }
            else {
                if (cursor_x == cursor_x_max) {
                    cursor_x = x + 1;
                    cursor_y += 1;
                }
                else cursor_x++;
            }
            i++;
        }
        COORD c;
        c.X = cursor_x;
        c.Y = cursor_y;
        return c;
    }

    //setter builder pattern
    TextBox& setText(string text) {
        this->text = text;
        return *this;
    }

    TextBox& setIdleBgColor(int idleBgColor) {
        this->idleBgColor = idleBgColor;
        return *this;
    }

    TextBox& setIdleTextColor(int idleTextColor) {
        this->idleTextColor = idleTextColor;
        return *this;
    }

    TextBox& setIdleBorderColor(int idleBorderColor) {
        this->idleBorderColor = idleBorderColor;
        return *this;
    }

    TextBox& setHoverTextColor(int hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        return *this;
    }

    TextBox& setHoverBgColor(int hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        return *this;
    }

    TextBox& setHoverBorderColor(int hoverBorderColor) {
        this->hoverBorderColor = hoverBorderColor;
        return *this;
    }

    TextBox& setTxtEncoded(bool isEncoded) {
        this->txtEncoded = isEncoded;
        return *this;
    }

    void deleteText() {
        auto c = graphics->GetConsoleCursorPosition();
        int l = getInnerWidth() * (c.Y - cursor_y_min) + (c.X - cursor_x_min + 1) - 2;
        if (l <= -1) return;
        if (l < text.length()) {
            text.erase(l, 1);
        }
        if (c.X == this->cursor_x_min) {
            c.X = this->cursor_x_max;
            --c.Y;
        }
        else --c.X;

        graphics->gotoXY(c.X, c.Y);

    }

    void addChar(char ch) {
        auto c = graphics->GetConsoleCursorPosition();
        int l = getInnerWidth() * (c.Y - cursor_y_min) + (c.X - cursor_x_min + 1) - 1;
        if (text.length() >= 1ll * getInnerWidth() * getInnerHeight() - 1) return;
        if (l > text.length()) return;
        text.insert(l, 1, ch);
        if (c.X == this->cursor_x_max || ch == '\n') {
            c.X = this->cursor_x_min;
            ++c.Y;
        }
        else ++c.X;

        graphics->gotoXY(c.X, c.Y);
    }

    void render() {
        assert(text.length() < 1ll * getInnerWidth() * getInnerHeight());
        if (!this->reRender) return;
        this->reRender = false;
        graphics->drawRect(x, y, width, height, border, bgColor, borderColor);
        outputText();
        graphics->color(0);
    };

    void update(pair<int, int> input = { -32 , 0 }) {
        COORD c = graphics->GetConsoleCursorPosition();
        if (c.X <= cursor_x_max && c.X >= cursor_x_min && c.Y <= cursor_y_max && c.Y >= cursor_y_min) {

            if (this->isHover == false) {
                this->isHover = true;
                COORD c = findTextEnding();
                graphics->gotoXY(c.X, c.Y);
                idle2Hover();
            }
            if (!this->isMutable) return;
            if (input.second == INPUT_CODE::BACKSPACE) {
                if (c.X == cursor_x_min && c.Y == cursor_y_min) {
                    return;
                }
                this->reRender = true;
                deleteText();
            }
            else if (input.second == INPUT_CODE::ENTER) {
                /*addChar('\n');
                COORD c = findTextEnding();
                graphics.gotoXY(c.X, c.Y);*/
            }
            else if (input.first != -32) {
                addChar(input.second);
                this->reRender = true;
            }


        }
        else {
            if (this->isHover == true) {
                this->isHover = false;
                //graphics.showCursor();
                if (!this->isMutable) return;
                hover2Idle();
            }
            this->isHover = false;
        }
    };

};



