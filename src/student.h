#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <list>
#include "slot.h"
#include <vector>
#include "uc.h"
#include "turma.h"
#include <iostream>
#include "ClassUC.h"
using namespace std;

class Student {
public:
    Student(int code, const string& name);

    int getCode() const;

    string getName() const;

    void addSloth(const Slot& slot);


    const list<Slot>& getSloths() const;
    void removeSloth(const Slot& slot);
    const list<Slot>& getSloth() const;
    void addClassUC(const ClassUC& newClassUc);
    bool operator<(const Student &other) const;
    bool operator==(const Student &other) const;
    void print_student()const;
    void print_classes()const;
    void print()const;
    vector<ClassUC>getclassUC() const;
private:
    int code;
    string name;
    list<Slot> sloths;
    vector<ClassUC> classes;



};

#endif
