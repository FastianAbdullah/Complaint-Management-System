// Manager.cpp

#include "Manager.h"
#include "Department.h"
#include "Complaint.h"
//#include "Task.h"
#include<iostream>
using namespace std;

Manager::Manager(int id, string name, Department* dept)
{
    this->id = id;
    this ->name = name;
    this->dept = dept;
}
void Manager::reviewComplaints()
{
    const vector<Complaint*>& complaints = dept->getComplaints();
    if (complaints.size() > 0)
    {
        cout << "--------------------------------\n";
        cout << "Manager Reviewing Complaints of dept " << dept->getName() << "\n";
        for (int i = 0; i < complaints.size(); ++i)
        {
            const Complaint* comp = complaints[i];
            cout << "\nComplaint ID: " << comp->id << "\nComplaint Description : " << comp->description << "\n";
            cout << "--------------------------------\n";
        }
    }
    else cout << "\nNo Complaints Yet in This Department\n";

}
bool Manager::checkComplaint(Complaint* comp, vector<Complaint*> complaints)
{
    auto it = find(complaints.begin(), complaints.end(), comp);
    return it != complaints.end();
}
string Manager::GetName()
{
    return this->name;
}
vector<Employee*> Manager::assignComplaintsAsTasks(Complaint* comp, vector<int>& emp_ids, string description)
{
    vector<Complaint*> complaints = dept->getComplaints();  //if that Complaint Exist in the Department.
    vector<Employee*> emp_of_ids;
    bool isFound = checkComplaint(comp, complaints);
    if (complaints.size() > 0)
    {
         emp_of_ids = Get_Emps_of_IDs(emp_ids);

        if (isFound)
        {
            Task* task = new Task(this, emp_of_ids, comp, description);
            for (int i = 0; i < emp_of_ids.size(); i++)
            {
                emp_of_ids[i]->addTask(task);
                // Update Manager's tracking
                assignedTasks[emp_of_ids[i]].push_back(task);
                assignedComplaints[emp_of_ids[i]].push_back(comp);
            }
            tasks.push_back(task);
            return emp_of_ids;
        }
        else
            cout << "There's no such complaint that you're referring to.\n";
    }
    else
        cout << "Your Can't Assign... You've no Complaints\n";
    return emp_of_ids;
}
void Manager::displayRelevantEmployees()
{
    if (assignedTasks.size() != 0)
    {
        for (const auto& entry : assignedTasks)
        {
            Employee* employee = entry.first;
            if (employee != NULL)
                cout << "Employee: " << employee->getName() << "\n";

        }
    }
}
void Manager::changeState_to_Completed(int id)
{
    vector<Complaint*> complaints = dept->getComplaints();
    bool flag = false;
    int i;
    for (i = 0; i < complaints.size(); i++)
    {
        if (id == complaints[i]->getID() && complaints[i]->currState() == Resolved)
        {
           complaints[i]->changeState(Completed);                    //id must exsists 
           break;
        }
    }

}
void Manager::changeState_to_Assigned(int id)
{
    vector<Complaint*> complaints = dept->getComplaints();
    bool flag = false;
    int i;
    for (i = 0; i < complaints.size(); i++)
    {
        if (id == complaints[i]->getID() && complaints[i]->currState() != Completed)
        {
            if (id == complaints[i]->getID() && complaints[i]->currState() == Resolved)
            {
                complaints[i]->changeState(Assigned);                    //id must exsists 
                break;
            }
        }
        else
            cout << "Can't Assign ...Complaint already Completed\n";
    }

}
void Manager::printResolvedComplaints()
{
    vector<Complaint*> complaints = dept->getComplaints();
    if (complaints.size() > 0)
    {
        cout << "Resolved Complaints are enlisted below\n";
        for (int i = 0; i < complaints.size(); i++)
        {
            if (complaints[i]->currState() == Resolved)
            {
                cout << "Complaint id: " << complaints[i]->getID() << " Complaint Description " << complaints[i]->getDescription();
            }
        }
    }
    else
        cout << "\nNo Complaints yet in this Department\n";
}
void Manager::checkFeedback(int id)
{
    
    vector<Complaint*> complaints = dept->getComplaints();
    for (int i = 0; i < complaints.size(); i++)
    {
        if (complaints[i]->getID() == id)
        {
           
            if(complaints[i]->getFlag()== 1)
            {
                complaints[i]->changeState(Closed);
            }
            else {
                complaints[i]->changeState(Assigned);
            }
        }
    }
  
}
vector<Employee*> Manager::Get_Emps_of_IDs(vector<int> emps_ids)
{
    vector<Employee*> cmp_specified_emps;
    vector<Employee*> emps_of_dept = dept->Get_Dept_Emps();

    for (int i = 0; i < emps_ids.size(); i++) {
        for (Employee* E : emps_of_dept) {
            if (emps_ids[i] == E->GetID())
                cmp_specified_emps.push_back(E);
        }
    }
    return cmp_specified_emps;
}
vector<Task*> Manager::GetTasks()
{
    if (tasks.size() != 0)
        return tasks;
    return vector<Task*>();
}
int Manager::GetID()
{
    return this->id;
}