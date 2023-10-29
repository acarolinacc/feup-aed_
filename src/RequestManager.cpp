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

