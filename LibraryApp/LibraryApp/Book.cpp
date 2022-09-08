// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////
///
#include "Book.h"
#include <iostream>
#include <iomanip>
using namespace std;
namespace sdds{

Book::Book(){
    m_authorName = nullptr;
}

Book:: Book(const Book& obj){
    operator=(obj);
}

Book& Book::operator=(const Book &Obj){
    delete [] m_authorName;
    m_authorName = nullptr;
    
    
    if (Obj.m_authorName != nullptr) {
        Publication::operator=(Obj);
        m_authorName = new char[strlen(Obj.m_authorName)+1];
        strcpy(m_authorName, Obj.m_authorName);
    }
    
    return *this;
}

char Book::type()const {
    return 'B';
}

ostream& Book::write(ostream& ostr) const {
    
    Publication::write(ostr);
    if (Publication::conIO(ostr)) {
        ostr << " ";
        
        if (strlen(m_authorName) > SDDS_AUTHOR_WIDTH) {
            for (int i = 0; i < SDDS_AUTHOR_WIDTH ; i++) {
                ostr << m_authorName[i];
            }
        }
        else{
            
            ostr << setw(SDDS_AUTHOR_WIDTH);
            ostr << left;
            ostr << setfill(' ');
            ostr << m_authorName;
        }
        ostr << " |";
    }
    else {
        ostr << "\t" << m_authorName;
    }
    
    return ostr;
    
}


std::istream& Book::read(std::istream& istr) {
    
    const int nameLength = 256;
    
    Publication::read(istr);
    
    delete[] m_authorName;
    m_authorName = nullptr;
    
    char authorName[nameLength + 1];
    
    if (Publication::conIO(istr)) {
        istr.ignore(1000, '\n');
        cout << "Author: ";
        istr.getline(authorName, nameLength + 1);
    }
    else {
        istr.ignore(1000, '\t');
        istr.get(authorName, nameLength + 1);
    }
    
    if (istr) {
        m_authorName = new char[strlen(authorName) + 1];
        strcpy(m_authorName, authorName);
    }
    
    return istr;
    
}

void Book::set(int memberid) {
    Publication::set(memberid);
    Publication::resetDate();
}

Book::operator bool() const {
    return (m_authorName != nullptr && m_authorName[0] != '\0' && Publication::operator bool() == true);
}

Book::~Book() {
    delete[] m_authorName;
}


}

