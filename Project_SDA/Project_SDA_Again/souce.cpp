#include <iostream>
#include<string>
#include "FileHandler.cpp"
#include "Department.h"
#include "Teacher.h"
#include "Administrator.h"
#include "Director.h"
#include <conio.h>   // Consider using alternative methods for platform-independent code
using namespace std;

//Task Append Issue
// Function to check if a given date is valid
bool isValid(int year, int month, int day) {
    // Check if the date is valid
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Check for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    return true;

}
// Function to verify login for a Teacher
bool LoginVerification(string name, vector<Teacher*> vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        if (name == vector[i]->getName())
        {

            cout << "\t\t\t\t< Welcome " << name << " >\n";
            return true;
        }
    }
    return false;
}
// Function to verify Manager login
bool VerifyManager(vector<Department*> dept_vec, string mgr_name, int user_dept)
{
    for (int i = 0; i < dept_vec.size(); i++)
    {
        if (dept_vec[user_dept]->getManager()->GetName() == mgr_name)
        {
            cout << "\n\t\t\t< Welcome " << mgr_name << " >\n";

            return true;
        }
    }

    return false;
}
// Function to verify Employee login
bool VerifyEmployee(vector<Department*> dept_vec, string emp_name, int user_dept)
{
    vector<Employee*> this_dep_emps = dept_vec[user_dept]->Get_Dept_Emps();

    for (int i = 0; i < this_dep_emps.size(); i++)
    {
        if (this_dep_emps[i]->getName() == emp_name)
        {
            cout << "\n\t\t\t< Welcome " << emp_name << " >\n";
            return true;
        }
    }
    return false;
}
// Function to get Teacher ID based on the name
int getTeacherID(string tech_name, vector<Teacher*> vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        if (tech_name == vector[i]->getName())
        {
            return vector[i]->getID();
        }
    }
    cout << "not exsists";

}
// Function to get Employee index based on the name
int getEmployeeIndex(string emp_name, vector<Employee*> employees)
{
    for (int i = 0; i < employees.size(); i++)
    {
        if (emp_name == employees[i]->getName())
        {
            return i;
        }
    }
    cout << "not exsists";

}
// Function to get Department ID based on the Complaint ID
int getDepartmentID(int complaint_ID, vector<Department*> dept_vec)
{
    
    for (int i = 0; i < dept_vec.size(); i++)
    {
        vector<Complaint*> complaints = dept_vec[i]->getComplaints();
        for (int j = 0; j < complaints.size(); j++)
        {
            if (complaint_ID == complaints[i]->getID())
                return complaints[i]->Get_dept_id();
       }
    }
}
// Function to exit the program when the user presses the Escape key
void Exit()
{
    char key;
    while (true)
    {
        if (_kbhit())
        {
            key = _getch();
            if (key == 27)
            {
                cout << "Closing Panel\n";
                break;
            }
        }
    }
}
// Administrator Panel function
void Administrator_Panel(vector<Teacher*> &tech_vec,vector<Department*> &dept_vec)
{
    int user_id = 0;
    Interface1* inter1 = new Main(tech_vec, dept_vec);
    Administrator* admin = new Administrator(inter1);
    int tech_id = 0;
    string tech_name = {};
    int mgr_id = 0;
    string mgr_name = {};
    int dept_id_mgr = 0;
    int emp_id = 0;
    int dept_id_emp = 0;
    string emp_name = {};
    int emp_id_remove = 0;
    int dept_id_remove_emp = 0;
    int manager_dept_id_remove = 0;
    int emp_dept_id_remove = 0;
    while (user_id != -1)
    {
        cout << "\n1. Add Teacher\n"
            << "2. Add Manager\n"
            << "3. Add Employee\n"
            << "4. Remove Employee\n"
            << "5. Remove Manager\n"
            << "6. Remove Teacher\n";
        cout << "\nEnter choice : ";
        cin >> user_id;

        if (user_id == 1)
        {
            cout << "Enter Teacher ID: ";
            cin >> tech_id;
            cout << "Enter Teacher Name: ";
            cin >> tech_name;
            Teacher* tech = new Teacher(tech_id, tech_name);
            admin->AddTech(tech);
            tech_vec = admin->Get_tech();
            Populate_to_file("Teacher.txt", tech_vec);
        }
        else if (user_id == 2)
        {
            cout << "Enter Manager ID: ";
            cin >> mgr_id;
            cout << "Enter Manager Name: ";
            cin >> mgr_name;
            cout << "Enter Manager Department";
            cin >> dept_id_mgr;
            Manager* mgr = new Manager(mgr_id,mgr_name,dept_vec[dept_id_mgr]);
            Manager* mgr2 = nullptr;
            Populate_from_file_2("Manager.txt", dept_vec,mgr2);
            admin->AddMgr(mgr, dept_id_mgr);
            Populate_mgrs_to_file("Manager.txt", dept_vec);
        }
        else if (user_id == 3)
        {
            cout << "Enter Employee ID : ";
            cin >> emp_id;
            cout << "Enter Employee Name : ";
            cin >> emp_name;
            cout << "Enter the Department in which you want to Add this Employee : ";
            cin >> dept_id_emp;
            Employee* emp = new Employee(emp_id, emp_name, dept_vec[dept_id_emp]);
            admin->AddEmp(emp,dept_id_emp);
            Populate_emps_to_file("employee.txt", dept_vec);
        }
        else if (user_id == 4)
        {          
            cout << "Enter Dept_id in which you want to Remove Employee : ";
            cin >> dept_id_remove_emp;
            cout << "Enter Employee ID : ";
            cin >> emp_id_remove;
            vector<Employee*> all_emps_of_dept = dept_vec[dept_id_remove_emp]->Get_Dept_Emps();
            for (int i = 0; i < all_emps_of_dept.size(); i++)
            {
                if (all_emps_of_dept[i]->GetID() == emp_id_remove)
                {
                    admin->removeEmp(dept_id_remove_emp, all_emps_of_dept[i]);
                    dept_vec = admin->Get_Dept();
                    Populate_emps_to_file("employee.txt", dept_vec);
                    Populate_Tasks_to_file("Tasks.txt", dept_vec);

                    break;
                }
            }
            
        }
        else if (user_id == 5)
        {
            cout << "Enter Department ID in which you Manager Exsists : ";
            cin >> manager_dept_id_remove;
            
            admin->removeMgr(manager_dept_id_remove, dept_vec[manager_dept_id_remove]->GetMgr());
            Populate_mgrs_to_file("Manager.txt", dept_vec);
        }
        else if (user_id == 6)
        {
            cout << "Enter Teacher ID : ";
            cin >> tech_id;
            bool flag = true;
            for (Teacher* t : tech_vec)
            {
                if (t->getID() == tech_id)
                {
                    admin->removeTech(t);
                    tech_vec = admin->Get_tech();
                    Populate_to_file("Teacher.txt", tech_vec);
                    cout << "Removal Successfull\n";
                    flag = false;
                }
            }
            if (flag)
                cout << "No Teacher with this ID Exsits\n";

           

        }
        else if (user_id == -1)
        {
            cout << "Exiting...";
        }
    }
    cout << "Press esc to Log Out\n";
    Exit();

}
// Director Panel function
void Director_Panel(vector<Teacher*> tech_vec, vector<Department*> dept_vec,vector<Employee*> emp)
{

    cout << "\t\t\t\t< Welcome Director >\n\n";
    Interface2* inter2 = new Main(tech_vec, dept_vec);
    Director* dir = new Director(inter2);
    int complaint_id;
    int user_id = 0;
    Manager* mgr;
   
  
    while (user_id != -1)
    {
        cout << "\n1. To See Detail of a Specific Complaint\n";
        cout << "-1 to Exit";
        cout << "\n\nEnter Choice : ";
        cin >> user_id;
        if (user_id == 1)
        {
            int startYear, startMonth, startDay;
            //Ask Start Time And End Time For Summary.
            cout << "Enter start date (YYYY MM DD): ";
            cin >> startYear >> startMonth >> startDay;

            int endYear, endMonth, endDay;
            cout << "Enter end date (YYYY MM DD): ";
            cin >> endYear >> endMonth >> endDay;

            if (isValid(startYear, startMonth, startDay) && isValid(endYear, endMonth, endDay)) {
                std::tm start_tm = {};
                start_tm.tm_year = startYear * 10000;
                start_tm.tm_mon = startMonth * 100;
                start_tm.tm_mday = startDay;

                std::tm end_tm = {};
                end_tm.tm_year = endYear * 10000;
                end_tm.tm_mon = endMonth * 100;
                end_tm.tm_mday = endDay;

                vector<Complaint*> cmps_in_rge = dir->cmps_in_range(start_tm, end_tm);
                cout << "\nEnter Complaint-ID to see Complete details : ";
                cin >> complaint_id;

                int dep_id = getDepartmentID(complaint_id, dept_vec);

                Populate_from_file_2("Manager.txt", dept_vec, mgr, dep_id);
                Populate_Tasks("Tasks.txt", dept_vec, dep_id);

                dir->cmp_details(cmps_in_rge, complaint_id);
            }

            else if (user_id == -1) {
                cout << "Exiting... ";
                break;
            }
            else {
                cout << "Invalid Press ! Enter Again\n";

            }

        }
        cout << "Press Escape to Log Out\n";
        Exit();
    }
} //Issue in files
// Teacher Panel function
void Teacher_Panel(vector<Department*> dept_vec, vector<Complaint*> all_cmps, vector<Teacher*> tech_vec)
{
    int choice = 0;
    int feed_id = 0;
    int com_id = 0;
    int dep_id = 0;

    string comp_description;

    string teacher_name;
    cout << "Enter your name : ";
    cin >> teacher_name;


    if (LoginVerification(teacher_name, tech_vec))
    {

        int id = getTeacherID(teacher_name, tech_vec);

        while (choice != -1)
        {
            cout << "\n1. Add Complaints.\n";
            cout << "2. View Complaints.\n";
            cout << "3. Report Feedback.\n";
            cout << "-1. Exit.\n";

            cout << "\nEnter Choice : ";
            cin >> choice;
            if (choice == 1)
            {
                cout << "Enter Complaint id : ";
                cin >> com_id;
                cout << "Enter Department id : ";
                cin >> dep_id;
                cout << "Enter Complaint Description : ";
                cin >> comp_description;
                Complaint* comp = new Complaint(com_id, tech_vec[id], dept_vec[dep_id], comp_description);
                tech_vec[id]->addComplaint(comp);
                dept_vec[dep_id]->addComplaint(comp);

                // tech_vec[id]->saveToFile(tech_vec[id], comp);
            }
            else if (choice == 2)
            {
                tech_vec[id]->printComplaints();
            }
            else if (choice == 3)
            {
                cout << "Enter Complaint id on which you want to give Feedback : ";
                cin >> feed_id;

                tech_vec[id]->reportFeedback(feed_id);


            }
            else if (choice == -1)
            {
                cout << "Exiting...";
            }
            else
                cout << "Invalid ID\n";
        }
        Populate_cmps_to_file("Complaint.txt", dept_vec);
        cin.ignore();

    }
    else
        cout << "Login Failed\n";


    cout << "Press Escape to Log Out\n";
    Exit();
}
// Manager Panel function
void Manager_Panel(vector<Complaint*> all_cmps, vector<Department*>& dept_vec, vector<Employee*>& emps_of_dept)
{
    Manager* mgr = nullptr;
    int user_dept;
    string name;
    int choice = 0;
    cout << "Enter your name : ";
    cin >> name;
    cout << "Enter your Department : ";
    cin >> user_dept;

    Populate_from_file_2("Manager.txt", dept_vec, mgr, user_dept);
    //Populate_All_Emps("employee.txt", emps_of_dept, dept_vec);

    if (VerifyManager(dept_vec, name, user_dept))
    {
        while (choice != -1 && mgr != nullptr)
        {
            cout << "\n1. Review Tasks.\n"
                << "2. Check Resolved Complaints.\n"
                << "3. Assign Tasks.\n"
                << "4. Check Teacher Feedback Against a Complaint.\n"
                << "-1. Exit.\n";

            cout << "Enter Choice : ";
            cin >> choice;
            int count = 0;
            if (choice == 3)
            {
                int user_cmp = 0;
                string description = {};
                vector<Complaint*> dept_cmps = dept_vec[user_dept]->getComplaints();
                
                count = dept_vec[user_dept]->Print_Cmps();
                if (count > 0)
                {
                    cin.ignore();
                    cout << "Select Complaint ID To Assign: ";
                    cin >> user_cmp;
                    cout << "Enter Complaint-Task Description : ";
                    cin >> description;

                    vector<Employee*> dept_emps = dept_vec[user_dept]->Get_Dept_Emps();
                    cout << "Available Employees for Department " << dept_vec[user_dept]->getName();

                    dept_vec[user_dept]->printEmployees();

                    vector<int> emps_id;
                    int emp_id = 0;

                    while (emp_id != -1) {
                        cout << "\nPlease Enter Emp_ID for this Complaint(Press -1 to End) :";
                        cin >> emp_id;
                        cin.ignore();
                        if (emp_id != -1)
                            emps_id.push_back(emp_id);
                    }
                    Complaint* cmp_to_assign = dept_vec[user_dept]->Get_Cmp_of_id(user_cmp);

                    vector<Employee*> Assigned_emps = mgr->assignComplaintsAsTasks(cmp_to_assign, emps_id, description);

                    for (Employee* emp : Assigned_emps)
                    {
                        cout << emp->getName() << " ";

                    }
                    cout << "has been Assigned Tasks\n";
                    Populate_Tasks_to_file("Tasks.txt", dept_vec);
                }
                else cout << "You can't Assign as there's no Complaint\n";
            }
            else if (choice == 1)
                mgr->reviewComplaints();
            else if (choice == 2)
                mgr->printResolvedComplaints();
            else if (choice == 4)
            {
                int comp_id_for_feedback;
                cout << "Enter Resolved Complaint ID to Change Feedback\n";
                cin >> comp_id_for_feedback;
                mgr->checkFeedback(comp_id_for_feedback);
            }
            else if (choice == -1)
                cout << "Exiting...";
            else
                cout << "Invalid Choice ! Enter Again";
        }
    }
    else
        cout << "Not Verified";

    cout << "Press Escape to Log Out\n";
    Exit();
}
// Employee Panel function
void Employee_Panel(vector<Employee*> all_emps, vector<Department*> dept_vec)
{
    string emp_name;
    int dep_id = 0;
    int choice = 0;

    cout << "Enter your name : ";
    cin >> emp_name;
    cout << "Enter your department : ";
    cin >> dep_id;
    Manager* mgr = nullptr;

    if (VerifyEmployee(dept_vec, emp_name, dep_id))
    {
        Populate_from_file_2("Manager.txt", dept_vec, mgr, dep_id);
        Populate_Tasks("Tasks.txt", dept_vec, dep_id);
        int idx = getEmployeeIndex(emp_name, all_emps);

        while (choice != -1)
        {
            cout << "\n1. View Task.\n";
            cout << "2. Complete Task.\n";
            cout << "Press -1 to Exit.\n";

            cout << "\nEnter Choice : ";
            cin >> choice;
            cout << "\n";

            if (choice == 1)
            {
                all_emps[idx]->viewTask();
            }
            else if (choice == 2)
            {
                all_emps[idx]->CompleteTask();
            }


            else if (choice == -1)
            {
                cout << "Exiting...";
            }
            else
                cout << "Invalid ID\n";
        }
        cin.ignore();
    }
    else
        cout << "Login Failed\n";

    cout << "Press Escape to Log Out\n";
    Exit();

}
// Main Panel function
void Main_Panel()
{
    vector<Teacher*> tech_vec;
    vector<Department*> dept_vec;
    vector<Complaint*> all_cmps;
    vector<Employee*> all_emps;
    Populate_from_file("Teacher.txt", tech_vec);
    Populate_from_file("Department.txt", dept_vec);
    Populate_Complaints("Complaint.txt", all_cmps, tech_vec, dept_vec);
    Populate_All_Emps("employee.txt", all_emps, dept_vec);

    int user_id;
    user_id = 0;
    while (user_id != -1)
    {
        system("cls");
       cout << "\t\t\t\t-------------------------------\n";
        cout << "\t\t\t\t  Complaint Management System\n";
        cout << "\t\t\t\t-------------------------------\n\n";
        cout << "\n1. Administrator\n"
            << "2. Director\n"
            << "3. Teacher\n"
            << "4. Manager\n"
            << "5. Employee\n\n"
            << "Press -1 to Exit.\n\n";

        cin >> user_id;
        switch (user_id)
        {
        case 1:
            Administrator_Panel(tech_vec, dept_vec);
            break;
        case 2:
            Director_Panel(tech_vec, dept_vec,all_emps);
            break;
        case 3:
            Teacher_Panel(dept_vec, all_cmps, tech_vec);
            break;
        case 4:
            Manager_Panel(all_cmps, dept_vec, all_emps);
            break;
        case 5:
            Employee_Panel(all_emps, dept_vec);
            break;
        case -1:
            return;
        default:
            cout << "Invalid ID...Enter Again\n";

        }
    }
}

int main() 
{
    Main_Panel();

    return 0;
}


    




