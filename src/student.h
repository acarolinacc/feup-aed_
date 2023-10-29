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
#include <map>
using namespace std;

class Student {
public:
    Student();
    Student(int code, const string& name);

    int getCode() const;

    string getName() const;


    void removeSchedule(const ClassUC& classUc);
    map<ClassUC, vector<Slot>> getSchedule() const;
    void addSchedule(const ClassUC& classUc, Slot slot);
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
    vector<ClassUC> classes;
    map<ClassUC,vector<Slot>> schedule;




};

#endif
