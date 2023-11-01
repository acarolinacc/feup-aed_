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

bool RequestManager::checkClassRequest(const Request &request) {
    if(checkOneClassUcPerStudent(request) and !checkIfTheSchedulesOverlap(request) and checkIfBalanceOcuppation(request) and
       checkIfTheCapIsExceeded(request)){return true;}
    return false;
}

void RequestManager::setManager(DataManager manager) {
    this->manager=manager;

}

RequestManager::RequestManager() = default;

const vector<ClassUC> &RequestManager::getAllUC() const {
    return allUC_;
}

set<Student> RequestManager::getStudents() {
    return students;
}

bool RequestManager::ingressarEmUC(const string& upNumber, const string& ucCode) {
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
    student.addClassUC(uc);
    //uc.addStudent(student);
    return true;
}

Student RequestManager::getStudentByUP(const string& upNumber) {
    for (const Student& student : students) {
        if (student.getCode() == stoi(upNumber)) {
            return student;
        }
    }

    return Student(0, "");
}


ClassUC RequestManager::getClassUCByCode(const string& ucCode) {
    for (const ClassUC& uc : allUC_) {
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

bool RequestManager::sairDeUC(const string& upNumber, const string& ucCode) {
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
    auto it = find(studentClasses.begin(), studentClasses.end(), uc);
    if (it == studentClasses.end()) {
        cout << "O estudante não está inscrito na UC " << ucCode << ". Não é possível sair." << endl;
        return false;
    }

    // Remover a UC da lista de UCs do estudante

    // Remover o estudante da lista de alunos da UC


    cout << "O estudante " << student.getName() << " saiu com sucesso da UC " << ucCode << "." << endl;
    return true;
}
