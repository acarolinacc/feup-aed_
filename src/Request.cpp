#include "Request.h"

#include <utility>

Request::Request(Student &student, ClassUC &wantedClass, string type) {
    this->student=student;
    this->wantedClass=wantedClass;
    this->type=type;
}

Student Request::getStudent() const {
    return student;
}

ClassUC Request::getClassUc() const {
    return wantedClass;
}

string Request::getType() const {
    return type;
}

void Request::printRequest() {
    std::cout << "Request Details:" << std::endl;
    std::cout << "Student:" << std::endl;
    student.print();
    std::cout << "Wanted Class: " << std::endl;
    wantedClass.print();
    std::cout << "Type: " << type << std::endl;
}






