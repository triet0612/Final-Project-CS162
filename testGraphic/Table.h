#pragma once
#include "RowContainer.h"
#include <string>
class Table : public Container {
private:
    SinglyLinkedList<RowContainer> rows;
    SinglyLinkedList<int> formatCols;
    int columns;
    int maxRow, curRow;
    int curPage, maxPage;
    
public:
    friend void tableProc(Table&);
    Table() : Container() {
        columns = 0;
        width = 1;
        this->maxRow = 2;
        this->curPage = 0;
        this->curRow = 1;
        this->maxPage = 1;
        rows.push_back(RowContainer());
    }

    Table(int x, int y, int maxRow, bool border = true, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15)
        : Container(x, y, 3, 3, border, idleBgColor, idleTextColor, idleBorderColor) {
        this->reset();
        this->maxRow = maxRow;
        RowContainer title = RowContainer(this->x, this->y,4, false);
        rows.push_back(title);
    }

    void reset(bool includeFormat = true) {
        this->columns = 0;
        this->width = 1;
        this->height = 1;
        this->cursor_x = x;
        this->cursor_y = y;
        this->maxRow = maxRow;
        this->curPage = 0;
        this->curRow = 1;
        this->maxPage = 1;
        if (!includeFormat) {
            RowContainer title = rows[0];
            rows.clear();
            rows.push_back(title);
        }
        else rows.clear();
        
    }

    void setDefaultType() {
        for (int i = 0; i < this->columns; ++i) {
            this->getRow(0).setBoxIdleBgColor(i, IDLE_BG1);
            this->getRow(0).setBoxIdleTextColor(i, IDLE_TEXT1);
            this->getRow(0).setIdleTextColor(IDLE_TEXT1);
        }
        this->getRow(0).hover2Idle();

        for (auto it = this->rows.begin() + 1; it != this->rows.end(); ++it) {
            auto& elem = *it;
            elem.setHoverBgColor(DEFAULT_COLOR::HOVER_BG).setHoverTextColor(DEFAULT_COLOR::HOVER_TEXT);
            for (int j = 0; j < this->columns; j++)
            {
                elem.setBoxIdleBgColor(j, DEFAULT_COLOR::IDLE_BG);
                elem.setBoxHoverBgColor(j, DEFAULT_COLOR::HOVER_BG);
                elem.setBoxHoverTextColor(j, DEFAULT_COLOR::HOVER_TEXT);
                elem.setBoxIdleTextColor(j, DEFAULT_COLOR::IDLE_TEXT);
                elem.hover2Idle();
            }
        }
    }

    template<class ... Args>
    void addTitleRow_back(Args ... lenBoxes) {
        for (auto len : { lenBoxes... }) {
            width += len - 1;
            formatCols.push_back(len);
        }

        rows[0].addTextBox_back(lenBoxes...);
        this->columns = rows[0].getColumns();
        
    }

    template<class ... Args>
    void addRow_back(Args ... txts) {
        int len = sizeof...(txts);
        assert(len <= columns);
        assert(this->maxRow > 1);
        int lstId = (this->rows.size() - 1) % (this->maxRow - 1);

        int x = rows[lstId].getX();
        int y = rows[lstId].getY() + rows[lstId].getHeight() - 2;

        RowContainer row(x, y, 3, false);
        for (auto w : formatCols) row.addTextBox_back(w);
        
        row.addText(txts...);
        rows.push_back(row);
        columns = formatCols.size();
        if (rows.size() == 2) {
            this->cursor_x = x + 1;
            this->cursor_y = y + 1;
            this->curRow = 1;
        }
        this->maxPage = (this->rows.size() - 1) / (this->maxRow - 1);
        height = min(rows.size(), this->maxRow) + this->rows[0].getHeight() - 1;
        this->initSecondaryVariables();
    }

    RowContainer& getRow(int index) {
        assert(index < rows.size() && index >= 0);
        return rows[index];
    }

    void setRowsIdleBgColor(int bgColor) {
        for (auto it = rows.begin() + 1; it != rows.end(); ++it) {
            it->data.setIdleBgColor(bgColor);
        }
    }

    void setRowsIdleTextColor(int textColor) {
        for (auto it = rows.begin() + 1; it != rows.end(); ++it) {
            it->data.setIdleTextColor(textColor);
        }
    }

    void setRowsHoverBgColor(int bgColor) {
        for (auto it = rows.begin() + 1; it != rows.end(); ++it) {
            it->data.setHoverBgColor(bgColor);
        }
    }

    int getPage(int row) {
        assert(this->maxRow > 1);
        return (row - 1) / (this->maxRow - 1);
    }

    int getCurRow() {
        return this->curRow;
    }

    int getCurPage() {
        return this->getPage(this->curRow);
    }

    int getRelCurRow() {
        assert(this->maxRow > 1);
        int shrink = (this->curRow - 1) % (this->maxRow - 1) + 1;
        if (this->curPage * (this->maxRow - 1) + shrink < this->rows.size()) return this->curPage * (this->maxRow - 1) + shrink;
        return this->rows.size() - 1;
    }

    void setRowsHoverTextColor(int textColor) {
        for (auto it = rows.begin() + 1; it != rows.end(); ++it) {
            it->data.setHoverTextColor(textColor);
        }
    }

    void defaultPressAnimation() {
        this->getRow(this->getCurRow()).hover2Idle();
        this->getRow(this->getCurRow()).render();
        graphics->hideCursor();
        Sleep(50);
        this->getRow(this->getCurRow()).idle2Hover();
        this->getRow(this->getCurRow()).render();
        graphics->hideCursor();
    }

    void defaultProc() {
        graphics->loopBoolean([&](pair<int, int> input) {
            int y = 0, x = 0;
            if (input.first == INPUT_CODE::ESC) return false;
            if (input.first == INPUT_CODE::ENTER) {
                this->defaultPressAnimation();
            }
            else if (input.first == INPUT_CODE::DIRECTION) {
                graphics->getNextDirection(input, x, y);

                this->switchPage(this->getCurPage() + x);
                this->focusRow(this->getCurRow() + y);

                graphics->hideCursor();
            }
            return true;
            });
    }

    void renderRows() {
        assert(this->curPage <= this->maxPage);
        ;
        for (int i = 1; i < this->maxRow; ++i) {
            if (this->curPage * (this->maxRow - 1) + i >= this->rows.size()) break;
            rows[this->curPage * (this->maxRow - 1) + i].render();
        }
    }

    void reloadPage() {
        for (int i = 1; i < this->maxRow; ++i) {
            if (this->curPage * (this->maxRow - 1) + i >= this->rows.size()) break;
            rows[this->curPage * (this->maxRow - 1) + i].hover2Idle();
        }
    }

    void updateRows(pair<int, int> input = { -32 , 0 }) {
        assert(this->curPage <= this->maxPage);
        rows.front().update();
        for (int i = 1; i < this->maxRow; ++i) {
            if (this->curPage * (this->maxRow - 1) + i >= this->rows.size()) break;
            rows[this->curPage * (this->maxRow - 1) + i].update();
        }
    }

    bool focusRow(int row) {
        if (row >= this->rows.size() || row <= 0) return false;
        if (row == this->getCurRow()) return false;

        this->getRow(this->curRow).hover2Idle();
        this->getRow(this->curRow).render();

        int nwPage = this->getPage(row);
        if (this->curPage != nwPage) {
            if (this->curPage < nwPage) this->curRow = 1;
            else 
                this->curRow = this->maxRow - 1;
            return this->switchPage(nwPage);
        }
        
        this->curRow = row;
        this->getRow(this->curRow).idle2Hover();
        this->getRow(this->curRow).render();
        return true;
    }

    bool switchPage(int page) {
        if (page < 0 || page > this->maxPage) return false;
        if (page == this->curPage) return false;
        this->curPage = page;
        this->curRow = this->getRelCurRow();
        this->reloadPage();
        this->setRerender();
        this->getRow(curRow).idle2Hover();
        this->getRow(curRow).render();

        this->render();

        return true;
    }

    void update(pair<int, int> input = { -32 , 0 }, function<void(Table&)> proc = [](Table& t) {t.defaultProc(); }) {
        if (this->isMouseInContainer()) {
            if (this->isHover == false) {
                this->isHover = true;
                this->reRender = true;

                COORD c = graphics->getLastPos();
                graphics->gotoXY(this->cursor_x, this->cursor_y);
                this->getRow(this->curRow).idle2Hover();
                this->render();
                graphics->hideCursor();

                proc(*this);

                graphics->showCursor();
                graphics->gotoXY(c.X, c.Y);
                
            }

        }
        else {
            if (this->isHover == true) {
                this->isHover = false;
                this->reRender = true;
            }
        }

        updateRows(input);
    }

    void render() {
        if (this->reRender) {
            this->reRender = false;
            graphics->drawRect(x, y, width, height, true);
            graphics->fillRect(x, y, width, height);
            for (auto& row : this->rows) {
                row.setRerender();
            }
            rows.front().render();
        }
        renderRows();
    }

};
