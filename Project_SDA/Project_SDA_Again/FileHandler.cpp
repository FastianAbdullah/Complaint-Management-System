//#include "souce.cpp"
#include<iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include "Manager.h"

using namespace std;
// Function to populate data from a file into a vector of objects
template<class T>
void Populate_from_file(string filename, vector<T*>& vec_to_populate) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return;
    }
    int id;
    string name;

    while (file >> id) {
        getline(file >> ws, name);

        T* data_pointer = new T(id, name);
        vec_to_populate.push_back(data_pointer);
    }
    file.close();
}
// Function to populate data from a file into a vector of objects with additional conditions
template<class D, class S>
void Populate_from_file_2(string filename, vector<S*>& vec_to_populate, D*& data_pointer = nullptr, int user_dept_Id = -1, string user_name = "\0") {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return;
    }
    int id, dept_Id;
    string name;
    bool check = false;
    bool check2 = false;

    if (is_same<D, Manager>::value) { //If Manager Calls the Function.
        while (file >> id && !check) {
            getline(file >> ws, name, '\t');
            file >> dept_Id;

            if (dept_Id == user_dept_Id && user_dept_Id != -1) {
                check = true;
                data_pointer = new D(id, name, vec_to_populate[dept_Id]); // dept_vec[0]
                vec_to_populate[dept_Id]->setManager((Manager*)data_pointer);
            }
            else if (user_dept_Id == -1) {
                data_pointer = new D(id, name, vec_to_populate[dept_Id]); // dept_vec[0]
                vec_to_populate[dept_Id]->setManager((Manager*)data_pointer);
                check2 = true;
            }
        }
        if (check2) check = true;
        if (!check)
            cout << "Manager of this Department Not Exist.\n";
    }
    else if (is_same<D, Employee>::value) { // if Employee Calls the Function.
        while (file >> id && !check) {
            getline(file >> ws, name, '\t');
            file >> dept_Id;

            if (dept_Id == user_dept_Id && user_name == name) {
                check = true;
                data_pointer = new D(id, name, vec_to_populate[dept_Id]);
                //  vec_to_populate[dept_Id]->addEmployees((Employee*)data_pointer);
            }
        }
        if (!check)
            cout << "Employee with this id or Dept not found!\n";
    }

    file.close();

}
// Function to populate complaints data from a file into vectors of complaints, teachers, and departments
template<class C, class T, class D>
void Populate_Complaints(string filename, vector<C*>& cmps_vec, vector<T*>& tech_vec, vector<D*>& dept_vec) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return;
    }
    int id = 0, dept_Id = 0, tech_id = 0, status_int = 0, year = 0, mon = 0, day = 0;
    string descrption;
    std::tm Time = {};
    C* cmp = nullptr;

    while (file >> id) {
        getline(file >> ws, descrption, '\t');
        file >> tech_id;
        file >> dept_Id;
        file >> status_int;
        file >> year;
        file >> mon;
        file >> day;

        Time.tm_year = year;
        Time.tm_mon = mon;
        Time.tm_mday = day;


        switch (status_int)
        {
        case 0:
            cmp = new C(id, tech_vec[tech_id], dept_vec[dept_Id], descrption, State::New);
            break;
        case 1:
            cmp = new C(id, tech_vec[tech_id], dept_vec[dept_Id], descrption, State::Assigned);
            break;
        case 2:
            cmp = new C(id, tech_vec[tech_id], dept_vec[dept_Id], descrption, State::Resolved);
            break;
        case 3:
            cmp = new C(id, tech_vec[tech_id], dept_vec[dept_Id], descrption, State::Completed);
            break;
        case 4:
            cmp = new C(id, tech_vec[tech_id], dept_vec[dept_Id], descrption, State::Closed);
            break;
        default:
            break;
        }
        cmp->setTime(Time);
        tech_vec[tech_id]->addComplaint((Complaint*)cmp);
        dept_vec[dept_Id]->addComplaint((Complaint*)cmp);
        cmps_vec.push_back((Complaint*)cmp);
    }
    file.close();
}
// Function to populate all employees data from a file into vectors of employees and departments
template<class E, class D>
void Populate_All_Emps(string filename, vector<E*>& emps_vec, vector<D*>& dept_vec) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return;
    }

    int id = 0, dept_id = 0;
    string name;

    while (file >> id) {
        getline(file >> ws, name, '\t');
        file >> dept_id;

        E* Emp_pointer = new E(id, name, dept_vec[dept_id]);
        dept_vec[dept_id]->addEmployees((Employee*)Emp_pointer);
        emps_vec.push_back((Employee*)Emp_pointer);

    }
    file.close();
}
// Function to populate tasks data from a file into vectors of departments
template<class D>
void Populate_Tasks(string filename, vector<D*>& dept_vec, int user_dept_id = 0) {
    ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file: " << filename << std::endl;
        return;
    }
    int dept_id = 0, cmp_id = 0, emp_id = 0;
    string description;
    map<int, vector<int>> cmp_with_emps;

    while (file >> dept_id) {
        getline(file >> ws, description, '\t');
        file >> cmp_id;
        file >> emp_id;

        if (dept_id == user_dept_id) {
            cmp_with_emps[cmp_id].push_back(emp_id);
        }
    }

    file.close();
    //For Each Complaint Get its Manager(Manager Should be there) and Assign task to employees of that complaint.
    if (dept_vec[dept_id]->GetMgr() != NULL) {
        for (const auto& entry : cmp_with_emps) {
            int c_id = entry.first;
            vector<int> e_ids = entry.second;
            vector<Employee*> Ass_emps = dept_vec[dept_id]->GetMgr()->assignComplaintsAsTasks(dept_vec[dept_id]->Get_Cmp_of_id(c_id), e_ids, description);

            for (Employee* e : Ass_emps) {
                cout << e->getName() << "'s tasks:\n";
                //    emp->viewTask();
                cout << "-----------------------\n";
            }
        }
    }
    else
        cout << "No Manager Exist. Assign Manager First!\n";

}
// Function to populate data from a vector of objects into a file
template<class S>
void Populate_to_file(string filename, vector<S*>& vec_to_store) {
    ofstream file(filename, ios::trunc);

    if (file.is_open()) {
        if (is_same<S, Teacher>::value) {
            for (S* tech : vec_to_store) {
                file << tech->getID() << " ";
                file << tech->getName() << "\n";
            }
        }
    }
    file.close();
}
// Function to populate managers data from a vector of departments into a file
template<class D>
void Populate_mgrs_to_file(string filename, vector<D*>& dept_vec) {
    ofstream file(filename, ios::trunc);

    if (file.is_open()) {
        for (D* dept : dept_vec) {
            Manager* mgr = dept->GetMgr();
            if (mgr != NULL) {
                file << mgr->GetID() << " ";
                file << mgr->GetName() << "\t";
                file << dept->GetID() << "\n";
            }
        }
    }
    file.close();
}
// Function to populate employees data from a vector of departments into a file
template<class D>
void Populate_emps_to_file(string filename, vector<D*>& dept_vec) {
    ofstream file(filename, ios::trunc);

    if (file.is_open()) {
        for (D* dept : dept_vec) {
            vector<Employee*> emps = dept->Get_Dept_Emps();
            for (Employee* e : emps) {
                file << e->GetID() << " ";
                file << e->getName() << "\t";
                file << dept->GetID() << "\n";
            }
        }
    }
    file.close();
}
// Function to populate complaints data from a vector of departments into a file
template <class D>
void Populate_cmps_to_file(string filename, vector<D*>& dept_vec) {
    ofstream file(filename, ios::trunc);

    if (file.is_open()) {
        for (D* dept : dept_vec) {
            vector<Complaint*> cmps = dept->getComplaints();
            for (Complaint* c : cmps) {
                file << c->getID() << " ";
                file << c->getDescription() << '\t';
                file << c->Get_teach_id() << '\t';
                file << c->Get_dept_id() << '\t';
                file << c->currState() << '\t';
                file << c->GetTime().tm_year << '\t';
                file << c->GetTime().tm_mon << '\t';
                file << c->GetTime().tm_mday << '\n';
            }
        }
    }
    file.close();
}
// Function to populate tasks data from a vector of departments into a file
template<class D>
void Populate_Tasks_to_file(string filename, vector<D*> dept_vec) {
    ofstream file(filename,ios::app);

    if (file.is_open()) {
        for (D* dept : dept_vec) {
            Manager* mgr = dept->GetMgr();
            if (mgr != NULL) {
                vector<Task*> tasks = mgr->GetTasks();
                for (Task* t : tasks) {
                    vector<Employee*> emps_of_task = t->getAssignedEmployees();
                    for (Employee* e : emps_of_task) {
                        file << dept->GetID() << " ";
                        file << t->getDescription() << "\t";
                        file << t->getAssignedComplaint()->getID() << " ";
                        file << e->GetID() << "\n";
                    }
                }
            }
        }
    }

    file.close();
}



