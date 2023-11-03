#include "slot.h"

/**
 * @brief Constructor for the Slot class.
 *
 * @param day The day of the slot.
 *
 * @param start The start time of the slot.
 *
 * @param duration The duration of the slot.
 *
 * @param type The type of the slot.
 *
 * Time Complexity: O(1)
 */

Slot::Slot(const string &day, const float &start, const float &duration, const string &type)
        : day_(day), start_(start), duration_(duration), type_(type),endTime(start+duration) {}


/**
 * @brief function to get the day of the slot
 *
 * @return the day of the slot.
 *
 * Time Complexity: O(1)
 */
const string &Slot::getDay() const {
    return day_;
}

/**
 * @brief function to get the start time of the slot
 *
 * @return the start time of the slot.
 *
 * Time Complexity: O(1)
 */

const float &Slot::getStart() const {
    return start_;
}

/**
 * @brief function to get duration of the slot
 *
 * @return the duration of the slot.
 *
 * Time complexity O(1)
 */

const float &Slot::getDuration() const {
    return duration_;
}

/**
 * @brief function to get the type of the slot
 *
 * @return the type of the slot.
 *
 * Time complexity 0(1)
 */
const string &Slot::getType() const {
    return type_;
}

/**
 * @brief function to get the end time of the slot.
 *
 * @return the end time of the slot.
 *
 * Time Complexity: O(1)
 */
float Slot::getEndTime() const {
    return start_+duration_;
}

/**
 * @brief Default constructor for the slot class.
 *
 * Time complexity 0(1)
 */

Slot::Slot() {
    day_="0";
    start_=0.0;
    duration_=0.0;
    endTime=0.0;
    type_="0";
}

/**
 * @brief function to check if the current slot overlaps with another slot.
 *
 * @param other The other slot to check for overlap.
 *
 * @return True if the slots overlap, otherwise false.
 *
 * Time Complexity: O(1)
 */
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

