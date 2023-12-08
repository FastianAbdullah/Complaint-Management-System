#include <iostream>
#include "Teacher.h"
#include <string>
#include <fstream>
#include <ctime>
Teacher::Teacher(int id,string name)
{
    this->id = id;
    this->name = name;
}
void Teacher::addComplaint(Complaint* comp)
{
    for (int i = 0; i < complaints.size(); i++)
    {
        if (comp->getID() == complaints[i]->getID())
        {
            cout << "Can't add Complaint with same ID\n";
            goto label;
        }

    }
    complaints.push_back(comp);
    label:
    return;
}
void Teacher::saveToFile(Teacher* teacher, Complaint* complaint)
{
    // Open a file in append mode
    ofstream file("Complaint.txt", std::ios::app);

    if (file.is_open()) {
        // Get the current time
        std::time_t currentTime = std::time(0);
        std::tm now;
        localtime_s(&now, &currentTime);
     
        // Write complaint details to the file
        file << complaint->getID() << " ";
        file << complaint->getDescription() << "\t";
        file << teacher->getID() << "\t";
        file << complaint->getAssociatedDepartment()->GetID() << " ";
        file << static_cast<int>(complaint->currState()) << "\t";
        file << (now.tm_year + 1900) << "\t" << (now.tm_mon + 1) << "\t" << now.tm_mday << "\n";
        // Close the file
        file.close();
    }
    else {
        std::cerr << "Error: Unable to open the file for writing.\n";
    }
}
const vector<Complaint*>& Teacher::getComplaints()
{
    return this->complaints;
}
void Teacher::reportFeedback(int id) {

    string args = {};

    for (int i = 0; i < complaints.size(); i++)
    {
        if (id == complaints[i]->getID())
        {
            
            if (complaints[i]->currState() == 2)
            {
                cout << "Enter Your Feedback ";
                cin >> args;
                if (args == "Satisfied")
                    complaints[i]->setFlag(1);
                else
                    complaints[i]->setFlag(0);
            }
            else
                cout << "\nYour Complaint is Still in working\nThanks for Your Patience\n";

        }
    }
}
string Teacher::getName()
{
    return this->name;
}
int Teacher::getID()
{
    return this->id;
}
void Teacher::printComplaints() {
    if (complaints.size() > 0)
    {
        
        cout << "---------------------------------------------\n";
        std::cout << "Complaints for Teacher " << name << " (ID: " << id << ")\n";
        for (const auto& comp : complaints) {
            cout << "\nComplaint ID : " << comp->getID() << "\nDescripton : " << comp->getDescription() << "\nComplaint's Department : " << comp->depName()
                << "\nComplaint's Teacher : " << comp->GetteacherName() << "\nComplaint's State : " << comp->currState() << endl;
            cout << "---------------------------------------------\n";
        }
    }
    else cout << "\nNo Complaints yet...\n";
}

