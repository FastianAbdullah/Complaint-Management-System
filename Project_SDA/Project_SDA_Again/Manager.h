#pragma once
// Manager.h

#pragma once
#include "Department.h"
#include "Employee.h"
#include <vector>
#include <map>
using namespace std;
class Task;
class Complaint;
class Department;
class Employee;


class Manager{
public:
    Manager(int id,string name, Department* dept);
    void reviewComplaints();
    vector<Employee*> assignComplaintsAsTasks(Complaint* comp, vector<int>& emp_ids, string description);
    bool checkComplaint(Complaint* comp,vector<Complaint*> complaints);
    void displayRelevantEmployees();
    void changeState_to_Completed(int id);
    void changeState_to_Assigned(int id);
    void printResolvedComplaints();
    void checkFeedback(int id);
    vector<Employee*> Get_Emps_of_IDs(vector<int> emps_ids);
    vector<Task*> GetTasks();
    int GetID();
    string GetName();
private:
    int id;
    string name;
    Department* dept;
   vector<Task*> tasks;
   map<Employee*, vector<Task*>> assignedTasks;
   map<Employee*, vector<Complaint*>> assignedComplaints;
  
};
