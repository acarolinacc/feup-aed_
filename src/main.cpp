#include <iostream>
#include "Menu.h"
#include "DataManager.h"
#include "RequestManager.h"
int main() {
    DataManager management;
    //Menu menu(management);
    //menu.start();
    management.readStudentClasses();
    management.readClasses();
    management.readClassesPerUC();
    RequestManager requestManager=RequestManager(management);
    Student student=Student(202025232,"Iara");
    student=management.findStudent(student);
    ClassUC classUc=ClassUC("L.EIC013","2LEIC15");
    Request request2=Request(student,classUc,"bila");
   bool a= requestManager.checkIfTheSchedulesOverlap(request2);
    cout << a;



    return 0;}
//testar

