
#ifndef SLOT_H
#define SLOT_H

#include <string>

using namespace std;
/**
 * @brief class to show the duration of the class, the time of the class, and the day
 */
class Slot {
public:
    Slot();

    Slot(const string &day, const float &start, const float &duration, const string &type);

    const string &getDay() const;
    const float &getStart() const;
    const float &getDuration() const;
    const string &getType() const;
    float getEndTime()const;
    bool overlaps(const Slot &other) const;

private:
    string day_;
    float start_;
    float duration_;
    string type_;
    float endTime;
};

#endif //UNTITLED_SLOT_H

