#include <ctime>
#include <iostream>
#include "Complaint.h"
#include "Teacher.h"
#include <fstream>

// Constructor for Complaint
Complaint::Complaint(int id, Teacher* t, Department* dep, string description, State st)
{
    this->id = id;
    this->t = t;
    this->dep = dep;
    this->description = description;
    this->state = st;

    // Getting current YYYY-MM-DD.
    if (state == New) {
        std::time_t cur_time = std::time(nullptr);
        localtime_s(&Local_Time, &cur_time);
        Local_Time.tm_year = Local_Time.tm_year + 1900;
        Local_Time.tm_mon = Local_Time.tm_mon + 1;
    }
}

// Getter for complaint description
string Complaint::getDescription()
{
    return this->description;
}

// Getter for complaint ID
int Complaint::getID()
{
    return this->id;
}

// Getter for complaints associated with a teacher
const vector<Complaint*>& Complaint::getComplaints(Teacher* t)
{
    return t->getComplaints();
}

// Getter for the department manager's name
string Complaint::Dept_mgr_name()
{
    return dep->GetMgrName();
}

// Display assigned employees for the complaint
void Complaint::Complaint_Assigned_Emps()
{
    dep->ABD_cmp_Employees();
}

// Getter for the current state of the complaint
State Complaint::currState() {
    return state;
}

// Setter to change the state of the complaint
void Complaint::changeState(State st) {
    state = st;
}

// Getter for teacher's name associated with the complaint
string Complaint::GetteacherName()
{
    return t->getName();
}

// Generate a report for the complaint
void Complaint::generateReport() {
    std::cout << "Complaint ID: " << id << endl;
    std::cout << "Description: " << description << endl;
    std::cout << "Assigned to Teacher: " << t->getName() << " (ID: " << t->getID() << ")" << endl;
    std::cout << "Assigned to Department: " << dep->getName() << endl;
    std::cout << "\nCurrent State: " << state << endl;
}

// Getter for the time of the complaint
tm Complaint::GetTime()
{
    return Local_Time;
}

// Getter for the associated department of the complaint
Department* Complaint::getAssociatedDepartment()
{
    return dep;
}

// Getter for the department name associated with the complaint
string Complaint::depName()
{
    return dep->getName();
}

// Getter for the satisfaction status of the complaint
const string& Complaint::getSatisfactionStatus() const {
    return satisfactionStatus;
}

// Setter to update the satisfaction status of the complaint
void Complaint::setSatisfactionStatus(const string& status) {
    satisfactionStatus = status;
}

// Setter to update the time of the complaint
void Complaint::setTime(tm Time) {
    Local_Time = Time;
}

// Getter for the teacher ID associated with the complaint
int Complaint::Get_teach_id()
{
    return t->getID();
}

// Getter for the department ID associated with the complaint
int Complaint::Get_dept_id()
{
    return dep->GetID();
}
