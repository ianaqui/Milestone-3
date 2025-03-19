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
    if (contains(curKey)) {
        remove(curKey);
    }

    if (doublyLinkedList->getSize() >= maxCacheSize) {
        if (!doublyLinkedList->isEmpty()) {
            DllNode* oldestNode = doublyLinkedList->tail;
            if (oldestNode != nullptr) {
                int oldestKey = oldestNode->key;
                remove(oldestKey);
                logToFileAndConsole("Cache is full. Removed oldest entry with key: " + std::to_string(oldestKey));
            }
        }
    }

    HashNode* newHashNode = new HashNode(curKey, myNode);
    hashTable->add(curKey, newHashNode);
    doublyLinkedList->insertAtHead(curKey, myNode);

    return true;
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
    HashNode* hashNode = hashTable->getItem(curKey);
    if (hashNode == nullptr) {
        return false;
    }

    doublyLinkedList->remove(curKey);
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
    logToFileAndConsole("\n\nPrinting out the cache contents\n");

    logToFileAndConsole("Here are the FIFO List contents: ");
    DllNode* current = doublyLinkedList->head;
    while (current != nullptr) {
        logToFileAndConsole("FIFO Node key: " + std::to_string(current->key) + " ");
        current = current->next;
    }
    logToFileAndConsole("End of FIFO List\n");

    hashTable->printTable();

    logToFileAndConsole("\nEnd of cache contents\n");
}