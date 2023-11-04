
#include <utility>

#include "Student.h"

using namespace std;
/**
 * @brief Default constructor for the student class
 *
 * Time Complexity O(1)
 */
Student::Student() {
    this->code = 0;
    this->name = "";
}
/**
 * @brief Constructor of the class Student
 *
 * @param code of the Student
 *
 * @param name of the Student
 *
 * Time Complexity O(1)
 */
Student::Student(int code, const string& name) : code(code), name(name) {}

/**
 * @brief function to get the student code
 *
 * @return code of the student
 *
 * Time complexity O(1)
 */
int Student::getCode() const {
    return code;
}
 /**
  * @brief function to get the student name
  *
  * @return name of the student
  *
  * Time Complexity O(1)
  */
string Student::getName() const {
    return name;
}

/**
 * @brief Add a ClassUC to the student's list of classes
 *
 * @param newClassUc the classUc to be added
 *
 * Time Complexity O(1)
 */
void Student::addClassUC(const ClassUC& newClassUc){
    classes.push_back(newClassUc);
}

/**
 * @brief Overloaded less than operator for comparing students based on their codes
 *
 * @param other The students to compare with
 *
 * @return True if this student's code is less than the other student's code, otherwise false
 *
 * Time Complexity O(1)
 */
bool Student::operator<(const Student &other) const {
    return this->code<other.code;
}
/**
 * @brief Overloaded equality operator for comparing students based on their codes and name
 *
 * @param other The students to compere with
 *
 * @return True if the name and the code are same, otherwise false
 *
 * Time Complexity O(1)
 */
bool Student::operator==(const Student &other) const{
    if(this->code==other.getCode() and this->name==other.getName()){return true;}
    return false;
}

/**
 * @brief function to print the student information
 *
 * Time Complexity O(1)
 */
void Student::print_student() const{
    cout << name << '/' << code<< '\n';
}

/**
 * @brief function to print the classes that the student is enrolled
 *
 * Time complexity O(n)
 */
void Student::print_classes() const{
    for (int i=0;i<classes.size()-1;i++) {
    cout << classes[i].getUcCode() << " " << classes[i].getClassCode() << "|";}
    cout << classes[classes.size()-1].getUcCode() << " " << classes[classes.size()-1].getClassCode() <<"|";
}
/**
 * @brief function to print the student information and their enrolled class
 *
 * Time complexity O(1)
 */
void Student::print() const{
    cout << "Student: "; print_student();
    cout << "Classes: "; print_classes();
    cout<< '\n';
}

/**
 * @brief function to get the list of ClassUC objects the student is enrolled in.
 *
 * @return A vector of ClassUC objects.
 *
 * Time complexity O(1)
 */
vector<ClassUC> Student::getclassUC() const {
    return classes;
}
/**
 * @brief function to get the schedule of the student, mapping ClassUC to a vector of slots.
 *
 * @return A map of ClassUC to a vector of slots.
 *
 * Time complexity O(1)
 */
map<ClassUC, vector<Slot>> Student::getSchedule() const {
    return schedule;

}

/**
 * @brief function to remove the schedule for a specific ClassUC.
 *
 * @param classUc the ClassUC for which to remove the schedule.
 *
 * Time complexity O(1)
 */
void Student::removeSchedule(const ClassUC& classUc){
    schedule.erase(classUc);
}
/**
 * @brief function to add the schedule for a specific ClassUC, mapping it to a vector of slots..
 *
 * @param classUc the ClassUC for which to add the schedule.
 *
 * @param slot the vector of slots to add to the schedule.
 *
 * Time complexity O(1)
 */
void Student::addSchedule(const ClassUC& classUc, const vector<Slot>& slot)  {
    schedule[classUc] = slot;
}
/**
 * @brief function to Compare function to sort slots for the student's schedule.
 *
 * @param a The first slot.
 *
 * @param b The second slot
 *
 * Time complexity O(1)
 */
bool slotSorter_student(const Slot& a,const Slot& b){
    return a.getStart()<b.getStart();

}
/**
 * @brief function to remove the schedule for a specific ClassUC.
 *
 * Time complexity  O(M * N * log N),  M is the number of elemets of schedule e N is the medium size medium of  vectors in schedule
 *
 */

void Student::sortSchedule() {
    for(auto a:schedule){
        sort(a.second.begin(),a.second.end(), slotSorter_student);
    }
}
/**
 * @brief function Set the list of ClassUC objects for the student.
 *
 * @param classe The new list of ClassUC objects.
 *
 * Time complexity O(1)
 */

void Student::setCLassUc(vector<ClassUC> classe) {
    classes=classe;
}

