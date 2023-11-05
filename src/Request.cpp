#include "Request.h"

#include <utility>

/**
 * @brief Constructor for the request class
 *
 * @param studentThe student making the request.
 *
 * @param wantedClass The class that the student wants.
 *
 * @param type The type of the request.
 *
 * Time complexity O(1)
 */
Request::Request(Student &student, ClassUC &wantedClass, string type) {
    this->student=student;
    this->wantedClass=wantedClass;
    this->type=type;
}

/**
 * @brief function to get the ClassUC associated with the request.
 *
 * @return the class that the student wants
 *
 * Time complexity O(1)
 */
Student Request::getStudent() const {
    return student;
}

/**
 * @brief function to get the type of the request
 *
 * @return The class that the student wants
 *
 * Time complexity O(1)
 */
ClassUC Request::getClassUc() const {
    return wantedClass;
}

/**
 * @brief function to print the details of the request, including the student, wanted class, and request type.
 *
 * @return The type of the request.
 *
 * Time complexity: O(1)
 */
string Request::getType() const {
    return type;
}

/**
 * @brief function to print the details of the request, including the student, wanted class, and request type
 *
 * Time complexity O(1)
 */
void Request::printRequest() {
    std::cout << "Detalhes do pedido:" << std::endl;
    student.print();
    std::cout << "Turma Desejada: " << std::endl;
    wantedClass.print();
    std::cout << "Tipo: " << type << std::endl;
}

/**
 * @brief Function to set the type of the request.
 *
 * @param newType The new type of the request.
 *
 * Time complexity: O(1)
 */

void Request::setType(string newType) {
    type=newType;

}






