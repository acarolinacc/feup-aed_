#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "student.h"
#include "slot.h"
#include "ClassUC.h"
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <uc.h>
#include <map>
class DataManager{


public:
    //DataManager();
    set<Student> getStudents() ;
    const vector<ClassUC>& getAllUC() const;
    void addStudent(const Student& student);
    void addClassUC(const ClassUC& classUC);
    Student addSlothStudents(const Student& student);
    void readClasses();
    void readStudentClasses();
    void readClassesPerUC();
    vector<Student> UCstudents(const string& ucId) const ;
    vector<ClassUC> classOfUc(const string& ucId)const;
    vector<ClassUC> classuC_x_year(char year)const;
    vector<ClassUC> ucWithXStudents(int x);
    int numberStudentsUc(const string& ucId)const;
    int studentregisterUCs(int n);
    bool sorterOccupation(const ClassUC& a, const ClassUC& b) const;
    bool sorter(const ClassUC& a, const ClassUC& b);
    vector<Slot> getClassUCSchedule(const ClassUC& classUc2);
    vector<Slot> getClassSchedule(const string& classCode);
    vector<Slot> getUcSchedule(const string& UcId);

    vector<ClassUC> sortAllU();
    vector<ClassUC> sortAllU_occupation();

    bool ingressarEmUC(const string &upNumber, const string &ucCode);

    bool sairDeUC(const string &upNumber, const string &ucCode);

private:
    set<Student>students;
    vector<Slot> classes;
    vector<ClassUC> allUC_ ;

    vector<Student> StudentsOfClassUc(const string &uc_id, const string &class_id);

    Student getStudentByUP(const string &upNumber);

    ClassUC getClassUCByCode(const string &ucCode);

    bool haveScheduleConflict(const ClassUC &studentClass, const ClassUC &newClass) const;

};

#endif


