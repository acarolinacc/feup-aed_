#include "slot.h"

Slot::Slot(const string &day, const string &start, const string &duration, const string &type)
        : day_(day), start_(start), duration_(duration), type_(type) {}

const string &Slot::getDay() const {
    return day_;
}

const string &Slot::getStart() const {
    return start_;
}

const string &Slot::getDuration() const {
    return duration_;
}

const string &Slot::getType() const {
    return type_;
}
