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
    Table();

    Table(int x, int y, int maxRow, bool border = true, int idleBgColor = 0, int idleTextColor = 15, int idleBorderColor = 15);

    void reset(bool includeFormat = true);

    void setDefaultType();

    void setDefaultType0();

    void setDefaultType2();

    template<class ... Args>
    void addTitleRow_back(Args ... lenBoxes);

    template<class ... Args>
    void addRow_back(Args ... txts);

    RowContainer& getRow(int index);

    void setRowsIdleBgColor(int bgColor);

    void setRowsIdleTextColor(int textColor);

    void setRowsHoverBgColor(int bgColor);

    void setCursorOnRow(int row);

    int getPage(int row);

    int getCurRow();

    int getCurPage();

    int getTotalRows();

    int getRelCurRow();

    void setRowsHoverTextColor(int textColor);

    void defaultPressAnimation();

    void defaultProc();

    void renderRows();

    void reloadPage();

    void updateRows(pair<int, int> input = { -32 , 0 });

    bool focusRow(int row);

    bool switchPage(int page);

    void update(pair<int, int> input = { -32 , 0 }, function<void(Table&)> proc = [](Table& t) {t.defaultProc(); });

    void render();

};

template<class ...Args>
inline void Table::addTitleRow_back(Args ...lenBoxes) {
    for (auto len : { lenBoxes... }) {
        width += len - 1;
        formatCols.push_back(len);
    }

    rows[0].addTextBox_back(lenBoxes...);
    this->columns = rows[0].getColumns();

}

template<class ...Args>
inline void Table::addRow_back(Args ...txts) {
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
    this->maxPage = (this->rows.size() - 2) / (this->maxRow - 1);
    height = min(rows.size(), this->maxRow) + this->rows[0].getHeight() - 1;
    this->initSecondaryVariables();
}
