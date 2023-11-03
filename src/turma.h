#ifndef TURMA_H
#define TURMA_H

#include <string>
#include <list>
#include "slot.h"
using namespace std;
/**
 * @brief class to show the class of a student
 */


class Turma {
public:
    Turma(int code);
    
    int getCode() const;
    
    void addSloth(const Slot& slot);

    void removeSlot(const Slot& slot);
    
    const list<Slot>& getSlots() const;

private:
    int code; 
    list<Slot> slots;
};

#endif
