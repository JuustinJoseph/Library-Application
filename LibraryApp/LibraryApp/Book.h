// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef Book_h
#define Book_h
#include "Publication.h"
#include <stdio.h>

namespace sdds{
class Book : public Publication{
    char* m_authorName;
    
public:
    Book();
    Book(const Book& obj);
    Book& operator=(const Book& Obj);
    virtual char type() const;
    std::ostream& write(std::ostream& ostr) const;
    std::istream& read(std::istream& istr);
    virtual void set(int memberid);
    virtual operator bool() const;
    virtual ~Book();
};
}

#endif /* Book_h */
