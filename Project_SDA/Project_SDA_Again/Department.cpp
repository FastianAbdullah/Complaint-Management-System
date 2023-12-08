#pragma once
// Department.cpp

#include "Department.h"
#include<iostream>

// Constructor for Department
Department::Department(int id, string name) {
    this->id = id;
    this->name = name;
    this->totalComplaints = 0;
    this->mgr = nullptr;
}

// Getter for department name
string Department::getName()
{
    return this->name;
}

// Display all assigned employees for the complaint
void Department::ABD_cmp_Employees()
{
    if (mgr != NULL)
    {
        mgr->displayRelevantEmployees();
    }
    else
        cout << "No Employees\n";
}

// Print the details of employees in the department
void Department::printEmployees()
{
    cout << "\nEmployees in " << this->name << " Department \n";
    for (int i = 0; i < employees.size(); i++)
    {
        cout << "\n" << "Employees ID " << employees[i]->GetID() << "Employees Name: " << employees[i]->getName() << "\n";
    }
}

// Getter for the department manager
Manager* Department::getManager()
{
    return this->mgr;
}

// Add a new complaint to the department
void Department::addComplaint(Complaint* comp)
{
    for (int i = 0; i < complaints.size(); i++)
    {
        if (comp->getID() == complaints[i]->getID())
        {
            cout << "Can't add Complaint with the same ID.\n";
            return;
        }
    }
    complaints.push_back(comp);
    AllCmptimes.push_back(comp->GetTime());
    this->totalComplaints++;
}

// Getter for the vector of complaints in the department
const vector<Complaint*>& Department::getComplaints() const {
    return complaints;
}

// Add a new employee to the department
void Department::addEmployees(Employee* emp) {
    employees.push_back(emp);
}

// Set the manager for the department
void Department::setManager(Manager* manager) {
    mgr = manager;
}

// Getter for the department ID
int Department::GetID()
{
    return this->id;
}

// Getter for the manager's name
string Department::GetMgrName()
{
    if (mgr)
        return mgr->GetName();
    else
        return "No Assigned Manager.";
}

// Getter for the vector of complaint times
vector<tm> Department::GetAllCmpTime()
{
    return AllCmptimes;
}

// Unused function, could be implemented to change state for a specific complaint
void Department::changeState(Complaint* comp)
{
    // Implementation could be added here if needed
}

// Remove an employee from the department
void Department::rmEmployee(Employee* emp)
{
    auto emp_itr = std::find(employees.begin(), employees.end(), emp);
    if (emp_itr != employees.end())
        employees.erase(emp_itr);
    else cout << "Employee Does Not Exist!\n";
}

// Display details of a specific complaint
void Department::PrintCmpDetails(int ind)
{
    if (ind >= 0 && ind < complaints.size()) {
        cout << "\n----------------------------------\n";
        cout << "Complaint ID: " << complaints[ind]->getID()
            << "\nComplaint Details for :" << name << " Department\n";
        cout << "\nDescription : " << complaints[ind]->getDescription() << "\nStatus :" << complaints[ind]->currState() << "\nTime :" << complaints[ind]->GetTime().tm_year << "-" << complaints[ind]->GetTime().tm_mon << "-" << complaints[ind]->GetTime().tm_mday << endl;
        cout << "\n----------------------------------\n";
    }
}

// Getter for a specific complaint using its index
Complaint* Department::GetCmp(int ind)
{
    if (ind >= 0 && ind < complaints.size())
        return complaints[ind];
    return nullptr;
}

// Getter for a specific complaint using its ID
Complaint* Department::Get_Cmp_of_id(int id)
{
    for (Complaint* c : complaints) {
        if (c->getID() == id)
            return c;
    }
    return nullptr;
}

// Remove the manager from the department
void Department::rmManager(Manager* mgr)
{
    if (this->mgr != NULL) {
        delete mgr;
        mgr = NULL;
        cout << "Manager Removed Successfully!\n";
    }
}

// Print details of all complaints in the department
int Department::Print_Cmps()
{
    int i = 0;
    cout << "\n\t\t\t" << name << "\n";
    if (complaints.size() > 0) {
        for (Complaint* C : complaints) {
            i++;
            cout << "\nComplaint ID :" << C->getID()
                << "\nDescription :" << C->getDescription()
                << "\nStatus :" << C->currState()
                << "\nTime :" << C->GetTime().tm_year << "-" << C->GetTime().tm_mon << "-" << C->GetTime().tm_mday << endl;
        }
    }
    else cout << "\nNo Complaints yet in this Department\n";
    return i;
}

// Getter for the vector of employees in the department
vector<Employee*> Department::Get_Dept_Emps()
{
    return this->employees;
}

// Getter for the manager of the department
Manager* Department::GetMgr()
{
    if (mgr != NULL)
        return mgr;
    else
        return nullptr;
}

// Getter for an employee using their ID
Employee* Department::Get_Emp_of_id(int id)
{
    for (Employee* e : employees)
    {
        if (e->GetID() == id)
            return e;
    }
    return nullptr;
}
