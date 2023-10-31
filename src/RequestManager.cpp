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

bool RequestManager::checkIfBalanceOcuppation(const Request &request) {//non tested
    int mins=CAP;int maxs=0;
    const int MAXDIFFERENCE=4;
    vector<ClassUC> allClassOfUc=manager.classOfUc(request.getClassUc().getUcCode());//vector with all classes of a uc;
    for(const ClassUC& classUc:allClassOfUc){
        int size_class=manager.studentsOfClassUc(classUc).size();
        if(classUc.getClassCode()==request.getClassUc().getClassCode()){//we want to check if the addition of the student will cause an imbalance so we need to add the student to the size of the requested_class
            size_class++;
        }
        if(size_class>maxs){maxs=size_class;}
        if(size_class<mins){mins=size_class;}
    }
    return (maxs-mins)<=MAXDIFFERENCE;
}




bool RequestManager::checkIfTheSchedulesOverlap(const Request& request) {
    ClassUC requestclass=request.getClassUc();
    Student requestStudent=request.getStudent();
    requestStudent=manager.findStudent(requestStudent);//i dont think is need but is to make sure that this student have classes;
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

RequestManager::RequestManager() = default;



