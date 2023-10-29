
#ifndef SLOT_H
#define SLOT_H

#include <string>

using namespace std;

class Slot {
public:
    Slot(const string &day, const string &start, const string &duration, const string &type);

    const string &getDay() const;
    const string &getStart() const;
    const string &getDuration() const;
    const string &getType() const;

private:
    string day_;
    string start_;
    string duration_;
    string type_;
};

#endif //UNTITLED_SLOT_H

