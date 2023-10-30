#include "slot.h"

Slot::Slot(const string &day, const float &start, const float &duration, const string &type)
        : day_(day), start_(start), duration_(duration), type_(type),endTime(start+duration) {}

const string &Slot::getDay() const {
    return day_;
}

const float &Slot::getStart() const {
    return start_;
}

const float &Slot::getDuration() const {
    return duration_;
}

const string &Slot::getType() const {
    return type_;
}
float Slot::getEndTime() const {
    return start_+duration_;
}

Slot::Slot() {
    day_="0";
    start_=0.0;
    duration_=0.0;
    endTime=0.0;
    type_="0";
}

bool Slot::overlaps(const Slot &other) const {
    if (this->day_ != other.getDay()) {
        return false;
    }
    if (this->start_ >= other.getEndTime() || this->endTime <= other.getStart()) {
        return false;
    }
    if(this->type_ == "T" || other.getType() == "T") {
        return false;
    }
    return true;
}

