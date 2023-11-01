#include <iostream>
#include "Menu.h"
#include "DataManager.h"
#include "RequestManager.h"
int main() {
    DataManager management;
    Menu menu(management);
    menu.start();




    return 0;}
//testar

