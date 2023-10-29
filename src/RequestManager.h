#ifndef FEUP_AED1_REQUESTMANAGER_H
#define FEUP_AED1_REQUESTMANAGER_H

#include <queue>
#include "DataManager.h"
#include "student.h"
#include "Request.h"
class RequestManager {
public:
    RequestManager(DataManager &manager);
    void addResquest(const Request& newRequest);
    queue<Request> getRequest() const;



private:
    queue<Request> requests;
    DataManager manager;
};



#endif //FEUP_AED1_REQUESTMANAGER_H
