// Employee.cpp
#include<iostream>
using namespace std;
#include "Employee.h"
#include "Department.h"
#include "Task.h"

// Constructor for Employee
Employee::Employee(int id, string name, Department* dept)
{
    this->id = id;
    this->name = name;
    this->dept = dept;
    this->task = nullptr;
}

// View the details of the assigned task
void Employee::viewTask() {
    if (task != nullptr) {
        cout << "Task Description: " << task->getDescription() << "\n";
    }
    else {
        cout << "No task assigned.\n";
    }
}

// Add a new task to the employee
void Employee::addTask(Task* tk) {
    task = tk;
}

// Complete the assigned task
void Employee::CompleteTask()
{
    task->doTask();
}

// Getter for employee name
string Employee::getName()
{
    return this->name;
}

// Print the status of a specific complaint assigned to the employee
void Employee::printComplainStatus(Complaint* comp)
{
    switch (comp->currState())
    {
    case 0:
        cout << "Status of that complaint ID " << comp->getID() << " is New\n";
        break;
    case 1:
        cout << "Status of that complaint ID " << comp->getID() << " is Assigned\n";
        break;
    case 2:
        cout << "Status of that complaint ID " << comp->getID() << " is Resolved\n";
        break;
    case 3:
        cout << "Status of that complaint ID " << comp->getID() << " is Completed\n";
        break;
    case 4:
        cout << "Status of that complaint ID " << comp->getID() << " is Closed\n";
        break;
    }
}

// Getter for employee ID
int Employee::GetID()
{
    return this->id;
}
