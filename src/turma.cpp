#include "Turma.h"

using namespace std;

Turma::Turma(int code) : code(code) {}

int Turma::getCode() const {
    return code;
}

void Turma::addSloth(const Slot& slot) {
    slots.push_back(slot);
}

const list<Slot>& Turma::getSlots() const {
    return slots;
}
