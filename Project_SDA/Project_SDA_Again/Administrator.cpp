#include "Administrator.h"

// Default constructor for Administrator
Administrator::Administrator() {

}

// Parameterized constructor for Administrator
Administrator::Administrator(Interface1* inter1) {
    // Initialize the Interface1 pointer with the provided object
    this->inter1 = inter1;
}

// Function to add an Employee to a department
void Administrator::AddEmp(Employee* emp, int dept_ID) {
    // Delegate the task to the Interface1 object
    inter1->AddEmployee(emp, dept_ID);
}

// Function to add a Manager to a department
void Administrator::AddMgr(Manager* mgr, int dept_ID) {
    // Delegate the task to the Interface1 object
    inter1->AddManager(mgr, dept_ID);
}

// Function to add a Teacher
void Administrator::AddTech(Teacher* _teach) {
    // Delegate the task to the Interface1 object
    inter1->AddTeacher(_teach);
}

// Function to remove an Employee from a department
void Administrator::removeEmp(int Dept_ID, Employee* emp) {
    // Delegate the task to the Interface1 object
    inter1->removeEmployee(Dept_ID, emp);
}

// Function to remove a Manager from a department
void Administrator::removeMgr(int Dept_ID, Manager* mgr) {
    // Delegate the task to the Interface1 object
    inter1->removeManager(Dept_ID, mgr);
}

// Function to remove a Teacher
void Administrator::removeTech(Teacher* t) {
    // Delegate the task to the Interface1 object
    inter1->removeTeacher(t);
}

// Function to get the vector of Teachers
vector<Teacher*> Administrator::Get_tech() {
    // Delegate the task to the Interface1 object
    return inter1->GetTeachers();
}

// Function to get the vector of Departments
vector<Department*> Administrator::Get_Dept() {
    // Delegate the task to the Interface1 object
    return inter1->Get_Depts();
}
