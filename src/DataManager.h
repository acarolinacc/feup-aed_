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
class DataManager{


public:
    //DataManager();
    set<Student> getStudents() const;
    const vector<ClassUC>& getAllUC() const;
    void addStudent(const Student& student);
    void addClassUC(const ClassUC& classUC);
    void readClasses();
    void readStudentClasses();
    void readClassesPerUC();
    vector<Student> UCstudents(const string& ucId) const ;
    vector<ClassUC> classOfUc(const string& ucId)const;
    vector<ClassUC> classuC_x_year(char year)const;
    vector<ClassUC> ucWithXStudents(int x);
    vector<Student> StudentsOfClassUc(const string& uc_id,const string& class_id);
    int numberStudentsUc(const string& ucId)const;
    int studentregisterUCs(int n);
    bool sorterOccupation(const ClassUC& a, const ClassUC& b) const;
    bool sorter(const ClassUC& a, const ClassUC& b);

    vector<ClassUC> sortAllU();
    vector<ClassUC> sortAllU_occupation();
private:
    set<Student>students;
    vector<Slot> classes;
    vector<ClassUC> allUC_ ;
};








#endif