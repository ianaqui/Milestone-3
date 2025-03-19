/**
*
* @author - Adrian Aquino, Wen-Chien Yen
* @file cache_manager.cpp - Implementation of the cache manager
*
* 03/13/25 - Created file and copied Javadoc comments from header file
* 03/14/25 - Implemented cache manager methods
*
*/

#include "cache_manager.h"
#include <iostream>
#include <string>

extern void logToFileAndConsole(std::string msg);
extern std::ofstream& getOutFile();

/**
*
* getTable
*
* Method to return the hash table
*
* @param    none
*
* @return	the hash table
*/
HashTable* CacheManager::getTable() {
    return hashTable;
}

/**
*
* getList
*
* Method to return the FIFO list
*
* @param    none
*
* @return	the FIFO list
*/
DoublyLinkedList* CacheManager::getList() {
    return doublyLinkedList;
}

/**
*
* getSize
*
* Method to return the number of items in the CacheManager
*
* @param    none
*
* @return	number of items in the CacheManager
*/
int CacheManager::getSize() {
    return hashTable->getNumberOfItems();
}

/**
*
* isEmpty
*
* Method to check if CacheManager is empty
*
* @param    none
*
* @return   true if the CacheManager has zero entries, false otherwise
*/
bool CacheManager::isEmpty() {
    return hashTable->isEmpty();
}

/**
*
* add
*
* Method to add a node to the CacheManager
*
* @param    curKey    key for this node
* @param    myNode    new node to add to the table
*
* @return   true if success, false otherwise
*/
bool CacheManager::add(int curKey, DllNode* myNode) {
    // Check if the key already exists and remove it
    if (contains(curKey)) {
        remove(curKey);
    }

    // Check if we need to remove the oldest item due to cache size limit
    if (doublyLinkedList->getSize() >= maxCacheSize) {
        if (!doublyLinkedList->isEmpty()) {
            int oldestKey = doublyLinkedList->tail->key;
            remove(oldestKey);
        }
    }

    // Create hash node and add to the hash table
    HashNode* newHashNode = new HashNode(curKey, myNode);
    bool addedToHash = hashTable->add(curKey, newHashNode);

    // Add to doubly linked list
    doublyLinkedList->insertAtHead(curKey, myNode);

    return addedToHash;
}

/**
*
* remove
*
* Method to remove node with curKey
*
* @param    key     key of node to remove
*
* @return   true if success, false otherwise
*/
bool CacheManager::remove(int curKey) {
    // Check if the key exists
    if (!hashTable->contains(curKey)) {
        return false;
    }

    // Remove from the doubly linked list first
    doublyLinkedList->remove(curKey);

    // Then remove from the hash table
    return hashTable->remove(curKey);
}

/**
*
* clear
*
* Method to remove all entries from the CacheManager
*
* @param    none
*
* @return   nothing, but will delete all entries from the CacheManager
*/
void CacheManager::clear() {
    doublyLinkedList->clear();
    hashTable->clear();
}

/**
*
* getItem
*
* Method to retrieve item from the CacheManager
*
* @param    curKey  retrieve node from CacheManager with curKey value
*
* @return   pointer to the DllNode
*/
DllNode* CacheManager::getItem(int curKey) {
    HashNode* hashNode = hashTable->getItem(curKey);
    if (hashNode == nullptr) {
        return nullptr;
    }

    // Move the node to the head to indicate recent usage
    doublyLinkedList->moveNodeToHead(curKey);

    return hashNode->getFifoNode();
}

/**
*
* getMaxCacheSize
*
* Method to retrieve max size of cache from the CacheManager
*
* @param    none
*
* @return   max size of cache manager
*/
int CacheManager::getMaxCacheSize() {
    return maxCacheSize;
}

/**
*
* contains
*
* Method to determine if a key value is in the cache
*
* @param    curKey  retrieve node from cacheManager with curKey value
*
* @return   true if exists, false otherwise
*/
bool CacheManager::contains(int curKey) {
    bool result = hashTable->contains(curKey);

    if (result) {
        doublyLinkedList->moveNodeToHead(curKey);
    }

    return result;
}

/**
*
* printCache
*
* Method to print out the cache information
*
* @param    none
*
* @return   pointer to the hash table array
*/
void CacheManager::printCache() {
    std::ofstream& outFile = getOutFile();

    std::cout << "\n\nPrinting out the cache contents" << std::endl;
    outFile << "\n\nPrinting out the cache contents" << std::endl;

    std::cout << "\nHere are the FIFO List contents: " << std::endl;
    outFile << "\nHere are the FIFO List contents: " << std::endl;

    if (doublyLinkedList->isEmpty()) {
        std::cout << "Empty list" << std::endl;
        outFile << "Empty list" << std::endl;
    } else {
        DllNode* current = doublyLinkedList->head;
        while (current != nullptr) {
            std::cout << "FIFO Node key: " << current->key << " " << std::endl;
            outFile << "FIFO Node key: " << current->key << " " << std::endl;
            current = current->next;
        }
    }

    std::cout << "End of FIFO List" << std::endl;
    outFile << "End of FIFO List" << std::endl;

    hashTable->printTable();

    std::cout << "\nEnd of cache contents" << std::endl;
    outFile << "\nEnd of cache contents" << std::endl;
}