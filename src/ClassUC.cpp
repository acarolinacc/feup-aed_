#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "ClassUC.h"

/**
 * @brief this function gets the code of the class
 *
 * @return A constant reference to code
 *
 * Time complexity O(1)
 */
const string &ClassUC::getClassCode() const {
    return classCode_;
}
/**
 * @brief this function gets the UC code of the class
 *
 * @return A constant reference to the UC code
 *
 * Time complexity O(1)
 */
const string &ClassUC::getUcCode() const {
    return ucCode_;
}

/**
 * @brief this function adds a time slot to the class's schedule
 *
 * @param b The time slot to add
 *
 * Time complexity O(1)
 */
void ClassUC::addSlot(Slot b){
    schedule_.push_back(b);
}

/**
 * @brief Default constructor for ClassUC
 *
 * Time complexity O(1)
 */
ClassUC::ClassUC() {
this->ucCode_ = "";
this->classCode_ = "";
}

/**
 * @brief this function parameterizes constructor for ClassUC with unique code and class code
 *
 * @param ucCode The unique code of the class
 *
 * @param classCode The class code
 *
 * @param schedule A vector of time slots for the class
 *
 * Time complexity O(n), where 'n' is the size of the schedule
 */
ClassUC::ClassUC(const string &ucCode, const string &classCode, const vector<Slot> &schedule) : ucCode_(ucCode),classCode_(classCode),schedule_(schedule) {}

/**
 * @brief this function Parameterizes constructor for ClassUC with unique code and class code, but no schedule
 *
 * @param ucCode The unique code of the class
 *
 * @param classCode The class code
 *
 * Time complexity O(1)
*/
ClassUC::ClassUC(const std::string &ucCode, const std::string &classCode) {
    vector<Slot> clear;
    this->ucCode_=ucCode;
    this->classCode_=classCode;
    //this->schedule_=clear;
}

/**
 * @brief this function get the schedule of time slots for the class
 *
 * @return A constant reference to the schedule
 *
 * Time complexity O(1)
 */
const vector<Slot> &ClassUC::getSchedule() const {
    return schedule_;
}

/**
 * @brief this function compares two ClassUC objects based on their UC codes
 *
 * @param other The other ClassUC object to compare to
 *
 * @return True if the current object's UC code is less than the other's UC code
 *
 * Time complexity O(1)
 */
bool ClassUC::operator<(const ClassUC& other) const{
    return ucCode_<other.getUcCode();  //this can be changed
}

/**
 * @brief this function check if two ClassUC objects are equal based on their UC and class codes
 *
 * @param other The other ClassUC object to compare to
 *
 * @return True if the UC and class codes are equal
 *
 * Time complexity O(1)
 */
bool ClassUC::operator==(const ClassUC& other) const{
    return (ucCode_==other.getUcCode() and classCode_==other.getClassCode());
}

/**
 * @brief this function compares the  function for sorting time slots based on their start times
 *
 * @param a The first time slot
 *
 * @param b The second time slot
 *
 * @return True if the start time of 'a' is less than the start time of 'b'
 *
 * Time complexity O(1)
 */
bool slotSorter(const Slot& a,const Slot& b){
    return a.getStart()<b.getStart();

}

/**
 * @brief this function sort the schedule of time slots in ascending order of start times
 *
 * Time complexity O(n log n), where 'n' is the size of the 'schedule'
 */
void ClassUC::sortShedule() {
    sort(schedule_.begin(),schedule_.end(), slotSorter);

}

/**
 * @brief this function sets the schedule of time slots for the class
 *
 * @param slots The new schedule of time slots
 *
 *  Time complexity O(n), where 'n' is the size of the slots
 */
void ClassUC::setSlots(vector<Slot> slots) {
    schedule_=slots;

}

/**
 * @brief this function prints the details of the class, including its UC code and class code
 *
 * Time complexity O(1)
 */
void ClassUC::print() {
    std::cout << "UC Code: " << ucCode_ << std::endl;
    std::cout << "Class Code: " << classCode_ << std::endl;
}
