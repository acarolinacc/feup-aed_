#include "Turma.h"

using namespace std;

/**
 * @brief Constructor of the class Turma
 * @param code the code representing Turma
 * Time complexity O(1)
 */
Turma::Turma(int code) : code(code) {}

/**
 * @brief fuction to get the code of the Turma
 * @return the code of the Turma
 * Time complexity O(1)
 */
int Turma::getCode() const {
    return code;
}
/**
 * @brief fuction to add a Slot to the list of slots associated with the Turma.
 * @param slot the slot to add the Turma
 * Time complexity O(1)
 */
void Turma::addSloth(const Slot& slot) {
    slots.push_back(slot);
}
/**
 * @brief fuction to get the list of slots associated with the Turma.
 * @return  a list of Slot objects.
 * Time complexity O(1)
 */
const list<Slot>& Turma::getSlots() const {
    return slots;
}
