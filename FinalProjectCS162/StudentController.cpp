#include "StudentController.h"

StudentController::StudentController() {
    loadData();
    curId = -1;
}

StudentController::~StudentController() {
    exportData();
}

void StudentController::regProc() {
	system("cls");
	Student student;
	//student.getGeneralData();
	list.push_back(student);
}

void StudentController::loadData() {
    ifstream ifs("Data/Student_account.txt");
    if (!ifs.is_open()) return;
    string tmp;
    getline(ifs, tmp);
    while (!ifs.eof()) {
        Student s;
        getline(ifs, tmp, ','); s.addUsername(tmp);
        if (tmp == "") break;
        getline(ifs, tmp, ','); s.addPassword(tmp);
        getline(ifs, tmp, ','); s.lastname = tmp;
        getline(ifs, tmp, ','); s.firstname = tmp;
        getline(ifs, tmp, ','); s.name = tmp;
        getline(ifs, tmp, ','); s.dob = tmp;
        getline(ifs, tmp, ','); s.gender = tmp;
        getline(ifs, tmp, ','); s.phone = tmp;
        getline(ifs, tmp); s.mail = tmp;
        s.stuId = s.username;
        list.push_back(s);
    }
    ifs.close();
}

void StudentController::exportData() {
    string path = "Data/Student_account.txt";
    ofstream out(path);
    out << "Username,Password,Lastname,Firstname,Name,Date of Birth,Gender,Phone,Email";
    for (const auto& elem : list) {
        out << "\n" << elem.username << ",";
        out << elem.pass << ",";
        out << elem.lastname << ",";
        out << elem.firstname << ",";
        out << elem.name << ",";
        out << elem.dob << ",";
        out << elem.gender << ",";
        out << elem.phone << ",";
        out << elem.mail;
    }
    out.close();
}

void StudentController::getCur(string& yearname, string& semester) {
    ifstream ifs("Data/CurrentSemester.txt");
    getline(ifs, yearname, '\n');
    getline(ifs, semester, '\n');
}

bool StudentController::loginProc(string username, string password) {
    curId = list.findIndex([&](Student s) {return s.username == username && s.pass == password; });
    return curId != -1;
}

//--

int StudentController::chooseOptions(Table& table) {
    ConsoleGraphics* graphics = &ConsoleGraphics::getInstance();
    int type = -1;
    graphics->loopBoolean([&](pair<int, int> input) {
        int y = 0, x = 0;
        if (input.first == INPUT_CODE::ESC) return false;
        if (input.first == INPUT_CODE::ENTER) {
            table.defaultPressAnimation();
            type = table.getCurRow();
            return false;
        }
        else if (input.first == INPUT_CODE::DIRECTION) {
            graphics->getNextDirection(input, x, y);

            table.switchPage(table.getCurPage() + x);
            table.focusRow(table.getCurRow() + y);

            graphics->hideCursor();
        }
        return true;

        });
    return type;
}

void StudentController::setupOptionsTable(Table& table) {
    system("cls");
    table = Table(0, 0, 6);

    table.addTitleRow_back(30);
    table.getRow(0).addText("WHAT DO YOU WANT ?");
    table.addRow_back("Enroll Courses");
    table.addRow_back("View Scores");
    table.addRow_back("View profile");
    table.addRow_back("Change password");
    table.addRow_back("Get me out the here");

    table.setDefaultType2();
    table.render();

    table.setCursorInside();
}

int StudentController::inputTypeProc() {
    int type = 0;
    Table table;
    setupOptionsTable(table);
    table.update({ -32, 0 }, [&](Table& table) {type = chooseOptions(table); });
    return type;
}

//----------------

void StudentController::setupProfileTable(Table& table) {
    system("cls");
    assert(curId >= 0);
    table = Table(0, 0, 6);

    table.addTitleRow_back(20, 30);
    Student target = list[curId];
    table.getRow(0).addText("   Categories", "       Information");
    table.addRow_back((string)"Name", target.name);
    table.addRow_back((string)"Phone", target.phone);
    table.addRow_back((string)"Mail", target.mail);
    table.addRow_back((string)"Gender", target.gender);
    table.addRow_back((string)"Date of birth", target.dob.convert2String());

    table.setDefaultType2();
    table.render();

    table.setCursorInside();

    TextBox notice = TextBox(0, 10, 20, 3, false).setText("Press ESC to exit");
    notice.render();
}

void StudentController::viewProfileProc() {
    Table table;
    setupProfileTable(table);
    table.update();
}

//----------------

void StudentController::setupVerifPassInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {
    for (int i = 0; i < 1; ++i) {
        inputList.push_back(InputRow(5, 4 * i + 1, 50, 3, 0, 15));
        pos.push_back(inputList.back().getInside());
        inputList.back().setTitleBoxWidth(21).setContentBoxWidth(30);
        inputList.back().setDefaultType3();
    }

    inputList[0].setTitle("Current Password: ").setContent("");
    inputList[0].getContentBox().setTxtEncoded(true);

    inputList[0].setCursorInside();
    buttonList.push_back(Button(6, 8, 10, 3));
    pos.push_back(buttonList.back().getInside());
    buttonList.back().setText("   OK");
    buttonList.back().setDefaultType2();

    for (auto& elem : buttonList) elem.render();
    for (auto& elem : inputList) elem.update();
    for (auto& elem : inputList) elem.render();
}

void StudentController::setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, string& res, bool& isOver) {
    target.setOnClick([&](Button& button) {
        res = inputList[0].getContentBox().getText();
        isOver = true;
        });
}

void StudentController::setValidPosition(COORD c, int x, int y, int& cur, bool inTxt, bool inBtn, sll<pair<int, int>>& pos, ConsoleGraphics& graphics) {
    if (!inTxt && !inBtn) {
        if (x > 0 || y > 0) cur = (cur + 1) % pos.size();
        else if (x < 0 || y < 0) cur = (cur + pos.size() - 1) % pos.size();
        graphics.gotoXY(pos[cur].first, pos[cur].second, true);
    }
    else if (inTxt) graphics.gotoXY(c.X, c.Y);
}

void StudentController::renderInputProc(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos, bool& isOver) {
    int cur = 0;
    ConsoleGraphics& graphics = ConsoleGraphics::getInstance();

    TextBox notice = TextBox(17, 8, 40, 3, false).setText("Press ESC for cancel");
    notice.render();

    graphics.loopBoolean([&](pair<int, int> input) {
        COORD c = graphics.GetConsoleCursorPosition();
        int x = 0, y = 0;
        bool inBtn = false, inTxt = false;
        if (input.first == INPUT_CODE::ESC) return false;
        graphics.getNextDirection(input, x, y);
        c.X += x; c.Y += y;

        for (auto& elem : inputList) if (elem.checkPosInsideContentBox(c)) inTxt = true;
        for (auto& elem : buttonList) if (elem.isPosInContainer(c)) inBtn = true;

        setValidPosition(c, x, y, cur, inTxt, inBtn, pos, graphics);

        for (auto& elem : inputList) elem.update(input);
        for (auto& elem : buttonList) elem.update(input);

        Sleep(60);

        for (auto& elem : inputList) elem.render();
        for (auto& elem : buttonList) elem.render();
        if (inBtn) graphics.hideCursor();
        else graphics.showCursor();
        graphics.color(0);
        return !isOver;
        });
}

void StudentController::renderCaution() {
    TextBox notice = TextBox(5, 10, 40, 3, false, 0, 12).setText("Wrong password");
    notice.render();
}

void StudentController::renderAccept() {
    TextBox notice = TextBox(5, 10, 40, 3, false, 0, 10).setText("input successfully, loading ...");
    notice.render();
}

string StudentController::inputVerifPassProc(bool& isCancel) {
    sll<InputRow> inputList;
    sll<Button> buttonList;
    sll<pair<int, int> > pos;
    string res;
    bool isOver = false;

    setupVerifPassInputList(inputList, buttonList, pos);
    setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

    renderInputProc(inputList, buttonList, pos, isOver);
    isCancel = !isOver;
    return res;
}

bool StudentController::verifPassProc() {
    assert(curId >= 0);
    bool isCancel = false;
    system("cls");
    string input = inputVerifPassProc(isCancel);
    while (input != list[curId].pass && !isCancel) {
        renderCaution();
        input = inputVerifPassProc(isCancel);
    };
    if (isCancel) return false;
    renderAccept();
    Sleep(1500);
    return true;
}

//-----

void StudentController::setupChangePassInputList(sll<InputRow>& inputList, sll<Button>& buttonList, sll<pair<int, int>>& pos) {
    for (int i = 0; i < 2; ++i) {
        inputList.push_back(InputRow(1, 4 * i + 1, 50, 3, 0, 15));
        pos.push_back(inputList.back().getInside());
        inputList.back().setTitleBoxWidth(25).setContentBoxWidth(30);
        inputList.back().setDefaultType3();
    }

    inputList[0].setTitle("Enter Password: ").setContent("");
    inputList[0].getContentBox().setTxtEncoded(true);
    inputList[1].setTitle("Enter Password again: ").setContent("");
    inputList[1].getContentBox().setTxtEncoded(true);

    inputList[0].setCursorInside();
    buttonList.push_back(Button(2, 8, 10, 3));
    pos.push_back(buttonList.back().getInside());
    buttonList.back().setText("   OK");
    buttonList.back().setDefaultType2();

    for (auto& elem : buttonList) elem.render();
    for (auto& elem : inputList) elem.update();
    for (auto& elem : inputList) elem.render();
}

void StudentController::setOnClickSubmitButton(Button& target, sll<InputRow>& inputList, pair<string, string>& res, bool& isOver) {
    target.setOnClick([&](Button& button) {
        res.first = inputList[0].getContentBox().getText();
        res.second = inputList[1].getContentBox().getText();
        isOver = true;
        });
}

pair<string, string> StudentController::inputChangePassProc(bool& isCancel) {
    sll<InputRow> inputList;
    sll<Button> buttonList;
    sll<pair<int, int> > pos;
    pair<string, string> res;
    bool isOver = false;

    setupChangePassInputList(inputList, buttonList, pos);
    setOnClickSubmitButton(buttonList[0], inputList, res, isOver);

    renderInputProc(inputList, buttonList, pos, isOver);
    isCancel = !isOver;
    return res;
}

void StudentController::renderMismatchCaution() {
    TextBox notice = TextBox(5, 10, 40, 3, false, 0, 12).setText("Different!");
    notice.render();
}

void StudentController::changePassProc() {
    if (!verifPassProc()) return;
    bool isCancel = false;
    system("cls");
    pair<string, string> ans = inputChangePassProc(isCancel);

    while (ans.first != ans.second && !isCancel) {
        renderMismatchCaution();
        ans = inputChangePassProc(isCancel);
    }
    if (isCancel) return;
    renderAccept();
    Sleep(1000);
    list[curId].pass = ans.first;
    exportData();
}

void StudentController::viewScores(string stuID) {
    string yearname, semester;
    getCur(yearname, semester);
    Course_controller courseController(yearname, semester);
    courseController.viewScoresOfAStudent(stuID);

}

void StudentController::enrollCourseProc() {
    int stuId = stoi(this->list[curId].stuId);
    string yearname, semester;
    getCur(yearname, semester);
    Course_controller courseController(yearname, semester);
    courseController.enrollCourseProc(stuId, this->list[curId].firstname, this->list[curId].lastname);

}

void StudentController::proc() {
    int option;
    while (true) {
        option = inputTypeProc();
        switch (option) {
        case 1:
            enrollCourseProc();
            break;
        case 2:
            viewScores(this->list[curId].stuId); break;
        case 3:
            viewProfileProc();
            break;
        case 4:
            changePassProc();
            break;
        default:
            return;
        }
    }

}
