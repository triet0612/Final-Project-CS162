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
    bool txtEncoded;

    //set default color option
    void setDefaultColorOption();;

    void initGeometry();

    void initSecondaryVariables();;
public:
    Container();;

    Container(int x, int y, int width, int height, bool border = true, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15);;

    void setRerender();

    void setX(int x);

    void setY(int y);

    void setXY(int x, int y);

    void setWidth(int width);

    void setHeight(int height);

    void setBorder(bool flag);

    virtual void setCursorInside();

    int getInnerWidth();;

    int getInnerHeight();;

    int getX();;
    int getY();;
    int getWidth();;
    int getHeight();;
    string getText();

    pair<int, int> getInside();

    virtual void hover2Idle();

    virtual void idle2Hover();

    void outputText();;

    bool isPosInContainer(COORD c);

    bool isMouseInContainer();;


};
