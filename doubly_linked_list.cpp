/**
*
* @author - Adrian Aquino, Wen-Chien Yen
* @file doubly_linked_list.cpp - Implementation of the doubly linked list
*
* 03/11/25 - Imported Wen-Chien Yen's doubly_linked_list.cpp from milestone 1
* 03/13/25 - Updated DllNode
* 03/14/25 - Added JavaDoc style comments from doubly_linked_list.h
* 03/19/25 - Updated print methods to match output file
*/

#include "doubly_linked_list.h"
#include <iostream>
#include <string>

extern std::ofstream& getOutFile();
extern void logToFileAndConsole(std::string msg);

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

/**
*
* getSize
*
* Method to return number of entries in the list
*
* @param: nothing
*
* @return: number of entries in the list
*/
int DoublyLinkedList::getSize() {
    return size;
}

/**
 *
 * isEmpty
 *
 * Method to check if the list is empty
 *
 * @param: nothing
 *
 * @return: true if head pointer is nullptr, otherwise return false
 */
bool DoublyLinkedList::isEmpty() {
    return head == nullptr;
}

/**
*
* insertAtHead
*
* Method to insert a new node at the head of the list
*
* @param    key     the int key for new node
* @param    newNode the new dll node
*
* @return: nothing; updates doubly linked list and size
*/
void DoublyLinkedList::insertAtHead(int key, DllNode* newNode) {
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        newNode->prev = nullptr;
        newNode->next = nullptr;
    } else {
        newNode->next = head;
        newNode->prev = nullptr;
        head->prev = newNode;
        head = newNode;
    }
    size++;
}

/**
*
* insertAtTail
*
* Method to insert a new node at the tail of the list
*
* @param    key     the int key for new node
* @param    newNode the new dll node
*
* @return: nothing; updates doubly linked list and size
*/
void DoublyLinkedList::insertAtTail(int key, DllNode* newNode) {
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
        newNode->prev = nullptr;
        newNode->next = nullptr;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = nullptr;
        tail = newNode;
    }
    size++;
}

/**
*
* remove
*
* Method to remove a node with a specific value from the list
*
* @param: key
*
* @return: nothing; updates doubly linked list
*/
void DoublyLinkedList::remove(int key) {
    if (isEmpty()) {
        return;
    }

    DllNode* current = head;

    while (current != nullptr) {
        if (current->key == key) {
            // If it's the only node
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            }
            // If it's the head
            else if (current == head) {
                head = head->next;
                head->prev = nullptr;
            }
            // If it's the tail
            else if (current == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            // If it's in the middle
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            delete current;
            size--;
            return;
        }
        current = current->next;
    }
}

/**
*
* removeHeaderNode
*
* Method to remove the header node (first node)
*
* @param: none
*
* @return: nothing; updates doubly linked list
*/
void DoublyLinkedList::removeHeaderNode() {
    if (isEmpty()) {
        return;
    }

    DllNode* temp = head;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }

    delete temp;
    size--;
}

/**
*
* removeTailNode
*
* Method to remove the tail node (last node)
*
* @param: none
*
* @return: nothing; updates doubly linked list
*/
void DoublyLinkedList::removeTailNode() {
    if (isEmpty()) {
        return;
    }

    DllNode* temp = tail;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    size--;
}

/**
*
* moveNodeToHead
*
* Method to move a specific node to the head of the list
*
* @param: key
*
* @return: nothing; updates doubly linked list
*/
void DoublyLinkedList::moveNodeToHead(int key) {
    if (isEmpty() || head->key == key) {
        return;
    }

    DllNode* current = head->next;

    while (current != nullptr) {
        if (current->key == key) {
            // If it's the tail
            if (current == tail) {
                tail = current->prev;
                tail->next = nullptr;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            // Move to head
            current->next = head;
            current->prev = nullptr;
            head->prev = current;
            head = current;
            return;
        }
        current = current->next;
    }
}

/**
*
* moveNodeToTail
*
* Method to move a specific node to the tail of the list
*
* @param: key
*
* @return: nothing; updates doubly linked list
*/
void DoublyLinkedList::moveNodeToTail(int key) {
    if (isEmpty() || tail->key == key) {
        return;
    }

    DllNode* current = head;

    while (current != nullptr) {
        if (current->key == key) {
            if (current == tail) {
                return;
            }

            if (current == head) {
                head = current->next;
                head->prev = nullptr;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            current->next = nullptr;
            current->prev = tail;
            tail->next = current;
            tail = current;
            return;
        }
        current = current->next;
    }
}

/**
*
* clear
*
* Method to clear the list by deleting all nodes
*
* @param: none
*
* @return: nothing; reset size to 0
*/
void DoublyLinkedList::clear() {
    DllNode* current = head;
    while (current != nullptr) {
        DllNode* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

/**
*
* printList
*
* Method to print the doubly linked list from head to tail to console and output file
*
* @param dll	none
*
* @return		nothing
*/
void DoublyLinkedList::printList() {
    std::ofstream& outFile = getOutFile();

    if (isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        outFile << "The list is empty." << std::endl;
        return;
    }

    DllNode* current = head;
    while (current != nullptr) {
        std::cout << "FIFO Node key: " << current->key << " " << std::endl;
        outFile << "FIFO Node key: " << current->key << " " << std::endl;
        current = current->next;
    }
}

/**
*
* reversePrintList
*
* Method to print the doubly linked list from tail to head to console and output file
*
* @param dll	none
*
* @return		nothing
*/
void DoublyLinkedList::reversePrintList() {
    std::ofstream& outFile = getOutFile();

    if (isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        outFile << "The list is empty." << std::endl;
        return;
    }

    DllNode* current = tail;
    while (current != nullptr) {
        std::cout << "FIFO Node key: " << current->key << " " << std::endl;
        outFile << "FIFO Node key: " << current->key << " " << std::endl;
        current = current->prev;
    }
}