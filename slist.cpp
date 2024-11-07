#include "slist.h"
#include "airport.h"
#include "node.h"
#include <iostream>

/*

Class Library File

*/

Node* head;
// Constructor
slist::slist(){
    head = nullptr;   
}
// Destructor
slist::~slist(){
    Node* currentNode = head;
    while (currentNode != nullptr){
        Node* temp = currentNode;
        currentNode = currentNode->next;
        delete temp;
    }
}
// add(value)				//Adds a new value to the end of this list.
void slist::add(Airport value){
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}
// clear()					//Removes all elements from this list.
void slist::clear(){
    this->~slist();
}
// equals(list)				//Returns true if the two lists contain the same elements in the same order.
bool slist::equals(slist list){
    Node* currentNode = head;
    Node* otherNode = list.head;
    while(currentNode != nullptr && otherNode != nullptr){
        if (!currentNode->data.equals(otherNode->data)) {
        return false;
        }
        currentNode = currentNode->next;
        otherNode = otherNode->next;
    }
    if (otherNode != nullptr){
        return false;
    }
    return true;
}
//get(index)				//Returns the element at the specified index in this list.
Airport slist::get(int index){
    Node* currentNode = head;
    int counter = 0;

    while (currentNode != nullptr && counter < index) {
        currentNode = currentNode->next;
        counter++;
    }
    // std::cout << counter;

    if (currentNode != nullptr) {
        return currentNode->data;
    } else {
        // out-of-bounds index
        std::cout << "ERROR\n";
        return Airport();
    }
}
//insert(index, value)		//Inserts the element into this list before the specified index.
void slist::insert(int index, Airport value){
    Node* newNode = new Node(value);
    if (index == 0) {
        // head exception
        newNode->next = head;
        head = newNode;
    } else {
        Node* prevNode = nullptr;
        Node* currentNode = head;
        int counter = 0;

        while (currentNode != nullptr && counter < index) {
            prevNode = currentNode;
            currentNode = currentNode->next;
            counter++;
        }

        if (currentNode != nullptr) {
            prevNode->next = newNode;
            newNode->next = currentNode;
        } else {
            prevNode->next = newNode;
            newNode->next = nullptr;
        }
    }
}
// getNodeAtIndex(index) allows for the return of a node, rather than just airport
Node* slist::getNodeAtIndex(int index) {
    Node* current = head;
    for (int i = 0; i < index && current != nullptr; ++i) {
        current = current->next;
    }
    return current;
}
//exchg(index1, index2)		//Switches the payload data of specified indexex.
void slist::exchg(int index1, int index2){
    if (index1 < 0 || index2 < 0 || index1 >= size() || index2 >= size()) {
        // out-of-bounds
        return;
    }

    Node* node1 = getNodeAtIndex(index1);
    Node* node2 = getNodeAtIndex(index2);

    // swap is super useful
    std::swap(node1->data, node2->data);
}
//swap(index1,index2)		//Swaps node located at index1 with node at index2
void slist::swap(int index1, int index2){
    if (index1 < 0 || index2 < 0 || index1 >= size() || index2 >= size()) {
        // out-of-bounds
        return;
    }

    Node* prev1 = nullptr;
    Node* node1 = head;
    for (int i = 0; i < index1; ++i) {
        prev1 = node1;
        node1 = node1->next;
    }

    Node* prev2 = nullptr;
    Node* node2 = head;
    for (int i = 0; i < index2; ++i) {
        prev2 = node2;
        node2 = node2->next;
    }

    if (node1 == node2->next || node2 == node1->next) {
        // Swap the 'next' pointers directly
        node1->next = node2->next;
        node2->next = node1;
        if (prev1) { // check if not null
            prev1->next = node2;
        } else {
            head = node2;
        }
    } else {
        Node* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;

        if (prev1) { // check if not null
            prev1->next = node2;
        } else {
            head = node2;
        }

        if (prev2) { // check if not null
            prev2->next = node1;
        } else {
            head = node1;
        }
    }
}
// isEmpty()				//Returns true if this list contains no elements.
bool slist::isEmpty(){
    return head == nullptr;
}
// remove(index)			//Removes the element at the specified index from this list.
void slist::remove(int index){
    if (index == 0) {
        // head node
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    Node* currentNode = head;
    int counter = 0;
    while(currentNode != nullptr){
        if (counter+1 == index){
            Node* temp = currentNode->next->next;
            delete currentNode->next;
            currentNode->next = temp;
        }
        counter++;
        currentNode = currentNode->next;
    }
}
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
void slist::set(int index, Airport value){
    Node* currentNode = head;
    int counter = 0;
    while (currentNode != nullptr) {
        if(counter == index){
            currentNode->data = value;
        }
        counter++;
        currentNode = currentNode->next;
    }
    
}
// size()					//Returns the number of elements in this list.
int slist::size(){
    Node* currentNode = head;
    int counter = 0;
    while(currentNode != nullptr){
        currentNode = currentNode->next;
        counter++;
    }
    return counter;
}
// subList(start, length)	//Returns a new list containing elements from a sub-range of this list.
slist slist::subList(int start, int length){
    if (start < 0 || length < 0 || start + length > size()) {
        // invalid input
        return slist();
    }
    slist returnList;
    Node* current = head;
    for (int i = 0; i < start; ++i) {
        current = current->next;
    }
    for (int i = 0; i < length; ++i) {
        returnList.add(current->data);
        current = current->next;
    }
    return returnList;
}
// toString()				//Converts the list to a printable string representation.
std::string slist::toString(){
    Node* currentNode = head;
    std::string returnString = "";
    while(currentNode != nullptr){
        returnString = returnString + " " + currentNode->data.toString();
        currentNode = currentNode->next;
    }
    returnString = returnString + " nullprt"; 
    return returnString;
}
