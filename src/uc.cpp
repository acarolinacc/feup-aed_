
#include "uc.h"

Uc::Uc(string ucId,int ucYear,int ucSemester,vector<Slot> ucSlot) {
    this->ucId=ucId;
    this->ucSemester=ucSemester;
    this->ucSlot=ucSlot;
    this->ucYear=ucYear;}

int Uc::getUcYear() const{
    return ucYear;
}
int Uc::getUcSemester() const{
    return ucSemester;
}
vector<Slot> Uc::getUcSlot() const {
    return ucSlot;
}
string Uc::getUcId() const {
    return ucId;
}
void Uc::addUcSlot(const Slot& slot){
    ucSlot.push_back(slot);
}

