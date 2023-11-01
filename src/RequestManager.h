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
    queue<Request> getRequest() const;
    //class Changes:
    bool checkOneClassUcPerStudent(const Request& request);
    bool checkIfTheCapIsExceeded(const Request& request);
    bool checkIfBalanceOcuppation(const Request& request);
    bool  checkIfTheSchedulesOverlap(const Request& request);
    bool checkClassRequest(const Request& request);






    int const CAP=25;

private:
    queue<Request> requests;
    DataManager manager;
    queue<Request>deniedRequest;
};



#endif //FEUP_AED1_REQUESTMANAGER_H
