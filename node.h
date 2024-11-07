#include "airport.h"
#include <iostream>

#ifndef NODE_H
#define NODE_H

class Node{
public:
    Airport data;
    Node* next;

    Node(Airport value){
        data = value;
        next = nullptr;
    } 
};

#endif