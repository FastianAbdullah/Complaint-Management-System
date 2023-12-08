#pragma once
#include "Complaint.h"
#include "Employee.h"
#include "Manager.h"
#include<vector>
#include<string>
#include <ctime>
using namespace std;

class Employee;
class Manager;
class Department {
public:
    Department(int id, string name);

    void addComplaint(Complaint* comp);
    const vector<Complaint*>& getComplaints() const;
    void addEmployees(Employee* emp);
    void setManager(Manager* mgr);
    string getName();
    void ABD_cmp_Employees();
    void printEmployees();
    Manager* getManager();
    //WRAPPER
    int GetID();
    string GetMgrName();
    vector<tm> GetAllCmpTime();
    void changeState(Complaint* comp);
    void rmEmployee(Employee* emp);
    Complaint* GetCmp(int ind);
    Complaint* Get_Cmp_of_id(int id);
    void PrintCmpDetails(int ind);
    void rmManager(Manager* mgr);
    int Print_Cmps();
    vector<Employee*> Get_Dept_Emps();
    Manager* GetMgr();
    Employee* Get_Emp_of_id(int id);
private:
    int id;
    string name;
    vector<Employee*> employees;
    vector<Complaint*> complaints;
    Manager* mgr;
    int totalComplaints;
    vector<tm> AllCmptimes;


};

