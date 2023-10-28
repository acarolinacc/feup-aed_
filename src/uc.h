#ifndef UC_H
#define UC_H
#include <string>
#include "slot.h"
#include <vector>
using  namespace std;
class Uc{
public:
    Uc(string ucId,int ucYear,int ucSemester,vector<Slot> ucSlot);
    int getUcYear() const;
    int getUcSemester() const;
    string getUcId() const;
    vector<Slot> getUcSlot() const;
    void addUcSlot(const Slot& slot);




private:
    string ucId;
    int ucYear;
    int ucSemester;
    vector<Slot> ucSlot;
};





#endif