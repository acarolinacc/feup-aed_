#include <iostream>
#include "Menu.h"
#include "DataManager.h"
#include "RequestManager.h"
int main() {
    DataManager management;//CLASS "L.EIC013","2LEIC07" tem balance direito,202023362,"Carminho"
    Menu menu(management);
    menu.start();


    return 0;}
//testar

