
#ifndef FEUP_AED1_REQUEST_H
#define FEUP_AED1_REQUEST_H
#include "student.h"
#include "ClassUC.h"

class Request {
public:
    Request(Student &student,ClassUC &wantedClass,string &type);
     Student getStudent() const;
     ClassUC getClassUc() const;
     string getType() const;


private:
    Student student;
    ClassUC wantedClass;
    string type;


};


#endif //FEUP_AED1_REQUEST_H
