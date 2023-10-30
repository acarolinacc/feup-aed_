#include <string>
#include <utility>
#include <vector>
#include "ClassUC.h"


const string &ClassUC::getClassCode() const {
    return classCode_;
}

const string &ClassUC::getUcCode() const {
    return ucCode_;
}

void ClassUC::addSlot(Slot b){
    schedule_.push_back(b);
}
ClassUC::ClassUC() {
this->ucCode_ = "";
this->classCode_ = "";
}

ClassUC::ClassUC(const string &ucCode, const string &classCode, const vector<Slot> &schedule) : ucCode_(ucCode),classCode_(classCode),schedule_(schedule) {}

ClassUC::ClassUC(const std::string &ucCode, const std::string &classCode) {
    vector<Slot> clear;
    this->ucCode_=ucCode;
    this->classCode_=classCode;
    //this->schedule_=clear;
}

const vector<Slot> &ClassUC::getSchedule() const {
    return schedule_;
}
bool ClassUC::operator<(const ClassUC& other) const{
    return ucCode_<other.getUcCode();  //this can be changed
}
bool ClassUC::operator==(const ClassUC& other) const{
    return ucCode_==other.getUcCode();
}
bool slotSorter(const Slot& a,const Slot& b){
    return a.getStart()<b.getStart();

}

void ClassUC::sortShedule() {
    sort(schedule_.begin(),schedule_.end(), slotSorter);

}

void ClassUC::setSlots(vector<Slot> slots) {
    schedule_=slots;

}
