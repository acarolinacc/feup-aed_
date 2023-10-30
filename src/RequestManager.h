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
    void addResquest(const Request& newRequest);
    queue<Request> getRequest() const;
    //class Changes:
    bool checkOneClassUcPerStudent(const Request& request);
    bool checkIfTheCapIsExceeded(const Request& request);
    bool checkIfBalanceOcuppation(const Request& request);
    bool  checkIfTheSchedulesOverlap(const Request& request);







    int const CAP=25;

private:
    queue<Request> requests;
    DataManager manager;
};



#endif //FEUP_AED1_REQUESTMANAGER_H
