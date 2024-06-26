#pragma once

#include <string>
#include <vector>
#include "Complaint.h"

using namespace std;
class Complaint;
class Teacher {
public:
	Teacher(int id, string name);
	void addComplaint(Complaint* comp);
	void printComplaints();
	int getID();
	string getName();
	const vector<Complaint*>& getComplaints();
	void reportFeedback(int id);
	void saveToFile(Teacher* teacher, Complaint* complaint);



private:
	int id;
	string name;
	vector<Complaint*> complaints;

};