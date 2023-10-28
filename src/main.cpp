#include <iostream>
#include "Menu.h"
#include "DataManager.h"

int main() {
    DataManager management;
    Menu menu(management);
    menu.start();


    /*
    vector<Student> estudantes=management.StudentsOfClassUc("L.EIC001","1LEIC05");
    for(auto student:estudantes){
        cout << student.getName() << "|" << student.getCode() <<endl;
    }
    */
    return 0;}