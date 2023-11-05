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
#include <map>
class DataManager{

/**
 * @brief the DataManager class manages data related to students and Ucs.
 */
public:
    //DataManager();
    set<Student> getStudents() ;
    const vector<ClassUC>& getAllUC() const;
    void addStudent(const Student& student);
    void addClassUC(const ClassUC& classUC);
    void setStudents( set<Student> newStudents);
    //read
    void readClasses();
    void readStudentClasses();
    //students
    vector<Student> studentYear(char year);
    vector<Student> studentsOfClassUc(const ClassUC& classUc);
    vector<Student> UCstudents(const string& ucId) const ;
    Student findStudent(const Student& student); //recebe um id e um nome e retorna o estudante com as suas turmas;
    //classUc
    vector<ClassUC> classOfUc(const string& ucId)const;
    vector<ClassUC> classuC_x_year(char year)const;
    vector<ClassUC> ucWithXStudents(int x);
    vector<ClassUC> getCLass(const string& classID);

    int numberStudentsUc(const string& ucId)const;
    int studentregisterUCs(int n);
    //shedule
    vector<Slot> getClassUCSchedule(const ClassUC& classUc2);
    vector<Slot> getClassSchedule(const string& classCode);
    vector<Slot> getUcSchedule(const string& UcId);
    Student getStudentSchedule(const Student& student);



    //sorter
    vector<ClassUC> sortAllU();
    vector<ClassUC> sortAllU_occupation();
    bool sorterOccupation(const ClassUC& a, const ClassUC& b) const;
    bool sorter(const ClassUC& a, const ClassUC& b);
    //auxiliar
    bool classUcHaveLessThenXStudents(const ClassUC& classUc, int x);
    void sortStudent(vector<Student>& students,string type);
    int extractLastNumber(const string &classCode);

    bool sortByLastNumber(const ClassUC &a, const ClassUC &b);

private:
    set<Student>students;
    vector<Slot> classes;
    vector<ClassUC> allUC_ ;

};

#endif


