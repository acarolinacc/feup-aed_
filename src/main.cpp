#include <iostream>
#include "Menu.h"
#include "DataManager.h"
#include "RequestManager.h"
int main() {
    DataManager management;
    //Menu menu(management);
    //menu.start();
    management.readClasses();
    management.readStudentClasses();
    management.readClassesPerUC();
    RequestManager requestManager(management);
    requestManager.setManager(management);
    Student student=Student(202029142,"Liliana");
    student=management.findStudent(student);
    ClassUC classUc=ClassUC("L.EIC003","1LEIC15");
    Request request=Request(student,classUc,"EC");
    cout << requestManager.checkIfBalanceOcuppation(request);




    return 0;}
//testar

