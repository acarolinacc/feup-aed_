#include <iostream>
#include "DataManager.h"
#include "ClassUC.h"


set<Student> DataManager::getStudents() {
    return students;
}

void DataManager::readStudentClasses(){
    ifstream file("../data/students_classes.csv");
    if (!file.is_open()) {
        cout << "erro a abrir fichiro"<< endl;
        return;
    }
    string line;
    string value;
    vector<string> values;
    string studentName; string studentCode;
    getline(file,line);//the first line is not important
    while (getline(file,line)){
        values.clear();
        istringstream iss(line);
        while (getline(iss,value,',')){    //values[0]-studentiD,value[1]-StudentName,value[2]-ucCode,value[3]-classCode
            values.push_back(value);
        }
        if (values.size() >= 4) {
            //adicionar os valores a um student e depois adicionar os students ao set de the estudantes

            int sCode = stoi(values[0]);
            Student student = Student(sCode, values[1]);
            ClassUC classUcRead=ClassUC(values[2],values[3]);
            auto it = students.find(student);
            if (it != students.end()) {
                Student alterStudent = *it;
                students.erase(it);
                alterStudent.addClassUC(classUcRead);
                students.insert(alterStudent);}
            else {
                student.addClassUC(classUcRead);
                students.insert(student);

            }

        }
    }
    file.close();
}

const vector<ClassUC> &DataManager::getAllUC() const {
    return allUC_;
}

void DataManager::readClasses() {

    string fname = "../data/classes.csv";
    ifstream file(fname);

    string line = "";
    string str = "";
    string previousUC = ""; //compares current uc code with the last one
    vector<string> temp;


    if (file.is_open()) {
        getline(file, line); //skip the first line, since is useless in this context
        while (getline(file, line)) {
            temp.clear();
            istringstream iss(line);

            while (getline(iss, str, ',')) {
                temp.push_back(str);
            }


            string classCode = temp[0];
            string ucCode = temp[1];
            string day = temp[2];
            string start = temp[3];
            string duration = temp[4];
            string type = temp[5];
            Slot slot (day, stof(start), stof(duration), type);



            if (ucCode != previousUC) {

                allUC_.push_back(ClassUC(ucCode,classCode,{slot}));

            } else {
                bool ucAlreadyIn = false;
                for (ClassUC& uc: allUC_) {
                    if (classCode == uc.getClassCode() && ucCode == uc.getUcCode()) {
                        uc.addSlot(slot);
                        ucAlreadyIn = true;
                    }
                }
                if (!ucAlreadyIn) { allUC_.push_back(ClassUC(ucCode, classCode, {slot})); }

            }

            previousUC=ucCode;
        }

    }
    else {cout << "Didn't manage to open classes.csv." << endl; }


}

void DataManager::readClassesPerUC() {
    ifstream file("../data/classes_per_uc.csv");
    string line;
    string value;

    while (getline(file, line)) {
        istringstream iss(line);
        vector<string> values;

        while (getline(iss, value, ',')) {
            values.push_back(value);
        }

        if (values.size() == 2) {
            string ucCode = values[0];
            string classCode = values[1];
        }
    }
}

//erro ao alterar o estudante


void DataManager::addStudent(const Student& student) {
    students.insert(student);
}

void DataManager::addClassUC(const ClassUC& classUC) {
    allUC_.push_back(classUC);
}


vector<Student> DataManager::UCstudents(const string& ucId) const {//iterar pela classes dos estudantes e por no vetor as classes que tem id
    vector<Student> studentUC;
    auto it=students.begin();
    while(it!=students.end()){
        int size_class=it->getclassUC().size();
        for(int i=0;i<size_class;i++){
            if(it->getclassUC()[i].getUcCode()==ucId){
                studentUC.push_back(*it); //caso o estudante esteja inscrito nesta uc adiciona o estudante no vector da uc;
            }
        }
        it++;
    }
    return studentUC;
}

vector<ClassUC> DataManager::classOfUc(const string& ucId)const{//iterate throw allUc and get only the ucClasses with ucID;
    vector<ClassUC> uc_classes;
    for (const auto& classUc:allUC_){
        if(classUc.getUcCode()==ucId) {
            uc_classes.push_back(classUc);
        }
    }
    return uc_classes;
}

int DataManager::numberStudentsUc(const string& ucId)const{
    vector<Student> studentUC= UCstudents(ucId);
    return  studentUC.size();
}
bool DataManager::sorterOccupation(const ClassUC& a, const ClassUC& b) const{
    const string& Acode=a.getUcCode();
    const string& Bcode=b.getUcCode();
    return (numberStudentsUc(Acode)> numberStudentsUc(Bcode));
}


vector<ClassUC> DataManager::classuC_x_year(char year)const{
    vector<ClassUC> uc_classes;
    for (const auto& classUc:allUC_){
        string classCode=classUc.getClassCode();
        char year_read=classCode[0];
        if(year_read==year) {
            uc_classes.push_back(classUc);
        }
    }
    return uc_classes;
}

vector<ClassUC> DataManager::ucWithXStudents(int x){
    vector<ClassUC> sorted_alluc=sortAllU();
    vector<ClassUC> uc_classes;
    string prev=" ";
    for (const auto& classUc:allUC_){
        if(numberStudentsUc(classUc.getUcCode())==x and prev!=classUc.getUcCode() ) {
            uc_classes.push_back(classUc);
        }
        prev=classUc.getUcCode();

    }
    return uc_classes;
}







vector<ClassUC> DataManager::sortAllU_occupation(){
    vector<ClassUC> sortedAlluc=allUC_;
    DataManager dataManager;
    sort(sortedAlluc.begin(), sortedAlluc.end(), [&dataManager](const ClassUC& a, const ClassUC& b) {return dataManager.sorterOccupation(a, b);});
    return sortedAlluc;
}

bool DataManager::sorter(const ClassUC& a, const ClassUC& b){
    char yearA=a.getClassCode()[0];
    char yearB=b.getClassCode()[0];
    const string& Acode=a.getUcCode();
    const string& Bcode=b.getUcCode();
    if(yearA!=yearB){
        return yearA<yearB;
    }
    if(a.getUcCode()!=b.getUcCode()){
        return a.getUcCode()<b.getUcCode();
    }
    return (UCstudents(Acode).size()< UCstudents(Bcode).size());
}


vector<ClassUC> DataManager::sortAllU(){
    vector<ClassUC> sortedAlluc=allUC_;
    DataManager dataManager;
    sort(sortedAlluc.begin(), sortedAlluc.end(), [&dataManager](const ClassUC& a, const ClassUC& b) {return dataManager.sorter(a, b);});//I used the lamda funtion to call the sorter which is a method of class Datamanager;
    return  sortedAlluc;
}


int DataManager::studentregisterUCs(int n) {
    int count2 = 0;
    for (const auto&  student : students) {
        int count = 0;
        for (auto c : student.getclassUC()){
            count++;
        }
        if(count >= n){
            count2++;
        }
    }
    return count2;
}

vector<Student> DataManager::studentsOfClassUc(const ClassUC&  classUc){
    vector<Student> students_class;
    auto it=students.begin();
    while(it!=students.end()) {
        int size_class = it->getclassUC().size();
        for (int i = 0; i < size_class; i++) {
            if (it->getclassUC()[i].getUcCode() == classUc.getUcCode() and it->getclassUC()[i].getClassCode() == classUc.getClassCode()) {
                students_class.push_back(*it);
            }

        }
        it++;
    }
    return students_class;

}

vector<Slot> DataManager::getClassUCSchedule(const ClassUC& classUc2) {
    vector<Slot> schedule;
    for (auto uc : allUC_) {
        if(uc.getClassCode()==classUc2.getClassCode() and uc.getUcCode()==classUc2.getUcCode()){
            schedule = uc.getSchedule();
        }
    }
    return schedule;
}

vector<Slot> DataManager::getUcSchedule(const string &UcId) {
    vector<Slot> schedule;
    for (const ClassUC& uc : allUC_) {
        if(uc.getUcCode()==UcId){
            for(auto slot:uc.getSchedule())
                schedule.push_back(slot);
        }
    }
    return schedule;
}

vector<Slot> DataManager::getClassSchedule(const string& classCode) {
    vector<Slot> schedule;
    for (const ClassUC& uc : allUC_) {
        if(uc.getClassCode()==classCode){
            for(auto slot:uc.getSchedule())
                schedule.push_back(slot);
        }
    }
    return schedule;
}

Student DataManager::getStudentSchedule(const Student& student) {
    auto it=students.find(student);
    Student wanted;
    if(it==students.end()){
        cout<<"student not found"<<endl;}
    else{
       wanted=*it;
    }
    for(auto i: wanted.getclassUC()){
        vector<Slot> slots= getClassUCSchedule(i);

        wanted.addSchedule(i,slots);
    }
    return wanted;
}

Student DataManager::findStudent(const Student& student) {//with a name and the up code,get the classes of the student
    auto  it=students.find(student);
    return *it;
}

bool DataManager::classUcHaveLessThenXStudents(const ClassUC& classUc, int x) {
    auto it=students.begin();
    int c=0;
    while (it!=students.end()){
        for(const ClassUC& i:it->getclassUC()){
            if(classUc.getUcCode()==i.getUcCode() and classUc.getClassCode()==i.getClassCode()){
                c++;
            }
        }
        it++;
        if (c >= x) {
            return false;}
    }
    return c<x;
}


bool DataManager::ingressarEmUC(const string& upNumber, const string& ucCode) {
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

Student DataManager::getStudentByUP(const string& upNumber) {
    for (const Student& student : students) {
        if (student.getCode() == stoi(upNumber)) {
            return student;
        }
    }

    return Student(0, "");
}


ClassUC DataManager::getClassUCByCode(const string& ucCode) {
    for (const ClassUC& uc : allUC_) {
        if (uc.getUcCode() == ucCode) {
            return uc;
        }
    }

    return ClassUC();
}
bool DataManager::haveScheduleConflict(const ClassUC& studentClass, const ClassUC& newClass) const {
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

bool DataManager::sairDeUC(const string& upNumber, const string& ucCode) {
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