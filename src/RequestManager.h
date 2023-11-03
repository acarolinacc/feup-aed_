#ifndef FEUP_AED1_REQUESTMANAGER_H
#define FEUP_AED1_REQUESTMANAGER_H

#include <queue>
#include "DataManager.h"
#include "student.h"
#include "Request.h"
#include <algorithm>
class RequestManager {
public:
    RequestManager(DataManager &manager);
    RequestManager();
    void setManager(DataManager manager);
    void addResquest(const Request& newRequest);
    void addDinedRequest(const Request& newRequest);
    void addAcceptRequest(const Request& newRequest);

    queue<Request> getRequest() const;
    //class Changes:
    bool checkOneClassUcPerStudent(const Request& request);
    bool checkIfTheCapIsExceeded(const Request& request);
    bool checkIfBalanceOcuppation(const Request& request);
    bool  checkIfTheSchedulesOverlap(const Request& request);
    bool checkClassRequest(const Request& request);
    bool checkClassStudent(const Request& request);



    //uc changes;
    bool haveScheduleConflict(const ClassUC &studentClass, const ClassUC &newClass) const;
    ClassUC getClassUCByCode(const string &ucCode);
    Student getStudentByUP(const int &upNumber);
    bool ingressarEmUC(const int &upNumber, const string &ucCode);
    bool sairDeUC(int upNumber, const string &ucCode);

    void requestProcess(DataManager &newManager,bool action);
    bool UcProcess(const Request& request);
    bool changeCLass(const Request& request,DataManager &newManager);
    bool changeUC(const Request& request,DataManager &newManager);
    ClassUC findClassinUc(Student student, const string& ucCode);
    bool undorequestUC(Request ucResquest);
    bool undorequestClass(Request classResquest);
    void undoRequest();
    void processUndoRequest(DataManager &newManager);
    void restore(const Request& request);






    int const CAP=25;

private:
    queue<Request> requests;
    DataManager manager;
    queue<Request>acceptRequest;
    queue<Request>deniedRequest;
    queue<Request> undoneRequests;



};



#endif //FEUP_AED1_REQUESTMANAGER_H
