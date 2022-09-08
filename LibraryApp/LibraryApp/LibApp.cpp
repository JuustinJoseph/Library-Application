// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////
///

#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "LibApp.h"
#include"Utils.h"
#include <fstream>
using namespace std;
using namespace sdds;

namespace sdds {

LibApp::LibApp(const char* fileName)
:m_changed(false),
m_mainMenu("Seneca Library Application"),
m_exitMenu("Changes have been made to the data, what would you like to do?"),
PubType("Choose the type of publication:") {
    
    strcpy(m_filename, fileName);
    
    m_mainMenu << "Add New Publication"
    << "Remove Publication"
    << "Checkout publication from library"
    << "Return publication to library";
    
    m_exitMenu << "Save changes and exit"
    << "Cancel and go back to the main menu";
    
    PubType << "Book"
    << "Publication";
    
    load();
}

LibApp::~LibApp() {
    for (int i = 0; i < m_numOfPub; i++) {
        delete record[i];
    }
}

bool LibApp::confirm(const char* message) {
    Menu temp(message);
    temp << "Yes";
    
    int input;
    input = temp.run();
    
    
    if (input == 1) {
        return true;
    }
    else
        return false;
}

void LibApp::load() {
    
    cout << "Loading Data" << endl;
    ifstream infile(m_filename);
    char input;
    
    for (int i = 0; infile && i < SDDS_LIBRARY_CAPACITY; i++) {
        infile >> input;
        infile.ignore();
        
        if (infile) {
            
            if (input == 'P') {
                record[i] = new Publication;
            }
            else if (input == 'B') {
                record[i] = new Book;
            }
            
            if (record[i]) {
                infile >> *record[i];
                m_lastLibNum = record[i]->getRef();
                m_numOfPub++;
            }
        }
    }
}

void LibApp::save() {
    cout << "Saving Data" << endl;
    ofstream onfile(m_filename);
    for (int i = 0; i < m_numOfPub; i++) {
        if (record[i]->getRef() != 0){
            onfile << *record[i] << endl;
        }
    }
    onfile.close();
}

int LibApp::search(int type) {
    
    PublicationSelector temp("Select one of the following found matches:", 15);
    int pubtype = 0;
    char title[256]{};
    int libRef = 0;
    bool result = true;
    
    do {
        pubtype = PubType.run();
        if (pubtype == 0){
            break;
        }
        
        cin.ignore(1000, '\n');
        cout << "Publication Title: ";
        cin.getline(title, 256);
        
        if (type == 1) {
            
            if (pubtype == 1){
                for (int i = 0; i < m_numOfPub; i++){
                    const char recordType = record[i]->type();
                    if (recordType == 'B' && record[i]->getRef() && record[i]->operator==(title)) {
                        temp << record[i];
                    }
                }
                result = false;
            }
            
            else if (pubtype == 2) {
                for (int i = 0; i < m_numOfPub; i++) {
                    const char recordType = record[i]->type();
                    if (recordType == 'P' && record[i]->getRef() && record[i]->operator==(title)) {
                        temp << record[i];
                    };
                }
                result = false;
            }
        }
        
        else if (type == 2) {
            if (pubtype == 1) {
                for (int i = 0; i < m_numOfPub; i++) {
                    const char recordType = record[i]->type();
                    int loanStatus = record[i]->onLoan();
                    if (loanStatus && recordType == 'B' && record[i]->getRef() && record[i]->operator==(title)) {
                        temp << record[i];
                    }
                }
            }
            
            else if (pubtype == 2) {
                for (int i = 0; i < m_numOfPub; i++) {
                    const char recordType = record[i]->type();
                    int loanStatus = record[i]->onLoan();
                    if (loanStatus && recordType == 'P' && record[i]->getRef() && record[i]->operator==(title)) {
                        temp << record[i];
                    };
                }
                result = false;
            }
            
        }
        
        else if (type == 3) {
            if (pubtype == 1) {
                for (int i = 0; i < m_numOfPub; i++) {
                    const char recordType = record[i]->type();
                    int loanStatus = record[i]->onLoan();
                    if (!loanStatus && recordType == 'B' && record[i]->getRef() && record[i]->operator==(title)) {
                        temp << record[i];
                    }
                }
                result = false;
            }
            
            else if (pubtype == 2) {
                for (int i = 0; i < m_numOfPub; i++) {
                    const char recordType = record[i]->type();
                    int loanStatus = record[i]->onLoan();
                    
                    if (!loanStatus && recordType == 'P' && record[i]->getRef() && record[i]->operator==(title)) {
                        temp << record[i];
                    };
                }
                result = false;
            }
        }
        
        else if (pubtype == 0)
            result = false;
        
        if (pubtype != 0 && temp) {
            temp.sort();
            libRef = temp.run();
            
            if (libRef > 0) {
                cout << *getPub(libRef) << endl;
                result = false;
            }
            
            if (libRef==0) result = true;
        }
        else {
            cout << "No matches found!" << endl;
        }
        
    }while (0);
    
    
    if (result){
        cout << "Aborted!" << endl;
    }
    
    return libRef;
}

void LibApp::returnPub() {
    int libRef{};
    
    cout << "Return publication to the library" << endl;
    libRef = search(2);
    
    if (libRef && confirm("Return Publication?")) {
        Publication* temp = getPub(libRef);
        int numOfDays = Date() - temp->checkoutDate();
        
        if (numOfDays > SDDS_MAX_LOAN_DAYS) {
            int numOfDaysExtra = numOfDays - SDDS_MAX_LOAN_DAYS;
            double penalty = numOfDaysExtra * 0.5;
            
            cout << "Please pay $";
            cout.setf(ios::fixed);
            cout.precision(2);
            cout << penalty << " penalty for being " << numOfDaysExtra << " days late!" << endl;
        }
        temp->set(0);
        m_changed = true;
        cout << "Publication returned" << endl;
    }
}


void LibApp::newPublication() {
    if (m_numOfPub == SDDS_LIBRARY_CAPACITY) {
        cout << "Library is at its maximum capacity!" << endl;
        return;
    }
    
    cout << "Adding new publication to the library" << endl;
    
    Publication* pub{};
    int type = PubType.run();
    bool result = true;
    do {
        if (type == 0){
            break;
        }
        
        if (type == 1){
            pub = new Book;
        }
        
        else if (type == 2){
            pub = new Publication;
        }
        
        cin.ignore(1000, '\n');
        cin >> *pub;
        
        if (cin.fail()) {
            cin.ignore(1000, '\n');
            cin.clear();
            break;
        }
        
        if (confirm("Add this publication to the library?")) {
            result = false;
            
            if (*pub) {
                m_changed = true;
                m_lastLibNum++;
                record[m_numOfPub] = pub;
                m_numOfPub++;
                pub->setRef(m_lastLibNum);
                cout << "Publication added" << endl;
            }
            else {
                cout << "Failed to add publication!" << endl;
                delete pub;
            }
            
        }
        else {
            break;
        }
    } while (0);
    
    if (result)
    {
        delete pub;
        cout << "Aborted!" << endl;
    }
}

void LibApp::removePublication() {
    
    cout << "Removing publication from the library" << endl;
    int libRef = search(1);
    
    if (libRef && confirm("Remove this publication from the library?")) {
        getPub(libRef)->setRef(0);
        m_changed = true;
        cout << "Publication removed" << endl;
    }
}

void LibApp::checkOutPub() {
    
    cout << "Checkout publication from the library" << endl;
    int libRef = search(3);
    
    int input;
    if (libRef != 0) {
        if (confirm("Check out publication?")) {
            
            cout << "Enter Membership number: ";
            cin >> input;
            
            if (input < 10000 || input > 99999) {
                cout << "Invalid membership number, try again: ";
                cin >> input;
            }
            
            getPub(libRef)->set(input);
            m_changed = true;
            cout << "Publication checked out" << endl;
        }
    }
}
}

void LibApp::run() {
    int mainPick, pick, choice;
    bool flag= true;
    
    while (flag== true)
    {
        mainPick = m_mainMenu.run();
        
        if (mainPick == 1) {
            newPublication();
            cout << endl;
        }
        else if (mainPick == 2) {
            removePublication();
            cout << endl;
        }
        else if (mainPick == 3) {
            checkOutPub();
            cout << endl;
        }
        else if (mainPick == 4) {
            returnPub();
            cout << endl;
        }
        else {
            if (m_changed == false) {
                flag= false;
            }
            else if (m_changed == true) {
                pick = m_exitMenu.run();
                if (pick == 1) {
                    save();
                    flag= false;
                }
                else if (pick == 2) {
                    flag= true;
                    cout << endl;
                }
                else {
                    choice = confirm("This will discard all the changes are you sure?");
                    if (choice == 1) {
                        flag= false;
                    }
                    else {
                        flag= true;
                    }
                }
            }
        }
    }
    cout << "\n-------------------------------------------" << endl;
    cout << "Thanks for using Seneca Library Application" << endl;
    
}

Publication* LibApp::getPub(int libRef) {
    for (int i = 0; i < m_numOfPub; i++) {
        if (libRef == record[i]->getRef()) {
            return record[i];
        }
    }
    return nullptr;
}

