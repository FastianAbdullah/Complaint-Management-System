#pragma once

#include<ctime>
#include<string>
#include "Department.h"
#include "Teacher.h"
#include<vector>
using namespace std;

enum State
{
	New,
	Assigned,
	Resolved,
	Completed,
	Closed
};

class Department;
class Teacher;
class Complaint {
	tm date;
	State state;
	Teacher* t;
	Department* dep;
	string satisfactionStatus;
	bool flag;
public:
	
	tm Local_Time;
	int id;
	string description;
	Complaint(int id, Teacher* t, Department* dep, string description, State st = New);
	const vector<Complaint*>& getComplaints(Teacher* t);
	string Dept_mgr_name();
	void Complaint_Assigned_Emps();
	State currState();
	void changeState(State st);
	string GetteacherName();
	void generateReport();
	string getDescription();
	int getID();
	tm GetTime();
	Department* getAssociatedDepartment();
	const string& getSatisfactionStatus() const;
	void setSatisfactionStatus(const string& status);
	void setFlag(bool f)
	{
		this->flag = f;
	}
	bool getFlag()
	{
		return this->flag;
	}
	void setTime(tm Time);
	string depName();
	int Get_teach_id();
	int Get_dept_id();

	
};
