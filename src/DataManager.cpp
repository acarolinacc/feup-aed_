#include <iostream>
#include "DataManager.h"
#include "ClassUC.h"


set<Student> DataManager::getStudents() const{
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
            Slot slot (day, start, duration, type);



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
    string Acode=a.getUcCode();
    string Bcode=b.getUcCode();
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
    for (auto  student : students) {
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

vector<Student> DataManager::StudentsOfClassUc(const string& uc_id,const string& class_id){
    vector<Student> students_class;
    auto it=students.begin();
    while(it!=students.end()) {
        int size_class = it->getclassUC().size();
        for (int i = 0; i < size_class; i++) {
            if (it->getclassUC()[i].getUcCode() == uc_id and it->getclassUC()[i].getClassCode() == class_id) {
                students_class.push_back(*it);
            }

        }
        it++;
    }
    return students_class;

}

