#ifndef CLASSUC_H
#define CLASSUC_H

#include <string>
#include <vector>
#include "slot.h"

class ClassUC {
public:
    ClassUC(const std::string &ucCode, const std::string &classCode, const std::vector<Slot> &schedule);
    ClassUC(const std::string &ucCode, const std::string &classCode);
    void addSlot(Slot slot);

    const std::string &getClassCode() const;
    const std::string &getUcCode() const;
    const std::vector<Slot> &getSchedule() const;

private:
    std::string ucCode_;
    std::string classCode_;
    std::vector<Slot> schedule_;
};

#endif
