/**
*
* @author - Adrian Aquino, Wen-Chien Yen
* @file hash_table.cpp - Implementation of the hash table
*
* 03/11/25 - Imported Adrian Aquino's hash_table.cpp from milestone 2
* 03/19/25 - Fixed implementation of add method
*
*/

#include <iostream>
#include <fstream>
#include "hash_table.h"

extern std::ofstream& getOutFile();


/**
*
* getTable
*
* Method to return the hash table
*
* @param    none
*
* @return   pointer to the hash table array
*/

HashNode** HashTable::getTable() {
    return table;
}


/**
*
* getSize
*
* Method to return the size of the hash table
*
* @param    none
*
* @returns  size of the hash table array
*/
int HashTable::getSize() {
    return numberOfBuckets;
}


/**
*
* calculateHashCode
*
* Method to calculate the hashCode
*
* @param    currentKey     key to be hashed
*
* @return   hashcode for currentKey
*/

int HashTable::calculateHashCode(int currentKey) {
    return currentKey % numberOfBuckets;
}


/**
*
* isEmpty
*
* Method to check if HashTable is empty
*
* @param    none
*
* @return   true if the table has zero entries, false otherwise
*/

bool HashTable::isEmpty() {
    return numberOfItems == 0;
}


/**
*
* getNumberOfItems
*
* Method to return number of items in the hash table
*
* @param    none
*
* @return   number of items in the table
*/

int HashTable::getNumberOfItems() {
    return numberOfItems;
}


/**
*
* add
*
* Method to add a node to the hash table
*
* @param    curKey    key for this node
* @param    myNode    new node to add to the table
*
* @return   true if success, false otherwise
*/

bool HashTable::add(int curKey, HashNode* myNode) {
    int hashCode = calculateHashCode(curKey);
    myNode->hashCode = hashCode;
    myNode->key = curKey;

    if (table[hashCode] == nullptr) {
        table[hashCode] = myNode;
        myNode->next = nullptr;
        myNode->prev = nullptr;
    } else {
        // Check if key already exists
        HashNode* current = table[hashCode];
        while (current != nullptr) {
            if (current->key == curKey) {
                // Replace existing node
                if (current->prev == nullptr) {
                    table[hashCode] = myNode;
                } else {
                    current->prev->next = myNode;
                }

                if (current->next != nullptr) {
                    current->next->prev = myNode;
                }

                myNode->prev = current->prev;
                myNode->next = current->next;

                delete current;
                return true;
            }
            current = current->next;
        }

        // Add to beginning of chain
        myNode->next = table[hashCode];
        myNode->prev = nullptr;
        table[hashCode]->prev = myNode;
        table[hashCode] = myNode;
    }

    numberOfItems++;
    return true;
}

/**
*
* remove
*
* Method to remove node with curKey
*
* @param    curKey     key of node to remove
*
* @return   true if success, false otherwise
*/
bool HashTable::remove(int curKey) {
    int hashCode = calculateHashCode(curKey);

    if (table[hashCode] == nullptr) {
        return false;
    }

    HashNode* current = table[hashCode];
    while (current != nullptr && current->key != curKey) {
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        table[hashCode] = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current;
    numberOfItems--;

    return true;
}


/**
*
* clear
*
* Method to remove all entries from the table
*
* @param    none
*
* @return   nothing, but will delete all entries from the table
*/

void HashTable::clear() {
    for (int i = 0; i < numberOfBuckets; i++) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }

        table[i] = nullptr;
    }

    numberOfItems = 0;
}


/**
*
* getItem
*
* Method to retrieve item from the hash table
*
* @param    curKey  retrieve node from hash table with curKey value
*
* @return   pointer to the HashNode
*/

HashNode* HashTable::getItem(int curKey) {
    int hashCode = calculateHashCode(curKey);

    HashNode* current = table[hashCode];
    while (current != nullptr) {
        if (current->key == curKey) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}


/**
*
* contains
*
* Method to check if a node with key exists in the table
*
* @param    curKey  key value to find
*
* @return   true if found, false otherwise
*/

bool HashTable::contains(int curKey) {
    return getItem(curKey) != nullptr;
}


/**
*
* printTable
*
* Method to print out the contents of table
*
* @param none
*
* @return               nothing, but output is sent to console
*/
void HashTable::printTable() {
    std::ofstream& outFile = getOutFile();

    std::cout << "\nHere are the Hash Table contents (" << numberOfItems << " entries):" << std::endl;
    outFile << "\nHere are the Hash Table contents (" << numberOfItems << " entries):" << std::endl;

    for (int i = 0; i < numberOfBuckets; i++) {
        if (table[i] == nullptr) {
            std::cout << "Bucket " << i << ": Empty" << std::endl;
            outFile << "Bucket " << i << ": Empty" << std::endl;
        } else {
            std::cout << "Bucket " << i << ": " << std::endl;
            outFile << "Bucket " << i << ": " << std::endl;

            HashNode* current = table[i];
            while (current != nullptr) {
                current->fifoNode->printNode();
                current = current->next;
            }
        }
    }

    std::cout << "End of table" << std::endl;
    outFile << "End of table" << std::endl;
}