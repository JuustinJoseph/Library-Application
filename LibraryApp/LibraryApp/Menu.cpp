// Final Project Milestone 1
// Menu Module
// File    menuTester.cpp
// Version 1.0
// Author    Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////


#include <iostream>
#include "Menu.h"
#include "Utils.h"
#include "string.h"

using namespace std;

namespace sdds {

    MenuItem::MenuItem() {
        m_item = nullptr;
    }

    MenuItem::MenuItem(const char *item) {
        if (item != nullptr && item[0]) {
            m_item = new char[strlen(item) + 1];
            strcpy(m_item, item);
        } else {
            m_item = nullptr;
        }
    }

    MenuItem::operator bool() const {
        return m_item[0] != '\0';
    }

    MenuItem::operator const char *() const {
        return m_item;
    }

    ostream &MenuItem::display(ostream &ostr) const {
        if (*this){
            ostr << m_item;
        }
        return ostr;
    }

    MenuItem::~MenuItem() {
        delete[] m_item;
    }

    Menu::Menu() {
        m_title.m_item = nullptr;
    }

    Menu::Menu(const char *item) {
        if (item != nullptr && item[0] != '\0') {
            m_title.m_item = new char[strlen(item) + 1];
            strcpy(m_title.m_item, item);
        } else {
            m_title.m_item = nullptr;
        }
    }

    ostream &Menu::displayTitle(ostream &ostr) const {
        if (m_title.m_item != nullptr && m_title.m_item[0] != '\0') {
            ostr << m_title.m_item;
        }
        return ostr;
    }

    ostream &Menu::displayMenu(ostream &ostr) const {
        if (m_title.m_item != nullptr && m_title.m_item[0] != '\0') {
            displayTitle(ostr);
            ostr <<  endl;
        }
        for (int i = 0; i < count; i++) {
            ostr.setf(ios::right);
            ostr << ' ' << i + 1 << "- ";
            arr[i]->display(ostr);
            ostr << endl;
        }

        ostr << " 0- Exit" << endl << "> ";

        return ostr;
    }

    unsigned int Menu::run() const {
        displayMenu(cout);
        return getInput(count);

    }

    int Menu::operator~() {
        displayMenu(cout);
        return getInput(count);
    }

    Menu &Menu::operator<<(const char *menuitemConent) {
        if (count < MAX_MENU_ITEMS) {
            arr[count] = new MenuItem(menuitemConent);
            count++;
        }
        return *this;
    }

    Menu::operator int() const {
        return count;
    }

    Menu::operator unsigned int() const {
        return count;
    }

    Menu::operator bool() const {
        return (count > 0);
    }

    const char *Menu::operator[](int index) const {
        if (index % count == 0) {
            index = 0;
        }
        return *this->arr[index];

    }

    ostream& operator << (ostream &ostr, const Menu& obj){
        return obj.displayTitle(ostr);
    }

    Menu::~Menu() {
        for (int i = 0; i < count; i++) {
            delete arr[i];
        }
    }
}
