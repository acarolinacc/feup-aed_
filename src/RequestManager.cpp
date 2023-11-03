#include "RequestManager.h"


RequestManager::RequestManager(DataManager &manager) {
    this->manager=manager;

}

void RequestManager::addResquest(const Request& newRequest) {
    requests.push(newRequest);
}

queue<Request> RequestManager::getRequest() const {
    return requests;
}

void RequestManager::addDinedRequest(const Request &newRequest) {
    deniedRequest.push(newRequest);
}

void RequestManager::addAcceptRequest(const Request &newRequest) {
    acceptRequest.push(newRequest);
}




bool classUCSorter(const ClassUC& a,const ClassUC& b){
    return  a.getClassCode()<b.getClassCode();
}
vector<ClassUC> classUCsort(const Student& student){
    vector<ClassUC>result=student.getclassUC();
    sort(result.begin(),result.end(),  classUCSorter);
    return result;

}


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

bool RequestManager::checkIfTheCapIsExceeded(const Request &request) {
    ClassUC classUc=request.getClassUc();
    bool  result= manager.classUcHaveLessThenXStudents(classUc, CAP);
    return result;
}

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




bool RequestManager::checkIfTheSchedulesOverlap(const Request& request) {
    ClassUC requestclass=request.getClassUc();
    Student requestStudent=request.getStudent();
    if(requestStudent.getSchedule().empty()){requestStudent=manager.findStudent(requestStudent);}//i dont think is need but is to make sure that this student have classes;
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
bool RequestManager::checkClassStudent(const Request &request) {//check if the student have the class that he want to leave
    vector<ClassUC> student_classes=request.getStudent().getclassUC();
    for(auto classes:student_classes){
        if(classes==request.getClassUc()){
            return true;
        }
    }
    return false;
}





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

void RequestManager::setManager(DataManager manager) {
    this->manager=manager;

}

RequestManager::RequestManager() = default;



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

Student RequestManager::getStudentByUP(const int &upNumber) {
    for (const Student& student : manager.getStudents()) {
        if (student.getCode() == (upNumber)) {
            return student;
        }
    }

    return Student(0, "");
}


ClassUC RequestManager::getClassUCByCode(const string& ucCode) {
    for (const ClassUC& uc : manager.getAllUC()) {
        if (uc.getUcCode() == ucCode) {
            return uc;
        }
    }

    return ClassUC();
}
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

bool RequestManager::sairDeUC(const int upNumber, const string& ucCode) {//alterar para request
    Student student = getStudentByUP(upNumber);
    if (student.getCode() == 0) {
        cout << "Estudante com UP " << upNumber << " não encontrado." << endl;
        return false;
    }

    ClassUC uc = getClassUCByCode(ucCode);
    if (uc.getUcCode() == "") {
        cout << "UC com código " << ucCode << " não encontrada." << endl;
        return false;
    }

    vector<ClassUC> studentClasses = student.getclassUC();
    for(auto classuc:studentClasses){
        if(classuc.getUcCode()==ucCode){
           return true;
        }
    }
        cout << "O estudante não está inscrito na UC " << ucCode << ". Não é possível sair." << endl;
        return false;
}

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
            cout << "student not found" << endl;
            return false;
        }
    }
    return false;
    }

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
                ClassUC newClassUC = findClassinUc(request.getStudent(),
                                                   uccode);//search for the class that is compatible
                if (newClassUC.getUcCode() == " ") {
                    cout << "class not found" << endl;
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
            cout << "student not found" << endl;
            return false;
        }
    }
    return false;
}


void RequestManager::requestProcess(DataManager &newManager,bool action) {//if the action is true the requestProcess,will process normal requests,if its true it will process undo requests
    queue<Request> requests_action;
    if(action){
        requests_action=requests;
    }
    else{
        requests_action=undoneRequests;
    }
    while (!requests_action.empty()) {
        Request actual_request = requests_action.front();
        if(actual_request.getType()[1]=='U') {//UC request;
            if(changeUC(actual_request,newManager)){
                addAcceptRequest(actual_request);
            }
            else{
                addDinedRequest(actual_request);
                cout <<"Request was dined,Request info:"<<endl;
                actual_request.printRequest();
            }
        }
        else if(actual_request.getType()[1]=='C'){//Class request;
            if(changeCLass(actual_request,newManager)){
                addAcceptRequest(actual_request);
            }
            else{
                addDinedRequest(actual_request);
                cout <<"Request was dined,Request info:"<<endl;
                actual_request.printRequest();
            }
    }
        else{//request need to be dined;
            addDinedRequest(actual_request);
            cout <<"Request was dined,Request info:"<<endl;
            actual_request.printRequest();
        }
        requests_action.pop();//pop the request readed

    }
    if(action){
        requests=requests_action;
    }
    else{
        undoneRequests=requests_action;
    }
}




void RequestManager::processUndoRequest(DataManager &newManager) {
    undoRequest();
    requestProcess(newManager, false);
}



void  RequestManager::undoRequest(){
    while (!acceptRequest.empty()){
        Request lastAcceptedRequest = acceptRequest.front();
        if(lastAcceptedRequest.getType()[1]=='U'){
            undorequestUC(lastAcceptedRequest);


        }
        else if(lastAcceptedRequest.getType()[1]=='C'){
            undorequestClass(lastAcceptedRequest);

        }
        else{//if the undo request is not accepted

            deniedRequest.push(lastAcceptedRequest);
        }
        acceptRequest.pop();
    }
}


bool RequestManager::undorequestUC(Request ucResquest) {
    if (ucResquest.getType() == "E") {
        ucResquest.setType("SU");
        if (sairDeUC(ucResquest.getStudent().getCode(), ucResquest.getClassUc().getUcCode())) {
            undoneRequests.push(ucResquest);

            return true;
        }
    }
    else if (ucResquest.getType() == "S") {
        ucResquest.setType("EU");
        if (ingressarEmUC(ucResquest.getStudent().getCode(), ucResquest.getClassUc().getUcCode())) {
            undoneRequests.push(ucResquest);

            return true;
        }
    }

    return false;
}

bool RequestManager::undorequestClass(Request classResquest){
    if(classResquest.getType()[0]=='E'){
        classResquest.setType("SC");
    }
    else if(classResquest.getType()[0]=='S'){
        classResquest.setType("EC");
    }
    if(checkClassRequest(classResquest)){
        undoneRequests.push(classResquest);
        return true;
    }
    return false;
}

void RequestManager::restore(const Request &request) {
    if (request.getType() == "E") {
        if (!undoneRequests.empty() && undoneRequests.front() == request) {
            Request undoneRequest = undoneRequests.front();
            sairDeUC(undoneRequest.getStudent().getCode(), undoneRequest.getClassUc().getUcCode());
            undoneRequests.pop();
        }
    } else if (request.getType() == "S") {

        if (!undoneRequests.empty() && undoneRequests.front() == request) {
            Request undoneRequest = undoneRequests.front();
            ingressarEmUC(undoneRequest.getStudent().getCode(), undoneRequest.getClassUc().getUcCode());
            undoneRequests.pop();
        }
    }
}
