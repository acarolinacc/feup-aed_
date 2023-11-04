#include <iostream>
#include "DataManager.h"
#include "ClassUC.h"

/**
 * @brief this function get a set of all the students in the DataManager
 *
 * Time complexity O(n), where 'n' is the number of students in the DataManager
 */
set<Student> DataManager::getStudents() {
    return students;
}
/**
 * @brief this function set the students in the DataManager to a new set of students
 *
 * @param newStudents The new set of students to be stored in the DataManager
 *
 * Time complexity O(n), where 'n' is the number of students in the new set
 */

void DataManager::setStudents(set<Student> newStudents) {
    students=newStudents;
}

/**
 * @brief this function reads student class information and update the DataManager's student set.
 *
 * Time complexity O(n), where 'n' is the number of entries in the file
 */
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

/**
 * @brief this function gets a constant reference to the vector of all UCs stored in the DataManager
 *
 * @return A constant reference to the vector of all UCs
 *
 * Time complexity O(1)
 */
const vector<ClassUC> &DataManager::getAllUC() const {
    return allUC_;
}

/**
 * @brief this function reads class information from a file and update the DataManager's vector of UCs
 *
 * Time complexity O(n), where 'n' is the number of entries in the file
 */
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


/**
 * @brief this function add a student to the DataManager's set of students
 *
 * @param student The Student object to be added.
 *
 * Time complexity is O(log n), where 'n' is the number of students in the set
 */

void DataManager::addStudent(const Student& student) {
    students.insert(student);
}

/**
 * @brief this function add a ClassUC object to the DataManager's vector of UCs
 *
 * @param classUC The ClassUC object to be added
 *
 * Time complexity  is O(1)
 */
void DataManager::addClassUC(const ClassUC& classUC) {
    allUC_.push_back(classUC);
}

/**
 * @brief this function gets a vector of students enrolled in a specific UC.
 *
 * @param ucId The UC code for which to retrieve enrolled students.
 *
 * @return A vector of students who are enrolled in the specified UC.
 *
 * Time complexity O(n * m), where 'n is the number of students and 'n' is the average number of UCs associated with each student
 */
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

/**
 * @brief this function gets a vector of classes associated with a specific UC
 *
 * @param ucId The UC code for which to retrieve associated classes.
 *
 * @return A vector of classes associated with the specified UC.
 *
 * Time complexity O(n), where 'n is the number of classes in the `allUC_`
 */
vector<ClassUC> DataManager::classOfUc(const string& ucId)const{//iterate throw allUc and get only the ucClasses with ucID;
    vector<ClassUC> uc_classes;
    for (const auto& classUc:allUC_){
        if(classUc.getUcCode()==ucId) {
            uc_classes.push_back(classUc);
        }
    }
    return uc_classes;
}

/**
 * @brief this function gets the number of students enrolled in a specific UC
 *
 * @param ucId The UC code for which to count the enrolled students
 *
 * @return The number of students enrolled in the specified UC
 *
 * Time complexity O(n * m), where 'n' is the number of students and 'm' is the average number of UCs associated with each student
 */
int DataManager::numberStudentsUc(const string& ucId)const{
    vector<Student> studentUC= UCstudents(ucId);
    return  studentUC.size();
}

/**
 * @brief this function compares two ClassUC objects based on UC student occupation
 *
 * @param a The first ClassUC object to compare
 *
 * @param b The second ClassUC object to compare
 *
 * @return True if the UC associated with 'a' has more students enrolled than the UC associated with 'b' ,otherwise false.
 *
 * Time complexity  O(n * m), where 'n' is the number of students, and 'm' is the average number of UCs associated with each studen
 */
bool DataManager::sorterOccupation(const ClassUC& a, const ClassUC& b) const{
    const string& Acode=a.getUcCode();
    const string& Bcode=b.getUcCode();
    return (numberStudentsUc(Acode)> numberStudentsUc(Bcode));
}

/**
 * @brief this function gets a vector of ClassUC objects associated with a specific year identifier
 *
 * @param year The year identifier to filter the classes
 *
 * @return A vector of ClassUC objects associated with the specified year
 *
 * Time complexity O(n), where 'n' is the number of ClassUC objects in the `allUC_
 */
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

/**
 * @brief this function gets a vector of ClassUC objects with a specific number of enrolled students
 *
 * @param x The number of students for filtering
 *
 * @return A vector of ClassUC objects with 'x' enrolled students
 *
 * Time complexity O(n), where 'n' is the number of ClassUC objects in the `allUC_
 */
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


/**
 * @brief this function sort the `allUC_` vector by UC student occupation
 *
 * @return A sorted vector of ClassUC objects
 *
 * Time complexity O(n log n), where 'n' is the number of ClassUC objects in the `allUC_`
 */
vector<ClassUC> DataManager::sortAllU_occupation(){
    vector<ClassUC> sortedAlluc=allUC_;
    DataManager dataManager;
    sort(sortedAlluc.begin(), sortedAlluc.end(), [&dataManager](const ClassUC& a, const ClassUC& b) {return dataManager.sorterOccupation(a, b);});
    return sortedAlluc;
}

/**
 * @brief Comparison function for sorting ClassUC objects
 *
 * @param a The first ClassUC object to compare
 *
 * @param b The second ClassUC object to compare
 *
 * @return True if 'a' should come before 'b' in the sorted order, otherwise false
 *
 * Time complexity O(n * m), where 'n' is the number of students and 'm' is the average number of UCs associated with each student
 */
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

/**
 * @brief this function sort the `allUC_` vector using the `sorter` comparison function
 *
 * This method sorts the `allUC_` vector based on the comparison function `sorter`
 *
 * @return A sorted vector of ClassUC objects
 *
 * Time complexity  O(n  log n), where 'n' is the number of ClassUC objects in the `allUC_` vector
 */
vector<ClassUC> DataManager::sortAllU(){
    vector<ClassUC> sortedAlluc=allUC_;
    DataManager dataManager;
    sort(sortedAlluc.begin(), sortedAlluc.end(), [&dataManager](const ClassUC& a, const ClassUC& b) {return dataManager.sorter(a, b);});//I used the lamda funtion to call the sorter which is a method of class Datamanager;
    return  sortedAlluc;
}

/**
 * @brief this function counts students who are registered in at least 'n' UCs
 *
 * @param n The minimum number of UCs a student should be registered in
 *
 * @return The count of students meeting the criteria
 *
 * Time complexity O(n * m), where 'n' is the number of students and 'm' is the average number of UCs associated with each student
 */

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

/**
 * @brief this function gets a vector of students enrolled in a specific ClassUC
 *
 * @param classUc The ClassUC object for which to retrieve enrolled students
 *
 * @return A vector of students enrolled in the specified ClassUC.
 *
 * Time complexity O(n * m), where 'n' is the number of students and 'm' is the average number of UCs associated with each student
 */
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

/**
 * @brief this function gets the schedule of a specific ClassUC
 *
 * @param classUc2 The ClassUC for which to retrieve the schedule
 *
 * @return A vector of Slot objects representing the schedule of the specified ClassUC
 *
 * Time complexity O(n), where 'n' is the number of ClassUC objects in the allUC_
 */

vector<Slot> DataManager::getClassUCSchedule(const ClassUC& classUc2) {
    vector<Slot> schedule;
    for (auto uc : allUC_) {
        if(uc.getClassCode()==classUc2.getClassCode() and uc.getUcCode()==classUc2.getUcCode()){
            schedule = uc.getSchedule();
        }
    }
    return schedule;
}

/**
 * @brief this function gets the schedule of a specific UC (University Course).
 *
 * @param UcId The UC code for which to retrieve the schedule.
 *
 * @return A vector of Slot objects representing the schedule of the specified UC.
 *
 * Time complexity O(n), where 'n' is the number of ClassUC objects in the allUC_
 */
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

/**
 * @brief this function gets the schedule of a specific class.
 *
 * @param classCode The class code for which to retrieve the schedule.
 *
 * @return A vector of Slot objects representing the schedule of the specified class.
 *
 * Time complexity O(n), where 'n' is the number of ClassUC objects in the allUC_
 */
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

/**
 * @brief this function gets the schedule of a specific student
 *
 * @param student The Student object for which to retrieve the schedule.
 *
 * @return A Student object with an updated schedule based on the student's enrolled classes.
 *
 *  Time complexity of O(n), where 'n' is the number of ClassUC
 */
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

/**
 * @brief this function finds a specific student
 *
 * @param student The Student object to find
 *
 * @return The found Student object
 *
 * Time complexity O(log n), where 'n' is the number of students
 */
Student DataManager::findStudent(const Student& student) {//with a name and the up code,get the classes of the student
    auto  it=students.find(student);
    return *it;
}

/**
 * @brief this function checks if a specific ClassUC has less than 'x' students
 *
 * @param classUc The ClassUC to check for student enrollment
 *
 * @param x The threshold number of students to compare against
 *
 * @return True if the ClassUC has fewer than 'x' students, otherwise false
 *
 * Time complexity  O(n * m), where 'n' is the number of students and 'm' is the average number of UCs associated with each student
 */

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

