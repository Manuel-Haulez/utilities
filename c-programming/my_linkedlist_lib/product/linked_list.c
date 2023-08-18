/**
 * @file linked_list.c
 * @author Manuel Haulez
 * @brief Generic doubly linked list implementation
 * @version 0.1 2023-08-10 Initial version
 * @version 0.2 2023-08-18 Fixed prev pointer in ListAddAfterFunction
 * @date 2023-08-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "linked_list.h"

typedef struct node Node;
struct node
{
    void* data;
    Node* prev;
    Node* next;
};

struct list
{
    Node* head;
    Node* lastAccessed;
    int dataSize;
};

/**
 * @brief Constructs a new linked list instance with the specified data size.
 *
 * @param The dataSize of the data elements to be stored in the list.
 * @return List pointer to the newly constructed linked list, or NULL on failure.
 */
List* ListConstruct(int dataSize)
{
    if (dataSize <= 0)
    {
        return NULL;
    }

    List* newList = malloc(dataSize);

    if (newList == NULL)
    {
        return NULL;
    }

    newList->head = NULL;
    newList->lastAccessed = NULL;
    newList->dataSize = dataSize;

    return newList;
}

/**
 * @brief Destructs a linked list instance and frees all associated memory.
 *
 * @param Pointer to a list pointer to the linked list to be destructed.
 * @return Error code indicating the success of the destruction operation.
 */
int ListDestruct(List** thisPtr)
{
    if (*thisPtr == NULL || thisPtr == NULL)
    {
        return -1;
    }

    int returnValue = ListClear(*thisPtr);

    if (returnValue == -1)
    {
        return -1;
    }

    free(*thisPtr);
    *thisPtr = NULL;

    return 0;
}

/**
 * @brief Retrieves the head data of the linked list.
 *
 * @param List pointer to the linked list.
 * @return Void pointer to the data in the head node, or NULL if the list is empty.
 */
void* ListGetHeadData(List* this)
{
    if (this == NULL || this->head == NULL)
    {
        return NULL;
    }

    this->lastAccessed = this->head;

    return this->head->data;
}

/**
 * @brief Retrieves the data stored in the tail node of the linked list.
 *
 * @param List pointer to the linked list.
 * @return Void pointer to the data in the tail node, or NULL if the list is empty.
 */
void* ListGetTailData(List* this)
{
    if (this == NULL || this->head == NULL)
    {
        return NULL;
    }

    Node* currentNode = this->head;

    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }

    this->lastAccessed = currentNode;

    return currentNode->data;
}

/**
 * @brief Retrieves the data stored in the next node of the last accessed node.
 *
 * @param List pointer to the linked list.
 * @return Void pointer to the data in the next node, or NULL if there is no next node.
 */
void* ListGetNextData(List* this)
{
    if (this == NULL || this->head == NULL || this->lastAccessed == NULL)
    {
        return NULL;
    }

    this->lastAccessed = this->lastAccessed->next;

    if (this->lastAccessed == NULL)
    {
        return NULL;
    }

    return this->lastAccessed->data;
}

/**
 * @brief Retrieves the data stored in the previous node of the last accessed node.
 *
 * @param List pointer to the linked list.
 * @return Void pointer to the data in the previous node, or NULL if there is no previous node.
 */
void* ListGetPreviousData(List* this)
{
    if (this == NULL || this->head == NULL || this->lastAccessed == NULL)
    {
        return NULL;
    }

    this->lastAccessed = this->lastAccessed->prev;

    if (this->lastAccessed == NULL)
    {
        return NULL;
    }

    return this->lastAccessed->data;
}

/**
 * @brief Adds a new node with the provided data to the beginning of the linked list.
 *
 * @param List pointer to the linked list.
 * @param Void pointer to the data to be added.
 * @return Error code indicating the success of the operation.
 */
int ListAddHead(List* this, void* data)
{
    if (this == NULL || data == NULL)
    {
        return -1;
    }

    Node* newNode = malloc(sizeof(Node));
    newNode->data = malloc(this->dataSize);

    if (newNode == NULL || newNode->data == NULL)
    {
        return -1;
    }

    memcpy(newNode->data, data, this->dataSize);
    newNode->prev = NULL;
    newNode->next = this->head;
    this->head = newNode;

    if (newNode->next != NULL)
    {
        newNode->next->prev = newNode;
    }

    return 0;
}

/**
 * @brief Adds a new node with the provided data to the end of the linked list.
 *
 * @param List pointer to the linked list.
 * @param Void pointer to the data to be added.
 * @return Error code indicating the success of the operation.
 */
int ListAddTail(List* this, void* data)
{
    if (this == NULL || data == NULL)
    {
        return -1;
    }

    Node* newNode = malloc(sizeof(Node));
    newNode->data = malloc(this->dataSize);

    if (newNode == NULL || newNode->data == NULL)
    {
        return -1;
    }

    memcpy(newNode->data, data, this->dataSize);
    newNode->prev = NULL;
    newNode->next = NULL;

    Node* currentNode = this->head;
    if (currentNode == NULL)
    {
        this->head = newNode;
        return 0;
    }

    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }

    currentNode->next = newNode;
    newNode->prev = currentNode;

    return 0;
}

/**
 * @brief Adds a new node with the provided data before the node containing the reference data.
 *
 * @param List pointer to the linked list.
 * @param Void pointer to the data to be added.
 * @param Void pointer to the reference data.
 * @return Error code indicating the success of the operation.
 */
int ListAddBefore(List* this, void* data, void* refData)
{
    if (this == NULL || this->head == NULL || data == NULL || refData == NULL)
    {
        return -1;
    }

    Node* currentNode = this->head;
    Node* previousNode = NULL;

    while (currentNode->next != NULL && memcmp(currentNode->data, refData, this->dataSize) != 0)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode->next == NULL && memcmp(currentNode->data, refData, this->dataSize) != 0)
    {
        return -1;
    }

    Node* newNode = malloc(sizeof(Node));
    newNode->data = malloc(this->dataSize);

    if (newNode == NULL || newNode->data == NULL)
    {
        return -1;
    }

    memcpy(newNode->data, data, this->dataSize);
    newNode->prev = NULL;

    newNode->next = currentNode;
    if (previousNode == NULL)
    {
        this->head = newNode;
        return 0;
    }

    previousNode->next = newNode;
    newNode->prev = previousNode;
    currentNode->prev = newNode;
    
    return 0;
}

/**
 * @brief Adds a new node with the provided data after the node containing the reference data.
 *
 * @param List pointer to the linked list.
 * @param Void pointer to the data to be added.
 * @param Void pointer to the reference data.
 * @return Error code indicating the success of the operation.
 */
int ListAddAfter(List* this, void* data, void* refData)
{
    if (this == NULL || this->head == NULL || data == NULL || refData == NULL)
    {
        return -1;
    }

    Node* currentNode = this->head;
    Node* previousNode = currentNode;

    while (currentNode != NULL && memcmp(previousNode->data, refData, this->dataSize) != 0)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == NULL && memcmp(previousNode->data, refData, this->dataSize) != 0)
    {
        return -1;
    }

    Node* copyNode = NULL;
    Node* newNode = malloc(sizeof(Node));
    newNode->data = malloc(this->dataSize);

    if (newNode == NULL || newNode->data == NULL)
    {
        return -1;
    }

    memcpy(newNode->data, data, this->dataSize);

    copyNode = previousNode->next;
    previousNode->next = newNode;
    newNode->next = copyNode;
    newNode->prev = previousNode;

    if (copyNode != NULL)
    {
        copyNode->prev = newNode;
    }

    return 0;
}

/**
 * @brief Removes the head node from the linked list.
 *
 * @param List pointer to the linked list.
 * @return Error code indicating the success of the operation.
 */
int ListRemoveHead(List* this)
{
    if (this == NULL || this->head == NULL)
    {
        return -1;
    }

    Node* currentNode = this->head;
    Node* temp = currentNode->next;

    free(currentNode->data);
    free(currentNode);

    this->head = temp;

    if (temp != NULL)
    {
        temp->prev = NULL;
    }

    return 0;
}

/**
 * @brief Removes the tail node from the linked list.
 *
 * @param List pointer to the linked list.
 * @return Error code indicating the success of the operation.
 */
int ListRemoveTail(List* this)
{
    if (this == NULL || this->head == NULL)
    {
        return -1;
    }

    Node* currentNode = this->head;
    Node* previousNode = NULL;

    while (currentNode->next != NULL)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    free(currentNode->data);
    free(currentNode);

    if (previousNode == NULL)
    {
        this->head = NULL;
        return 0;
    }
    previousNode->next = NULL;

    return 0;
}

/**
 * @brief Removes the first node containing the reference data from the linked list.
 *
 * @param List pointer to the linked list.
 * @param Void pointer to the reference data.
 * @return Error code indicating the success of the operation.
 */
int ListRemove(List* this, void* refData)
{
    if (this == NULL || this->head == NULL || refData == NULL)
    {
        return -1;
    }

    Node* currentNode = this->head;
    Node* previousNode = NULL;
    Node* temp = NULL;

    while (currentNode != NULL && memcmp(currentNode->data, refData, this->dataSize) != 0)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == NULL)
    {
        return -1;
    }

    if (currentNode == this->lastAccessed)
    {
        this->lastAccessed = NULL;
    }

    temp = currentNode->next;
    free(currentNode->data);
    free(currentNode);

    if (previousNode == NULL)
    {
        this->head = temp;
    }
    else
    {
        previousNode->next = temp;
    }

    if (temp != NULL)
    {
        temp->prev = previousNode;
    }

    return 0;
}

/**
 * @brief Clears all nodes and associated memory from the linked list, leaving an empty list.
 *
 * @param List pointer to the linked list.
 * @return Error code indicating the success of the operation.
 */
int ListClear(List* this)
{
    if (this == NULL)
    {
        return -1;
    }

    while (this->head != NULL)
    {
        ListRemoveHead(this);
    }

    return 0;
}