#include "uc.h"

/**
 * @brief Constructor for the Uc class
 *
 * @param ucId The identifier of the Uc
 *
 * @param ucYear The year of the Uc
 *
 * @param ucSemester The semester of the Uc
 *
 * @param ucSlot A vector of slots associated with the Uc
 *
 * Time Complexity: O(n), where 'n' is the number of slots in 'ucSlot'
 */
Uc::Uc(string ucId,int ucYear,int ucSemester,vector<Slot> ucSlot) {
    this->ucId=ucId;
    this->ucSemester=ucSemester;
    this->ucSlot=ucSlot;
    this->ucYear=ucYear;}

/**
 * @brief function to get te year of the UC
 *
 * @return the year of the UC
 *
 * Time complexity O(1)
 */
int Uc::getUcYear() const{
    return ucYear;
}

/**
 * @brief function to get the semester of the UC
 *
 * @return the semester of the Uc.
 *
 * Time complexity O(1)
 */
int Uc::getUcSemester() const{
    return ucSemester;
}

/**
 * @brief function to get the list of slots
 *
 * @return vector of slot
 *
 * Time complexity O(1)
 *
 */
vector<Slot> Uc::getUcSlot() const {
    return ucSlot;
}

/**
 * @brief function to get the identifier of the Uc
 *
 * @return the identifier of the Uc
 *
 * Time complexity O(1)
 */
string Uc::getUcId() const {
    return ucId;
}

/**
 * @brief function to add a Slot to the list of slots associated with the Uc
 *
 * @param slot The Slot to add to the Uc
 *
 * Time Complexity: O(1)
 */
void Uc::addUcSlot(const Slot& slot){
    ucSlot.push_back(slot);
}

