/**
*
* @author - Adrian Aquino, Wen-Chien Yen
* @file hash_table.cpp - Implementation of the hash table
*
* 03/11/25 - Imported Adrian Aquino's hash_table.cpp from milestone 2
*/

#include "hash_table.h"
#include <iostream>
#include <string>

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
    int result = currentKey % numberOfBuckets;
    return result;
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
    if (numberOfItems == 0) {
        return true;
    } else {
        return false;
    }
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

    if (table[hashCode] == nullptr) {
        table[hashCode] = myNode;
        numberOfItems++;
        return true;
    }

    HashNode* current = table[hashCode];

    while (current != nullptr) {
        if (current->key == curKey) {
            myNode->next = current->next;
            myNode->prev = current->prev;

            if (current->prev != nullptr) {
                current->prev->next = myNode;
            } else {
                table[hashCode] = myNode;
            }

            if (current->next != nullptr) {
                current->next->prev = myNode;
            }

            delete current;
            return true;
        }
        current = current->next;
    }

    myNode->next = table[hashCode];
    table[hashCode]->prev = myNode;
    table[hashCode] = myNode;
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
* Method to verify if a key is in the hash table
*
* @param    curKey  check key for hash table with curKey value
*
* @return   true if found, false otherwise
*/
bool HashTable::contains(int curKey) {
    HashNode* result = getItem(curKey);

    if (result == nullptr) {
        return false;
    } else {
        return true;
    }
}

/**
*
* printTable
*
* Method to print out the contents of table
*
* @param    none
*
* @return   nothing, but output is sent to console and to file
*/
void HashTable::printTable() {
    std::ofstream& outFile = getOutFile();

    std::cout << "\nTable contents (" << numberOfItems << " entries):\n\n";
    outFile << "\nTable contents (" << numberOfItems << " entries):\n\n";

    int emptyStart = -1;
    int i = 0;

    while (i < numberOfBuckets) {
        if (table[i] == nullptr) {
            emptyStart = i;

            std::cout << "Empty: ";
            outFile << "Empty: ";

            while (i < numberOfBuckets && table[i] == nullptr) {
                std::cout << i;
                outFile << i;

                i++;
                if (i < numberOfBuckets && table[i] == nullptr) {
                    std::cout << ", ";
                    outFile << ", ";
                }
            }

            std::cout << "\n\n";
            outFile << "\n\n";
        } else {
            std::cout << "Index: " << i << ": ";
            outFile << "Index: " << i << ": ";

            HashNode* current = table[i];
            while (current != nullptr) {
                std::cout << current->key;
                outFile << current->key;

                if (current->next != nullptr) {
                    std::cout << " -> ";
                    outFile << " -> ";
                }

                current = current->next;
            }

            std::cout << "\n\n";
            outFile << "\n\n";
            i++;
        }
    }

    std::cout << "End of table\n";
    outFile << "End of table\n";
}
