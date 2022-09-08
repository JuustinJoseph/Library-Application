// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "Utils.h"
#include <iostream>
#include "string.h"
using namespace std;

namespace sdds{
    int getInput(int num){

        int input = 0;
        bool flag = false;


        while (!flag) {

            cin >> input;
            if (cin.good() && input >= 0 && input <= num) {
                flag = true;
            }
            else{
                cout << "Invalid Selection, try again: ";
                cin.clear();
                cin.ignore(10000, '\n');
                flag = false;
            }
        }
        return input;
    }

}
