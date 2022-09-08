// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "Streamable.h"
#include <iostream>

namespace sdds {
    Streamable::~Streamable() {}

    std::ostream& operator<<(std::ostream& ostr, const Streamable& src) {
        if (src) {
            src.write(ostr);
        }
        return ostr;
    }
    std::istream& operator>>(std::istream& istr, Streamable& src) {
        return src.read(istr);
    }

}
