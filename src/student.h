#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <list>
#include "slot.h"
#include <vector>
#include <iostream>
#include "ClassUC.h"
#include <map>
#include <algorithm>
using namespace std;
/**
 * @brief class for students representation
 */
class Student {
public:
    Student();
    Student(int code, const string& name);

    int getCode() const;

    string getName() const;
    void setCLassUc( vector<ClassUC> classe);
    void removeSchedule(const ClassUC& classUc);
    map<ClassUC, vector<Slot>> getSchedule() const;
    void addSchedule(const ClassUC& classUc, const vector<Slot>& slot) ;
    void addClassUC(const ClassUC& newClassUc);
    bool operator<(const Student &other) const;
    bool operator==(const Student &other) const;
    void print_student()const;
    void print_classes()const;
    void print()const;
    void sortSchedule();
    vector<ClassUC>getclassUC() const;

private:
    int code;
    string name;
    vector<ClassUC> classes;
    map<ClassUC,vector<Slot>> schedule;




};

#endif
