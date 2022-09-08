// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef Publication_hpp
#define Publication_hpp

#include <stdio.h>
#include <iostream>
#include "Streamable.h"
#include "Date.h"
#include "Lib.h"

namespace sdds{

class Publication : public Streamable{
    
    char* m_title{};
    char m_shelfId[SDDS_SHELF_ID_LEN + 1];
    int m_membership{ 0 };
    int m_libRef{ -1 };
    Date m_date;
    
public:
    
    Publication();
    Publication(const Publication& obj);
    Publication& operator=(const Publication& obj);
    virtual void set(int member_id);
    void setRef(int value);
    void resetDate();
    virtual char type()const;
    bool onLoan()const;
    Date checkoutDate()const;
    bool operator==(const char* title)const;
    operator const char* ()const;
    int getRef()const;
    bool conIO(std::ios& io)const;
    
    std::ostream& write(std::ostream& ostr) const;
    std::istream& read(std::istream& istr);
    operator bool() const;
    
    virtual ~Publication();
    
};

}

#endif /* Publication_hpp */
