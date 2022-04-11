#pragma once
#include "Container.h"
#include "Textbox.h"
class InputRow : private Container {
private:
    SinglyLinkedList<TextBox> textBoxes;
    int titleBoxWidth, contentBoxWidth;
public:
    InputRow();

    InputRow(int x, int y, int width, int height, int bgColor, int textColor);

    InputRow& setTitleBoxWidth(int width);

    InputRow& setContentBoxWidth(int width);

    InputRow& setTitle(string title);

    InputRow& setContent(string content);

    TextBox& getTitleBox();

    TextBox& getContentBox();

    void setDefaultType0();

    void setDefaultType();


    void setDefaultType2();

    void setDefaultType3();

    void setDefaultType4();

    bool checkMouseInsideContentBox();

    bool checkPosInsideContentBox(COORD c);

    void setCursorInside() override;

    pair<int, int> getInside();

    void hover2Idle() override;

    void idle2Hover() override;

    void update(pair<int, int> input = { -32 , 0 });

    void render();

};


