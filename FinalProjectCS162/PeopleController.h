#pragma once
#include "GeneralPersonalInfo.h"
#include "SinglyLinkedList.h"
#include "SinglyLinkedList.h"
#include "InputRow.h"
#include "Button.h"
class PeopleController
{
protected:
    int curId;

public:


    virtual bool loginProc(string username, string password) = 0;

    virtual void regProc() = 0;

};
