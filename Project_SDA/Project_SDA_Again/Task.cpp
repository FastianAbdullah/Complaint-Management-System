// Task.cpp
#include "Task.h"
#include<iostream>
using namespace std;

Task::Task(Manager* mgr, const vector<Employee*>& emp,Complaint* comp, const string& description)
{
    this ->description = description;
    this->assignedEmployees = emp;
    this->assignedManager = mgr;
    this->assignedComplaint = comp;
    assignedComplaint->changeState(State::Assigned);;

}
Manager* Task::getAssignedManager() const {
    return assignedManager;
}
vector<Employee*>& Task:: getAssignedEmployees()
{
    return assignedEmployees;
}
string Task::getDescription()
{
    return this->description;
}
Complaint* Task::getAssignedComplaint()
{
    return this->assignedComplaint;
}
void Task::doTask()
{
    if (this != NULL) {
        if (this->assignedComplaint->currState() != State::Completed)
        {
            if (this->assignedComplaint->currState() != State::Resolved)
            {
                this->assignedComplaint->changeState(State::Resolved);
                cout << this->assignedComplaint->getDescription() << " is Completed\n " << endl;
            }
            else
                cout << "Complaint Already resolved by and Employee.\n";
        }
        else
            cout << "Complaint Already Completed" << endl;
    }
    else
        cout << "There's No Task to complete\n";
}
