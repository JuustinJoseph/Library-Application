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

#ifndef MS1_MENU_H
#define MS1_MENU_H

#include <iostream>
#include "string.h"

using namespace std;

namespace sdds {

    const int MAX_MENU_ITEMS = 20;

    class Menu;

    class MenuItem {

        char* m_item;

        MenuItem();
        MenuItem(const char* item);
        MenuItem(const MenuItem& obj) = delete;
        MenuItem& operator=(const MenuItem& obj) = delete;
        operator bool() const;
        operator const char*()const;
        ~MenuItem();
        ostream &display(ostream& ostr) const;

        friend class Menu;

    };

    class Menu {

        MenuItem m_title;
        MenuItem* arr[MAX_MENU_ITEMS] = {};
        int count = 0;

    public:

        Menu();
        Menu(const char* item);
        Menu(const Menu& obj) = delete;
        Menu& operator=(const Menu obj) = delete;
        ostream& displayTitle(ostream& ostr) const ;
        ostream& displayMenu(ostream& ostr) const;
        int unsigned run() const;
        Menu& operator<<(const char* menuitemConent);
        operator int()const;
        operator unsigned int()const;
        operator bool()const;
        int operator~();
        const char* operator[](int index) const;
        ~Menu();

    };
    ostream& operator << (ostream &ostr, const Menu& obj);

}

#endif //MS1_MENU_H
