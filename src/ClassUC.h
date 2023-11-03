#ifndef CLASSUC_H
#define CLASSUC_H

#include <string>
#include <vector>
#include "slot.h"
#include <algorithm>

/**
 * @brief class to show tha class uc
 */
class ClassUC {
public:
    ClassUC();
    ClassUC(const std::string &ucCode, const std::string &classCode, const std::vector<Slot> &schedule);
    ClassUC(const std::string &ucCode, const std::string &classCode);
    void addSlot(Slot slot);
    void setSlots(vector<Slot> slots);
    bool operator<(const ClassUC& other) const;
    bool operator==(const ClassUC& other) const;

    const std::string &getClassCode() const;
    const std::string &getUcCode() const;
    const std::vector<Slot> &getSchedule() const;
    void sortShedule();
    void print();
private:
    std::string ucCode_;
    std::string classCode_;
    std::vector<Slot> schedule_;
};

#endif
