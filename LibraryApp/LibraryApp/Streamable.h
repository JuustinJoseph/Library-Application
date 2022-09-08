// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////

#ifndef streamable_h
#define streamable_h

#include <stdio.h>
#include <iostream>
namespace sdds{

class Streamable{
public:
    virtual std::ostream& write(std::ostream& os)const = 0;
    virtual std::istream& read(std::istream& is) = 0;
    virtual bool conIO(std::ios& io)const = 0;
    virtual operator bool()const = 0;
    virtual ~Streamable();
    
};

std::ostream& operator<<(std::ostream& ostr, const Streamable& src);
std::istream& operator>>(std::istream& istr, Streamable& src);

}

#endif /* streamable_h */
