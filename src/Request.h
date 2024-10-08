
#ifndef FEUP_AED1_REQUEST_H
#define FEUP_AED1_REQUEST_H
#include "student.h"
#include "ClassUC.h"

/**
 * @brief function to register the requests made by the students
 */
class Request {
public:
    Request(Student &student,ClassUC &wantedClass,string type);
     Student getStudent() const;
     ClassUC getClassUc() const;
     string getType() const;
     void setType(string newType);
     void printRequest();

    bool operator==(const Request& other) const {

        return (student == other.student) && (wantedClass == other.wantedClass) && (type == other.type);
    }

private:
    Student student;
    ClassUC wantedClass;
    string type;

//type apresenta uma string com o tipo de operaçao, exemplo sair uc(SU)
//Entrar-E,Sair-S,,Uc-U,CLass-C
//

};


#endif //FEUP_AED1_REQUEST_H
