/*

Header file for single linked list class library

*/
#include <string>
#include "airport.h"
#include "node.h"

#ifndef SLIST_H
#define SLIST_H

class slist {
    
public:
    Node* head;
    slist();
    ~slist();
    Node*       getNodeAtIndex(int index);
    void        add(Airport value);
    void        clear();
    bool        equals(slist list);
    Airport    get(int index);
    void        insert(int index, Airport value);
    void        exchg(int index1, int index2);
    void        swap(int index1, int index2);
    bool        isEmpty();
 // void        mapAll(void (*fn)(int));
    void        remove(int index);
    void        set(int index, Airport value);
    int         size();
    slist       subList(int start, int length);
    std::string toString();
};

#endif
