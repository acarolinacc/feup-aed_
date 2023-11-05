#include "RequestManager.h"

/**
 * @brief this function constructs a RequestManager with the given DataManager
 *
 * @param manager A reference to the DataManager
 *
 * Time complexity O(1)
 */
RequestManager::RequestManager(DataManager &manager) {
    this->manager=manager;

}

/**
 * @brief this function adds a new request to the queue of requests
 *
 * @param newRequest The new request to be added
 *
 * Time complexity O(1)
 */
void RequestManager::addResquest(const Request& newRequest) {
    requests.push(newRequest);
}

/**
 * @brief this function gets the queue of requests
 *
 * @return A copy of the queue of requests
 *
 * Time complexity O(n), where 'n' is the number of elements in the queue
 */
queue<Request> RequestManager::getRequest() const {
    return requests;
}

/**
 * @brief this function adds a denied request to the queue of denied requests
 *
 * @param newRequest The denied request to be added
 *
 * Time complexity O(1)
 */
void RequestManager::addDinedRequest(const Request &newRequest) {
    deniedRequest.push(newRequest);
}

/**
 * @brief this function adds an accepted request to the queue of accepted requests
 *
 * @param newRequest The accepted request to be added
 *
 * Time complexity O(1)
 */
void RequestManager::addAcceptRequest(const Request &newRequest) {
    acceptRequest.push(newRequest);
}



/**
 * @brief Comparator function to sort ClassUC objects by their class code
 *
 * @param a The first ClassUC object
 *
 * @param b The second ClassUC object
 *
 * @return True if a should come before b in the sorted order, false otherwise
 *
 * Time complexity O(nlog(n)), where 'n' is the number of elements in the vector
 */
bool classUCSorter(const ClassUC& a,const ClassUC& b){
    return  a.getClassCode()<b.getClassCode();
}
vector<ClassUC> classUCsort(const Student& student){
    vector<ClassUC>result=student.getclassUC();
    sort(result.begin(),result.end(),  classUCSorter);
    return result;

}

/**
 * @brief this function checks if a student is already enrolled in another ClassUC with the same UC code
 *
 * @param request The request to be checked
 *
 * @return True if the student is not already enrolled in a ClassUC with the same UC code, false otherwise
 *
 * Time complexity O(n log n), where 'n' is the number of ClassUC objects associated with the student
 */
bool RequestManager::checkOneClassUcPerStudent(const Request& request) {
    Student requestStudent=request.getStudent();
    vector<ClassUC> sortedClassUc= classUCsort(requestStudent);
    ClassUC prevClassUC;
    for(const auto& a:sortedClassUc){
        if(prevClassUC.getUcCode()==a.getUcCode()){
            return false;
        }
        prevClassUC=a;
    }
    return true;

}

/**
 * @brief this function checks if the capacity of a ClassUC is exceeded with the addition of a new student
 *
 * @param request The request to be checked
 *
 * @return True if the capacity is not exceeded, false otherwise
 *
 * Time complexity O(n), where 'n' is the number of students associated with the ClassUC in the request
 */
bool RequestManager::checkIfTheCapIsExceeded(const Request &request) {
    ClassUC classUc=request.getClassUc();
    bool  result= manager.classUcHaveLessThenXStudents(classUc, CAP);
    return result;
}

/**
 * @brief this function checks if adding or removing a student from a class will maintain balance in class size
 *
 * @param request The request containing information about the class and the student's action (add or remove)
 *
 * @return true if the addition/removal maintains balance, false otherwise
 *
 * Time complexity O(n), where 'n' is the number of classes in the given UC
*/

bool RequestManager::checkIfBalanceOcuppation(const Request &request) {// tested
    int mins=CAP;int maxs=0;
    const int MAXDIFFERENCE=4;
    string type=request.getType();
    vector<ClassUC> allClassOfUc=manager.classOfUc(request.getClassUc().getUcCode());//vector with all classes of a uc;
    for(const ClassUC& classUc:allClassOfUc){
        int size_class=manager.studentsOfClassUc(classUc).size();
        if(classUc.getClassCode()==request.getClassUc().getClassCode()){//we want to check if the addition of the student will cause an imbalance so we need to add the student to the size of the requested_class
            if(type[0]=='S'){size_class--;}//if the student want to left the class the size of the class will decrease
            if(type[0]=='E'){size_class++;}//if the student want to join the class the size of the class will encrease
        }
        if(size_class>maxs){maxs=size_class;}
        if(size_class<mins){mins=size_class;}
    }
    return (maxs-mins)<=MAXDIFFERENCE;
}




/**
 * @brief this function checks if the schedules of a new student overlap with existing schedules of the ClassUC
 *
 * @param request The request to be checked
 *
 * @return True if there is no schedule overlap, false otherwise
 *
 * time complexity of O(n * m * p), where 'n' is the number of days in the student's schedule 'm' is the number of slots per day in the student's schedule 'p' is the number of slots in the ClassUC schedule.
 */
bool RequestManager::checkIfTheSchedulesOverlap(const Request& request) {
    ClassUC requestclass=request.getClassUc();
    Student requestStudent=request.getStudent();
    if(requestStudent.getSchedule().empty()){
        requestStudent=manager.findStudent(requestStudent);//i dont think is need but is to make sure that this student have classes;
    }
    requestStudent=manager.getStudentSchedule(requestStudent);
    vector<Slot> classShedule=manager.getClassUCSchedule(requestclass);
    requestclass=ClassUC(requestclass.getUcCode(),requestclass.getClassCode(),classShedule);
    requestclass.sortShedule();  //sort each slots to be easier to make the overlaping
    for(const auto& mape:requestStudent.getSchedule()){
        for(const auto& slots_Student:mape.second){
            for(const auto& slot_uc:requestclass.getSchedule()){
                if(slots_Student.overlaps(slot_uc)){return true;}
            }
        }
    }
    return false;
}

/**
 * @brief this function checks if the student is enrolled in the class they are trying to leave
 *
 * @param request The request to be checked
 *
 * @return True if the student is enrolled in the class, false otherwise
 *
 * Time complexity O(n), where 'n' represents the number of ClassUC
 */
bool RequestManager::checkClassStudent(const Request &request) {//check if the student have the class that he want to leave
    vector<ClassUC> student_classes=request.getStudent().getclassUC();
    for(auto classes:student_classes){
        if(classes==request.getClassUc()){
            return true;
        }
    }
    return false;
}

/**
 * @brief this function checks the validity of a Class or UC request
 *
 * @param request The request to be checked
 *
 * @return True if the request is valid, false otherwise
 *
 * Time complexity O(n), where 'n' is the number of schedules being checked for overlaps
 */

bool RequestManager::checkClassRequest(const Request &request) {
    if(request.getType()[0]=='E') {
        if (checkOneClassUcPerStudent(request) and !checkIfTheSchedulesOverlap(request) and
            checkIfBalanceOcuppation(request) and
            checkIfTheCapIsExceeded(request)) {
            return true;
        }
    }
    else if(request.getType()[0]=='S'){//when is a exit request is just needed to check if the student is the in the class,that he want to leave:

        if(checkClassStudent(request) and checkIfBalanceOcuppation(request)){
            return true;
        }

    }
    return false;
}

/**
 * @brief Set the Data Manager for the RequestManager
 *
 * @param manager The Data Manager to be set
 *
 * Time complexity O(1)
 */
void RequestManager::setManager(DataManager manager) {
    this->manager=manager;

}


/**
 * @brief Default constructor for RequestManager.
 */
RequestManager::RequestManager() = default;

/**
 * @brief this function handles a request to join or leave a UC
 *
 * @param upNumber The UP number of the student
 *
 * @param ucCode The code of the UC
 *
 * @return True if the request was successful, false otherwise
 *
 * Time complexity O(n * m), where 'n' is the number of UCs associated with the student, and 'm' is the average number of schedules within each of these UCs
 */

bool RequestManager::ingressarEmUC(const int &upNumber, const string& ucCode) {//alterar para request
    Student student = getStudentByUP(upNumber);
    if (student.getCode() == 0) {
        cout << "Estudante com UP " << upNumber << " não encontrado." << endl;
        return false;
    }

    // Verificar se o aluno já está inscrito em 7 UCs
    if (student.getclassUC().size() >= 7) {
        cout << "O estudante já está inscrito em 7 UCs. Não é possível ingressar em mais." << endl;
        return false;
    }

    // Obter a UC com base no id fornecido
    ClassUC uc = getClassUCByCode(ucCode);
    if (uc.getUcCode() == "") {
        cout << "UC com código " << ucCode << " não encontrada." << endl;
        return false;
    }

    // Verificar se há vagas disponíveis na UC

    // Verificar se há conflitos de horário
    vector<ClassUC> studentClasses = student.getclassUC();
    for (const ClassUC& studentClass : studentClasses) {
        if (haveScheduleConflict(studentClass, uc)) {
            cout << "Conflito de horário entre a UC " << studentClass.getUcCode() << " e a UC " << ucCode << ". Não é possível ingressar." << endl;
            return false;
        }
    }

    // Tudo está em ordem, ingressar na UC
    //uc.addStudent(student);
    return true;
}

/**
 * @brief this function retrieves a student based on their UP number
 *
 * @param upNumber The UP number of the student
 *
 * @return The student with the given UP number
 *
 * Time complexity O(n), where 'n' is the number of students
 */
Student RequestManager::getStudentByUP(const int &upNumber) {
    for (const Student& student : manager.getStudents()) {
        if (student.getCode() == (upNumber)) {
            return student;
        }
    }

    return Student(0, "");
}

/**
 * @brief this function retrieves a ClassUC object based on its code
 *
 * @param ucCode The code of the UC
 *
 * @return The ClassUC object with the given code
 *
 * Time complexity O(n), where 'n' is the number of ClassUC objects
 */

ClassUC RequestManager::getClassUCByCode(const string& ucCode) {
    for (const ClassUC& uc : manager.getAllUC()) {
        if (uc.getUcCode() == ucCode) {
            return uc;
        }
    }

    return ClassUC();
}


/**
 * @brief this function checks if there is a schedule conflict between two classes
 *
 * @param studentClass The class of the student
 *
 * @param newClass The new class to be checked for conflict
 *
 * @return True if there is a schedule conflict, false otherwise
 *
 * Time Complexity O(n*m), where 'n' is the number of slots in studentClass and 'm' is the number of slots in newClass
 */
bool RequestManager::haveScheduleConflict(const ClassUC& studentClass, const ClassUC& newClass) const {
    if (studentClass.getUcCode() == newClass.getUcCode()) {
        return false;
    }

    // horário do estudante
    vector<Slot> studentClassSchedule = studentClass.getSchedule();

    // horário da nova UC
    vector<Slot> newClassSchedule = newClass.getSchedule();

    // verificar se há algum conflito de horário entre as turmas
    for (const Slot& studentSlot : studentClassSchedule) {
        for (const Slot& newSlot : newClassSchedule) {
            // verificar se os dias da semana e horas são iguais
            if (studentSlot.getDay() == newSlot.getDay() && studentSlot.getStart() == newSlot.getStart()) {
                // se ambos os tipos de aula forem TP, há um conflito
                if (studentSlot.getType() == "TP" && newSlot.getType() == "TP") {
                    return true;
                }
                return false;
            }
        }
    }

    return false;
}


/**
 * @brief this function checks if a student can leave a specific UC
 *
 * @param upNumber The UP number of the student
 *
 * @param ucCode The code of the UC to check
 *
 * @return True if the student can leave the UC, false otherwise
 *
 * Time Complexity O(n), where 'n' is the number of UCs the student is enrolled in
 */
bool RequestManager::sairDeUC(const int upNumber, const string& ucCode) {//alterar para request
    Student student = getStudentByUP(upNumber);
    if (student.getCode() == 0) {
        cout << "Estudante com UP " << upNumber << " não encontrado." << endl;
        return false;
    }

    ClassUC uc = getClassUCByCode(ucCode);
    if (uc.getUcCode().empty()) {
        cout << "UC com código " << ucCode << " não encontrada." << endl;
        return false;
    }

    vector<ClassUC> studentClasses = student.getclassUC();
    for(const ClassUC& classuc:studentClasses){
        if(classuc.getUcCode()==ucCode){
           return true;
        }
    }
        cout << "O estudante não está inscrito na UC " << ucCode << ". Não é possível sair." << endl;
        return false;
}

/**
 * @brief this function processes UC-related requests
 *
 * @param request The request to be processed
 *
 * @return True if the request was successful, false otherwise
 *
 * Time Complexity O(n) where 'n' is the number of UCs the student is enrolled in
 */
bool RequestManager::UcProcess(const Request& request) {
    char type_c=request.getType()[0];
    int upNumber=request.getStudent().getCode();
    string UcNumber=request.getClassUc().getUcCode();
    if(type_c=='S'){
        return sairDeUC(upNumber,UcNumber);
    }
    else if(type_c=='E'){
        return ingressarEmUC(upNumber,UcNumber);
    }
    return false;
}

/**
 * @brief this function Changes the class of a student based on a request
 *
 * @param request The request for class change
 *
 * @param newManager The DataManager to be updated with the changes
 *
 * @return True if the class change was successful, false otherwise
 *
 * Time Complexity O(N) where N is the number of UCs the student is enrolled in
 */

bool RequestManager::changeCLass(const Request& request,DataManager &newManager) {//if the request was accepted,the class need to be change
    if(checkClassRequest(request)) {//check if the request is valid
        set<Student> students = manager.getStudents();
        auto it = students.find(request.getStudent());
        if (it != students.end()) {
            Student copyStudent = *it;
            if (request.getType()[0] == 'S') {//we need to remove the request class in the classes of the student
                vector<ClassUC> studentClasses=copyStudent.getclassUC();
                for (auto d =studentClasses.begin(); d !=studentClasses.end();) {
                    if (request.getClassUc() == *d) {
                        studentClasses.erase(d);
                        copyStudent.setCLassUc(studentClasses);
                        break;
                    } else { d++; }
                }
            } else if (request.getType()[0] == 'E') {
                copyStudent.addClassUC(request.getClassUc());//Add the new clas uc
            }
            students.erase(it);
            students.insert(copyStudent);       //i need to remove the student and then add it again
            manager.setStudents(students);
            newManager=manager;
            return true;
        } else {
            cout << "Estudante nao encontrado" << endl;
            return false;
        }
    }
    return false;
    }


/**
 * @brief this function finds a compatible class for the student in a UC
 *
 * @param student The student for whom a class needs to be found
 *
 * @param ucCode The code of the UC to find a compatible class in
 *
 * @return The compatible class if found, an empty ClassUC otherwise
 *
 * Time Complexity: O(n), where 'n' is the number of classes in the specified UC
 */
ClassUC RequestManager::findClassinUc(Student student, const string &ucCode) {
    ClassUC  notFound;
    vector<ClassUC> classOfUc=manager.classOfUc(ucCode);
    for(auto classUc:classOfUc){
        Request classRequest=Request(student,classUc,"EC");
        if(checkClassRequest(classRequest)){
            return  classUc;
        }
    }
    return notFound;
}

/**
 * @brief this function Processes UC-related requests and change the student's UC enrollment
 *
 * @param request The request to be processed
 *
 * @param newManager The DataManager to be updated with the changes
 *
 * @return True if the request was successfully processed, false otherwise
 *
 * Time Complexity O(n), where 'n' is the number of UCs
 */
bool RequestManager::changeUC(const Request &request,DataManager &newManager) {//non tested
    if(UcProcess(request)) { //check if the request is valid
        set<Student> students = manager.getStudents();
        string uccode = request.getClassUc().getUcCode();
        auto it = students.find(request.getStudent());
        if (it != students.end()) {
            Student copyStudent = *it;
            if (request.getType()[0] == 'S') {//we need to remove the request class in the classes of the student
                vector<ClassUC> classes=copyStudent.getclassUC();
                for (auto d = classes.begin(); d != it->getclassUC().end();) {
                    if (uccode == d->getUcCode()) {
                        classes.erase(d);
                        copyStudent.setCLassUc(classes);
                        break;
                    } else { d++; }
                }
            } else if (request.getType()[0] == 'E') {
                ClassUC newClassUC = findClassinUc(request.getStudent(),uccode);//search for the class that is compatible
                if (newClassUC.getUcCode().empty()) {
                    cout << "Turma não encontrada" << endl;
                    return false;
                } else {
                    copyStudent.addClassUC(newClassUC);
                }
            }
            students.erase(it);
            students.insert(copyStudent);       //i need to remove the student and then add it again
            manager.setStudents(students);
            newManager=manager;
            return true;
        } else {
            cout << "Estudante nao encontrado" << endl;
            return false;
        }
    }
    return false;
}

/**
 * @brief this function Processes and handle requests by changing the student's UC enrollment and classes.
 *
 * @param newManager The DataManager to be updated with the changes.
 *
 * Time Complexity O(n), where 'n' is the number of pending requests in the queue
 */
void RequestManager::requestProcess(DataManager &newManager) {//if the action is true the requestProcess,will process normal requests,if its true it will process undo requests

    while (!requests.empty()) {
        Request actual_request = requests.front();
        if (actual_request.getType()[1] == 'U') {//UC request;
            if (changeUC(actual_request, newManager)) {
                addAcceptRequest(actual_request);
            }
            else {
                addDinedRequest(actual_request);
                cout << "Pedido foi negado, informação do pedido:" << endl;
                actual_request.printRequest();
            }
        }
        else if(actual_request.getType()[1] == 'C') {//Class request;
            if (changeCLass(actual_request, newManager)) {
                addAcceptRequest(actual_request);
            } else {
                addDinedRequest(actual_request);
                cout << "Pedido foi negado, informação do pedido:" << endl;
                actual_request.printRequest();
            }
        }
        else {//request need to be dined;
            addDinedRequest(actual_request);
            cout << "Pedido foi negado, informação do pedido:" << endl;
            actual_request.printRequest();
        }
        requests.pop();//pop the request readed

    }
}

/**
 * @brief this function Processes and handle undo requests by reverting previous changes to UC enrollment and classes.
 *
 * @param newManager The DataManager to be updated with the changes.
 *
 * Time Complexity: O(n), where 'n' is the number of undo requests in the queue.
 */
void RequestManager::processUndoRequest(DataManager &newManager) {
    while (!acceptRequest.empty()){
        Request lastAcceptedRequest = acceptRequest.front();
        if(lastAcceptedRequest.getType()[1]=='U'){
            undorequestUC(lastAcceptedRequest,newManager);

        }
        else if(lastAcceptedRequest.getType()[1]=='C'){
            undorequestClass(lastAcceptedRequest,newManager);

        }
        else{//if the undo request is not accepted

            deniedRequest.push(lastAcceptedRequest);
        }
        acceptRequest.pop();
    }
}



/**
 * @brief this function reverts changes made by a UC-related request
 *
 * @param ucRequest The UC-related request to be undone
 *
 * @param newManager The DataManager to be updated with the changes
 *
 * Time Complexity: O(n), where 'n' is the number of UCs the student is enrolled in
 */
void RequestManager::undorequestUC(const Request& ucResquest,DataManager& newmanager) {
    set<Student> students=manager.getStudents();
    auto it = students.find(ucResquest.getStudent());
    Student copyStudent=*it;
    vector<ClassUC>classes=ucResquest.getStudent().getclassUC();
    string uccode = ucResquest.getClassUc().getUcCode();
    if (ucResquest.getType()[0] == 'E') {//sair da uc que entrou
        for (auto d = classes.begin(); d != it->getclassUC().end();) {
            if (uccode == d->getUcCode()) {
                classes.erase(d);
                copyStudent.setCLassUc(classes);
                break;
            } else { d++; }
        }
    }
    else if (ucResquest.getType()[0] == 'S') {
        copyStudent.addClassUC(ucResquest.getClassUc());
    }
    students.erase(it);
    students.insert(copyStudent);       //i need to remove the student and then add it again
    manager.setStudents(students);
    newmanager=manager;
}

/**
 * @brief this function reverts changes made by a class-related request
 *
 * @param classRequest The class-related request to be undone
 *
 * @param newManager The DataManager to be updated with the changes
 *
 * Time Complexity O(n), where 'n' is the number of classes the student is enrolled in
 */
void  RequestManager::undorequestClass(const Request& classResquest,DataManager &newManager){
    set<Student> students = manager.getStudents();
    auto it = students.find(classResquest.getStudent());
    Student copyStudent=*it;
    if(classResquest.getType()[0]=='E') {//neeed exit the class
        vector<ClassUC> studentClasses = copyStudent.getclassUC();
        for (auto d = studentClasses.begin(); d != studentClasses.end();) {
            if (classResquest.getClassUc() == *d) {
                studentClasses.erase(d);
                copyStudent.setCLassUc(studentClasses);
                break;
            } else { d++; }
        }
    }
    else if(classResquest.getType()[0]=='S'){
            copyStudent.addClassUC(classResquest.getClassUc());
    }
    students.erase(it);
    students.insert(copyStudent);       //i need to remove the student and then add it again
    manager.setStudents(students);
    newManager=manager;

}

/**
 * @brief this function displays information about all requests, accepted and denied, and undone requests
 *
 * Time Complexity: O(n), where 'n' is the number of requests and undo requests
 */
void RequestManager::showAllChanges() {

        showUndo();
        showrequests();
        showAccept();
        showDinie();

}

/**
 * @brief this function display information about undone requests
 *
 * @return The number of undone requests
 *
 * Time Complexity O(n), where 'n' is the number of undone requests
 */
int RequestManager::showUndo() {
    int c=0;
    queue<Request>undorequests=undoneRequests;
    while (!undorequests.empty()){

        cout<< "Pedidos que foram desfeitos"<<endl;

        cout<< "Pedidos que foram cancelados"<<endl;
        undorequests.front().printRequest();
        undorequests.pop();
        c++;
    }
    if(c==0){
        cout<<"Nao ha pedidos cancelados"<<endl;
    }
    return c;
}
/**
 * @brief this function display information about pending requests
 *
 * @return The number of pending requests
 *
 * Time Complexity: O(n), where 'n' is the number of pending requests.
 */

int RequestManager::showrequests() {
    int c=0;
    queue<Request>copyRequests=requests;
    while (!copyRequests.empty()){
        cout<< "Pedidos não processados"<<endl;
        cout<< "Pedidos para serem processados"<<endl;
        copyRequests.front().printRequest();
        copyRequests.pop();
        c++;
    }
    if(c==0){
        cout<<"Não ha pedidos para serem processados"<<endl;}
    return c;
}

/**
 * @brief this function displays information about accepted requests
 *
 * @return The number of accepted requests
 *
 * Time Complexity: O(n), where 'n' is the number of accepted requests
 *
 */

int RequestManager::showAccept() {
    int c=0;
    queue<Request>copyAccept=acceptRequest;
    while (!copyAccept.empty()){
        cout<< "Pedidos aceites"<<endl;
        copyAccept.front().printRequest();
        copyAccept.pop();
        c++;
    }
    if(c==0){
        cout<<"Não ha pedidos aceites"<<endl;}


    return c;
}

/**
 * @brief this function displays information about denied requests.
 *
 * @return The number of denied requests.
 *
 * Time Complexity: O(n), where 'n' is the number of denied requests.
 */
int RequestManager::showDinie() {
    int c=0;
    queue<Request>copydinied=deniedRequest;
    while (!copydinied.empty()){
        cout<< "Pedidos negados"<<endl;
        cout<< "Pedidos rejeitados"<<endl;
        copydinied.front().printRequest();
        copydinied.pop();
        c++;
    }
    if(c==0){
        cout<<"Não ha pedidos rejeitados"<<endl;}

    return c;
}

/**
 * @brief this function writes student information to a file.
 *
 * Time complexity O(n), where 'n' is the number of students in the list
 */

void RequestManager::writeFiles() {
    ofstream  file;
    set<Student> students=manager.getStudents();
    file.open("../data/students_classes.csv");
    file << "StudentCode,StudentName,UcCode,ClassCode" << endl;
    auto it=students.begin();
    while (it!=students.end()){
        for(const ClassUC& classes:it->getclassUC()){
            file << it->getCode() << "," << it->getName() << "," << classes.getUcCode() << "," << classes.getClassCode() << endl;
        }
        it++;
    }

}


