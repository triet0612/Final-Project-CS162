#include "Table.h"

Table::Table() : Container() {
    columns = 0;
    width = 1;
    this->maxRow = 2;
    this->curPage = 0;
    this->curRow = 1;
    this->maxPage = 1;
    rows.push_back(RowContainer());
}

Table::Table(int x, int y, int maxRow, bool border, int idleBgColor, int idleTextColor, int idleBorderColor)
    : Container(x, y, 3, 3, border, idleBgColor, idleTextColor, idleBorderColor) {
    this->reset();
    this->maxRow = maxRow;
    RowContainer title = RowContainer(this->x, this->y, 4, false);
    rows.push_back(title);
}

void Table::reset(bool includeFormat) {
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

void Table::setDefaultType() {
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

void Table::setDefaultType0() {
    for (int i = 0; i < this->columns; ++i) {
        this->getRow(0).setBoxIdleBgColor(i, IDLE_BG0);
        this->getRow(0).setBoxIdleTextColor(i, IDLE_TEXT0);
        this->getRow(0).setIdleTextColor(IDLE_TEXT0);
    }
    this->getRow(0).hover2Idle();

    for (auto it = this->rows.begin() + 1; it != this->rows.end(); ++it) {
        auto& elem = *it;
        elem.setHoverBgColor(DEFAULT_COLOR::HOVER_BG0).setHoverTextColor(DEFAULT_COLOR::HOVER_TEXT0);
        for (int j = 0; j < this->columns; j++)
        {
            elem.setBoxIdleBgColor(j, DEFAULT_COLOR::IDLE_BG0);
            elem.setBoxHoverBgColor(j, DEFAULT_COLOR::HOVER_BG0);
            elem.setBoxHoverTextColor(j, DEFAULT_COLOR::HOVER_TEXT0);
            elem.setBoxIdleTextColor(j, DEFAULT_COLOR::IDLE_TEXT0);
            elem.hover2Idle();
        }
    }
}

void Table::setDefaultType2() {
    for (int i = 0; i < this->columns; ++i) {
        this->getRow(0).setBoxIdleBgColor(i, IDLE_BG2);
        this->getRow(0).setBoxIdleTextColor(i, IDLE_TEXT2);
        this->getRow(0).setIdleTextColor(IDLE_TEXT2);
    }
    this->getRow(0).hover2Idle();

    for (auto it = this->rows.begin() + 1; it != this->rows.end(); ++it) {
        auto& elem = *it;
        elem.setHoverBgColor(DEFAULT_COLOR::HOVER_BG2).setHoverTextColor(DEFAULT_COLOR::HOVER_TEXT2);
        for (int j = 0; j < this->columns; j++)
        {
            elem.setBoxIdleBgColor(j, DEFAULT_COLOR::IDLE_BG2);
            elem.setBoxHoverBgColor(j, DEFAULT_COLOR::HOVER_BG2);
            elem.setBoxHoverTextColor(j, DEFAULT_COLOR::HOVER_TEXT2);
            elem.setBoxIdleTextColor(j, DEFAULT_COLOR::IDLE_TEXT2);
            elem.hover2Idle();
        }
    }
}

RowContainer& Table::getRow(int index) {
    assert(index < rows.size() && index >= 0);
    return rows[index];
}

void Table::setRowsIdleBgColor(int bgColor) {
    for (auto it = rows.begin() + 1; it != rows.end(); ++it) {
        it->data.setIdleBgColor(bgColor);
    }
}

void Table::setRowsIdleTextColor(int textColor) {
    for (auto it = rows.begin() + 1; it != rows.end(); ++it) {
        it->data.setIdleTextColor(textColor);
    }
}

void Table::setRowsHoverBgColor(int bgColor) {
    for (auto it = rows.begin() + 1; it != rows.end(); ++it) {
        it->data.setHoverBgColor(bgColor);
    }
}

void Table::setCursorOnRow(int row) {
    if (row >= this->rows.size()) row = this->rows.size() - 1;
    if (row <= 0) row = 1;
    this->rows[row].setCursorInside();
    this->curRow = row;
}

int Table::getPage(int row) {
    assert(this->maxRow > 1);
    return (row - 1) / (this->maxRow - 1);
}

int Table::getCurRow() {
    return this->curRow;
}

int Table::getCurPage() {
    return this->getPage(this->curRow);
}

int Table::getTotalRows() {
    return this->rows.size();
}

int Table::getRelCurRow() {
    assert(this->maxRow > 1);
    int shrink = (this->curRow - 1) % (this->maxRow - 1) + 1;
    if (this->curPage * (this->maxRow - 1) + shrink < this->rows.size()) return this->curPage * (this->maxRow - 1) + shrink;
    return this->rows.size() - 1;
}

void Table::setRowsHoverTextColor(int textColor) {
    for (auto it = rows.begin() + 1; it != rows.end(); ++it) {
        it->data.setHoverTextColor(textColor);
    }
}

void Table::defaultPressAnimation() {
    this->getRow(this->getCurRow()).hover2Idle();
    this->getRow(this->getCurRow()).render();
    graphics->hideCursor();
    Sleep(50);
    this->getRow(this->getCurRow()).idle2Hover();
    this->getRow(this->getCurRow()).render();
    graphics->hideCursor();
}

void Table::defaultProc() {
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

void Table::renderRows() {
    assert(this->curPage <= this->maxPage);
    ;
    for (int i = 1; i < this->maxRow; ++i) {
        if (this->curPage * (this->maxRow - 1) + i >= this->rows.size()) break;
        rows[this->curPage * (this->maxRow - 1) + i].render();
    }
}

void Table::reloadPage() {
    for (int i = 1; i < this->maxRow; ++i) {
        if (this->curPage * (this->maxRow - 1) + i >= this->rows.size()) break;
        rows[this->curPage * (this->maxRow - 1) + i].hover2Idle();
    }
}

void Table::updateRows(pair<int, int> input) {
    assert(this->curPage <= this->maxPage);
    rows.front().update();
    for (int i = 1; i < this->maxRow; ++i) {
        if (this->curPage * (this->maxRow - 1) + i >= this->rows.size()) break;
        rows[this->curPage * (this->maxRow - 1) + i].update();
    }
}

bool Table::focusRow(int row) {
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

bool Table::switchPage(int page) {
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

void Table::update(pair<int, int> input, function<void(Table&)> proc) {
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

void Table::render() {
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
