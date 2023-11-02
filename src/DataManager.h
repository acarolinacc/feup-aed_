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
    void setStudents( set<Student> newStudents);

    void readClasses();
    void readStudentClasses();
    void readClassesPerUC();
    vector<Student> studentsOfClassUc(const ClassUC& classUc);
    vector<Student> UCstudents(const string& ucId) const ;
    vector<ClassUC> classOfUc(const string& ucId)const;
    vector<ClassUC> classuC_x_year(char year)const;
    vector<ClassUC> ucWithXStudents(int x);
    int numberStudentsUc(const string& ucId)const;
    int studentregisterUCs(int n);

    vector<Slot> getClassUCSchedule(const ClassUC& classUc2);
    vector<Slot> getClassSchedule(const string& classCode);
    vector<Slot> getUcSchedule(const string& UcId);
    Student getStudentSchedule(const Student& student);
    Student findStudent(const Student& student); //recebe um id e um nome e retorna o estudante com as suas turmas;

    bool classUcHaveLessThenXStudents(const ClassUC& classUc, int x);

    vector<ClassUC> sortAllU();
    vector<ClassUC> sortAllU_occupation();
    bool sorterOccupation(const ClassUC& a, const ClassUC& b) const;
    bool sorter(const ClassUC& a, const ClassUC& b);


    bool ingressarEmUC(const string &upNumber, const string &ucCode);

    bool sairDeUC(const string &upNumber, const string &ucCode);

private:
    set<Student>students;
    vector<Slot> classes;
    vector<ClassUC> allUC_ ;



    Student getStudentByUP(const string &upNumber);

    ClassUC getClassUCByCode(const string &ucCode);

    bool haveScheduleConflict(const ClassUC &studentClass, const ClassUC &newClass) const;

};

#endif


