//
// Created by marti on 19-04-2018.
//
#include "Table.h"
#include "../Packets/Packet.h"
#include <string>

#ifndef CC5303_DISTRIBUTED_SYSTEMS_NODE_H
#define CC5303_DISTRIBUTED_SYSTEMS_NODE_H


class Node {
    private:
        Table table;
        std::string ip;
        int port;
        std::string name;

    public:
        explicit Node(std::string ip, int port, std::string name);
        int establish_connection(int ip, int port);
        int receive_packet(Packet);
        int send_packet(Packet);
        void listening();
        void run();
};


#endif //CC5303_DISTRIBUTED_SYSTEMS_NODE_H
