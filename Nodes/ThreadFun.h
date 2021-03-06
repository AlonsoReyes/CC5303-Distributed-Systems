//
// Created by marti on 24-04-2018.
//

#ifndef CC5303_DISTRIBUTED_SYSTEMS_RECEIVE_H
#define CC5303_DISTRIBUTED_SYSTEMS_RECEIVE_H

#endif //CC5303_DISTRIBUTED_SYSTEMS_RECEIVE_H

#include "C.h"
#include "T.h"

void acceptTh(Node *n, int sd);
void receiveTh(Node *n, int sd);
void sendTh(T* n);
void cProcessTh(C*n);
void cServerTh(C *n);
void tServerTh(T *n);
void offServerTh(Node* n);
void tMigrateServerTh(T *n, std::string sIP, std::string sPort, std::string type);
void cMigrateServerTh(C *n, std::string sIP, std::string sPort, std::string type);