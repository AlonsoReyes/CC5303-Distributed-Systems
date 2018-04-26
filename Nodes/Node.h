//
// Created by marti on 19-04-2018.
//
#include "Table.h"
#include <string>
#include <iostream>
#include <deque>
#include "../utils.h"
#include <mutex>

#define ACK_MESSAGE 1
#define CHAT_MESSAGE 2
#define TABLE_MESSAGE 3

#define HEADER_SIZE 19

#ifndef CC5303_DISTRIBUTED_SYSTEMS_NODE_H
#define CC5303_DISTRIBUTED_SYSTEMS_NODE_H


class Node {

public:
    std::mutex mtx;
    Table table;
    std::string ip;
    uint16_t port;
    std::string name;
    std::vector<std::pair<std::string, std::pair<int, int>>> connections;
    std::deque<unsigned char*> message_queue;
    int connectionIndex = 0;
    std::vector<std::pair<int, std::string>> socketDescriptors;
    explicit Node(std::string ip, uint16_t port, std::string name);
    virtual int receivePacket(char* p);
    virtual void receiveTablePacket();
    virtual int run();
    Table* getTable();
    std::string getSrcIp(const unsigned char* packet);
    std::string getDestIp(const unsigned char* packet);
    std::string getMessage(const unsigned char* packet);
    int getLastBit(const unsigned char* packet);
    int getFragmentBit(const unsigned char* packet);
    uint16_t getTotalLength(const unsigned char* packet);
    int getType(const unsigned char* packet);
    uint16_t getOffset(const unsigned char* packet);
    uint16_t getSrcPort(const unsigned char* packet);
    uint16_t getDestPort(const unsigned char* packet);
    void printPacket(const unsigned char* packet);
    unsigned char* makePacket(std::string ip_dest, std::string port_dest, int type, std::string message);
    std::pair<char *, char *> fragment(size_t packet, int MTU);
    void sendNextPacket();
    virtual int sendMessage(std::string ip_dest, std::string port_dest, int type, std::string message);
};


#endif //CC5303_DISTRIBUTED_SYSTEMS_NODE_H
