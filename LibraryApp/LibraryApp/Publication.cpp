// -----------------------------------------------------------
// Name: Justin Joseph          Date: 7/7/2022
//-----------------------------------------------------------
//I have done all the coding by myself and only copied the code
//that my professor provided to complete my project milestones.
//-----------------------------------------------------------
/////////////////////////////////////////////////////////////////

#include "Publication.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace sdds{

Publication::Publication(){
    m_title = nullptr;
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    m_date = Date();
}

Publication::Publication(const Publication& obj){
    operator=(obj);
}

Publication& Publication::operator=(const Publication& obj){
    
    delete[] m_title;
    m_title = nullptr;
    
    if (obj.m_title != nullptr){
        m_title = new char[strlen(obj.m_title)+1];
        strcpy(m_title, obj.m_title);
    }
    
    strcpy(m_shelfId, obj.m_shelfId);
    set(obj.m_membership);
    setRef(obj.m_libRef);
    m_date = obj.m_date;
    
    
    return *this;
    
}

void Publication::set(int member_id) {
    m_membership = member_id;
}

void Publication::setRef(int value){
    m_libRef = value;
}

void Publication::resetDate(){
    m_date = Date();
}

char Publication::type()const{
    return 'P';
}

bool Publication::onLoan()const{
    if (m_membership != 0){
        return true;
    }
    return false;
}

Date Publication::checkoutDate()const{
    return m_date;
}

bool Publication::operator==(const char* title)const{
    if (strstr(m_title, title) != nullptr)
    {
        return true;
    }
    return false;
}

Publication::operator const char* ()const{
    return  m_title;
}

int Publication::getRef()const {
    return m_libRef;
}

bool Publication::conIO(ios& io)const{
    
    return &io == &cin || &io == &cout;
}

ostream& Publication::write(std::ostream& ostr) const
{
    if (conIO(ostr))
    {
        ostr << "| " << m_shelfId << " | ";
        if (strlen(m_title) > SDDS_TITLE_WIDTH) {
            for (int i = 0; i < SDDS_TITLE_WIDTH ; i++) {
                ostr << m_title[i];
            }
        }
        else {
        
        ostr << setw(SDDS_TITLE_WIDTH) << left << setfill('.') << m_title;
        }
        ostr << " | ";
        if (m_membership == 0) {
            ostr << " N/A ";
        }
        else {
            ostr << m_membership;
        }
        ostr << " | " << m_date << " |";
    }
    else{
        ostr << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
    }
    return ostr;
}


istream& Publication::read(istream& istr){
    
    delete[] m_title;
    m_title = nullptr;
    
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    m_date = Date();
    
    char shelfId[SDDS_SHELF_ID_LEN + 1];
    char title[256 + 1];
    int membership = 0;
    int libRef = -1;
    Date date;
    
    if(conIO(istr)){
        cout << "Shelf No: ";
        istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1);
        
        if (strlen(shelfId) != SDDS_SHELF_ID_LEN) {
            istr.setstate(ios::failbit);
        }
        
        cout << "Title: ";
        istr.getline(title, 256 + 1);
        cout << "Date: ";
        istr >> date;
    }
    
    else{
        istr >> libRef;
        istr.ignore(1000, '\t');
        istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
        istr.getline(title, 256 + 1, '\t');
        istr >> membership;
        istr.ignore(1000, '\t');
        istr >> date;
    }
    
    if(!date)
    {
        istr.setstate(ios::failbit);
    }
    
    if(istr)
    {
        m_title = new char[strlen(title) + 1];
        strcpy(m_title, title);
        strcpy(m_shelfId, shelfId);
        m_membership = membership;
        m_date = date;
        m_libRef = libRef;
    }
    
    return istr;
}

Publication::operator bool() const{
    if (m_title != nullptr && m_shelfId[0] != '\0') {
        return true;
    }
    return false;
}

Publication::~Publication() {
    delete[] m_title;
}

}
