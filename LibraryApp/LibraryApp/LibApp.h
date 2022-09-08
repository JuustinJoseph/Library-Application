// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef LibApp_h
#define LibApp_h
#include <stdio.h>
#include "Menu.h"
#include <iomanip>
#include "Menu.h"
#include "LibApp.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"

using namespace std;

namespace sdds{

class LibApp{
    
    char m_filename[256];
    bool m_changed;
    Menu m_mainMenu;
    Menu m_exitMenu;
    Publication* record[SDDS_LIBRARY_CAPACITY]{};
    int m_numOfPub = 0;
    int m_lastLibNum = 0;
    
    Menu PubType;
    
    bool confirm(const char* message);
    
    void load();  // prints: "Loading Data"<NEWLINE>
    void save();  // prints: "Saving Data"<NEWLINE>
    int search(int typeOfSearch);
    
    Publication* getPub(int libRef);
    
    void returnPub();  /*  Calls the search() method.
                        prints "Returning publication"<NEWLINE>
                        prints "Publication returned"<NEWLINE>
                        sets m_changed to true;
                        */
    void newPublication();
    void removePublication();
    void checkOutPub();
    
    bool exit();
    
public:
    
    LibApp(const char* filename);
    void run();
    ~LibApp();
    
};

}
#endif /* LibApp_h */
