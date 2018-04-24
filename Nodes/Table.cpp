//
// Created by marti on 19-04-2018.
//

#include "Table.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

void Table::addDirectClient(std::string name) {
    this->direct_clients.push_back(name);
}

void Table::addDirectRouter(std::string name) {
    this->direct_routers.push_back(name);
}

void Table::addReachableClient(std::string name, std::vector<std::string> ways) {
    std::pair<std::string, std::vector<std::string>> p = std::pair<std::string, std::vector<std::string>>(name, ways);
    std::vector<std::pair<std::string, std::vector<std::string>>> v;
    v.push_back(p);
    this->reachable_clients.push_back(v);
}
