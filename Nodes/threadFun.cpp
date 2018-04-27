//
// Created by marti on 24-04-2018.
//

#include "threadFun.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "../utils.h"
#include <thread>


void acceptTh(Node *n, int sd) {
    while(1){
        int new_socket;
        struct sockaddr_in address;
        int addrlen = sizeof(address);

        if ((new_socket = accept(sd, (struct sockaddr *)&address,
                                 (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        std::string ip = inet_ntoa(address.sin_addr);
        std::string port = std::to_string(ntohs(address.sin_port));

        std::cout << "connnection established" << std::endl;

        std::thread receiver (receiveTh, n, new_socket);
        receiver.detach();
    }

}

void copyBuffer(char* buffer, char** to, int size) {
    for (int i = 0; i < size; i++) {
        (*to)[i] = (unsigned char) buffer[i];
    }
}

void receiveTh(Node *n, int sd){
    char buffer[1024] = {0};
    int valread = 1;
    while (valread > 0) {
        valread = read(sd, buffer, 1024);

        char * to = (char *)malloc(valread * sizeof(char));

        //unsigned char* to = (unsigned char *)malloc(valread * sizeof(unsigned char));
        //strncpy(to, buffer, valread);
        copyBuffer(buffer, &to, valread);
        n->printPacket((unsigned char*)to);

        (n->mtx).lock();
        (n->message_queue).push_back((unsigned  char*)to);
        (n->mtx).unlock();
    }
}

void sendTh(Node *n) {
    unsigned char* packet;
    std::string name;
    std::string ip;
    std::string port;
    std::vector<std::string> usefulRouters;
    while (1) {
        (n->mtx).lock();
        if (!n->message_queue.empty()) {
            packet = (n->message_queue).front();
            (n->message_queue).pop_front();
            (n->mtx).unlock();
            ip = n->getDestIp(packet);
            port = std::to_string(n->getDestPort(packet));
            name = ip + ":" + port;
            std::cout << "Searching for Routers..." << std::endl;
            usefulRouters = n->searchConnectedRouter(name);
            std::cout << "mensaje extraido: " << usefulRouters.front() << std::endl;
            int sd = n->getSocketDescriptor(usefulRouters.front());
            n->sendMessage(ip, port, n->getType(packet), n->getMessage(packet), sd);
            std::cout << "mensaje enviado: " << std::endl;
        } else {
            (n->mtx).unlock();
        }
        sleep(1);
    }
}

void cProcessTh(Node *n, int sd) {
    unsigned char* packet;
    std::string ip;
    std::string port;
    std::string name;
    while (1){
        (n->mtx).lock();
        if (!n->message_queue.empty()){
            packet = (n->message_queue).front();
            (n->message_queue).pop_front();
            (n->mtx).unlock();
            if (n->getType(packet) == CHAT_MESSAGE){
                ip = n->getSrcIp(packet);
                port = n->getSrcPort(packet);
                name = ip + ":" + port;
                std::cout << "llego mensaje de " << port << " : " << n->getMessage(packet) << std::endl;
                n->sendMessage(ip, port, ACK_MESSAGE, "", n->getSocketDescriptor(name));
            } else{
                //TODO: es ACK y desbloquea nodo
            }
        } else{
            (n->mtx).unlock();
        }
        sleep(5);
    }
}

