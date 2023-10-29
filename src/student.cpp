#include "Student.h"

using namespace std;

Student::Student(int code, const string& name) : code(code), name(name) {}

int Student::getCode() const {
    return code;
}

string Student::getName() const {
    return name;
}

void Student::addSloth(const Slot& slot) {
    sloths.push_back(slot);
}


const list<Slot>& Student::getSloths() const {
    return sloths;
}
void Student::addClassUC(const ClassUC& newClassUc){
    classes.push_back(newClassUc);
}


bool Student::operator<(const Student &other) const {
    return this->code<other.code;
}
bool Student::operator==(const Student &other) const{
    if(this->code==other.getCode() and this->name==other.getName()){return true;}
    return false;
}

void Student::print_student() const{
    cout << name << '/' << code<< '\n';
}

void Student::print_classes() const{
    for (int i=0;i<classes.size()-1;i++) {
    cout << classes[i].getUcCode() << " " << classes[i].getClassCode() << "|";}
    cout << classes[classes.size()-1].getUcCode() << " " << classes[classes.size()-1].getClassCode() <<"|";
}
void Student::print() const{
    cout << "Student: "; print_student();
    cout << "Classes: "; print_classes();
    cout<< '\n';
}
vector<ClassUC> Student::getclassUC() const {
    return classes;
}