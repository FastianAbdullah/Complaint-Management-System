#pragma once
#pragma once
#include "Interface1.h"
#include "Main.h"



class Administrator {
public:
    Administrator();
    Administrator(Interface1* inter1);
    //Wrappers
    void AddEmp(Employee* emp, int dept_ID);
    void AddMgr(Manager* mgr, int dept_ID);
    void AddTech(Teacher* _teach);
    void removeEmp(int Dept_ID, Employee* emp);
    void removeMgr(int Dept_ID, Manager* mgr);
    void removeTech(Teacher* t);
    vector<Teacher*> Get_tech();
    vector<Department*> Get_Dept();
private:
    Interface1* inter1;

};