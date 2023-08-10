#include "linked_list.h"

typedef struct node Node;
struct node
{
    void *data;
    Node *previous;
    Node *next;
};

struct list
{
    Node *head;
    Node *lastAccessed;
    int dataSize;
};

List *ListConstruct(int dataSize)
{
    if (dataSize <= 0)
    {
        return NULL;
    }

    List *newList = malloc(dataSize);

    if (newList == NULL)
    {
        return NULL;
    }

    newList->head = NULL;
    newList->lastAccessed = NULL;
    newList->dataSize = dataSize;

    return newList;
}

int ListDestruct(List **thisPtr)
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

void *ListGetHeadData(List *this)
{
    if (this == NULL || this->head == NULL)
    {
        return NULL;
    }

    this->lastAccessed = this->head;

    return this->head->data;
}

void *ListGetTailData(List *this)
{
    if (this == NULL || this->head == NULL)
    {
        return NULL;
    }

    Node *currentNode = this->head;

    while (currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }

    this->lastAccessed = currentNode;

    return currentNode->data;
}

void *ListGetNextData(List *this)
{
    if (this == NULL || this->head == NULL)
    {
        return NULL;
    }

    if (this->lastAccessed == NULL)
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

void *ListGetPreviousData(List *this)
{
    if (this == NULL || this->head == NULL)
    {
        return NULL;
    }

    if (this->lastAccessed == NULL)
    {
        this->lastAccessed = this->head;
        return this->head->data;
    }

    this->lastAccessed = this->lastAccessed->previous;

    if (this->lastAccessed == NULL)
    {
        return NULL;
    }

    return this->lastAccessed->data;
}

int ListAddHead(List *this, void *data)
{
    if (this == NULL || data == NULL)
    {
        return -1;
    }

    Node *newNode = malloc(sizeof(Node));
    newNode->data = malloc(this->dataSize);

    if (newNode == NULL || newNode->data == NULL)
    {
        return -1;
    }

    memcpy(newNode->data, data, this->dataSize);
    newNode->previous = NULL;
    newNode->next = this->head;

    this->head = newNode;

    if (newNode->next != NULL)
    {
        newNode->next->previous = newNode;
    }

    return 0;
}

int ListAddTail(List *this, void *data)
{
    if (this == NULL || data == NULL)
    {
        return -1;
    }

    Node *newNode = malloc(sizeof(Node));
    newNode->data = malloc(this->dataSize);

    if (newNode == NULL || newNode->data == NULL)
    {
        return -1;
    }

    memcpy(newNode->data, data, this->dataSize);
    newNode->previous = NULL;
    newNode->next = NULL;

    Node *currentNode = this->head;
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
    newNode->previous = currentNode;

    return 0;
}

int ListAddBefore(List *this, void *data, void *refData)
{
    if (this == NULL || this->head == NULL || data == NULL || refData == NULL)
    {
        return -1;
    }

    Node *currentNode = this->head;
    Node *previousNode = NULL;

    while (currentNode->next != NULL && memcmp(currentNode->data, refData, this->dataSize) != 0)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode->next == NULL && memcmp(currentNode->data, refData, this->dataSize) != 0)
    {
        return -1;
    }

    Node *newNode = malloc(sizeof(Node));
    newNode->data = malloc(this->dataSize);

    if (newNode == NULL || newNode->data == NULL)
    {
        return -1;
    }

    memcpy(newNode->data, data, this->dataSize);
    newNode->previous = NULL;

    newNode->next = currentNode;
    if (previousNode == NULL)
    {
        this->head = newNode;
        return 0;
    }

    previousNode->next = newNode;
    newNode->previous = previousNode;
    currentNode->previous = newNode;
    
    return 0;
}

int ListAddAfter(List *this, void *data, void *refData)
{
    if (this == NULL || this->head == NULL || data == NULL || refData == NULL)
    {
        return -1;
    }

    Node *currentNode = this->head;
    Node *previousNode = currentNode;

    while (currentNode != NULL && memcmp(previousNode->data, refData, this->dataSize) != 0)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == NULL && memcmp(previousNode->data, refData, this->dataSize) != 0)
    {
        return -1;
    }

    Node *copyNode = NULL;
    Node *newNode = malloc(sizeof(Node));
    newNode->data = malloc(this->dataSize);

    if (newNode == NULL || newNode->data == NULL)
    {
        return -1;
    }

    memcpy(newNode->data, data, this->dataSize);

    copyNode = previousNode->next;
    previousNode->next = newNode;
    newNode->next = copyNode;

    if (copyNode != NULL)
    {
        copyNode->previous = newNode;
    }

    return 0;
}

int ListRemoveHead(List *this)
{
    if (this == NULL || this->head == NULL)
    {
        return -1;
    }

    Node *currentNode = this->head;
    Node *temp = currentNode->next;

    free(currentNode->data);
    free(currentNode);

    this->head = temp;

    if (temp != NULL)
    {
        temp->previous = NULL;
    }

    return 0;
}

int ListRemoveTail(List *this)
{
    if (this == NULL || this->head == NULL)
    {
        return -1;
    }

    Node *currentNode = this->head;
    Node *previousNode = NULL;

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

int ListRemove(List *this, void *refData)
{
    if (this == NULL || this->head == NULL || refData == NULL)
    {
        return -1;
    }

    Node *currentNode = this->head;
    Node *previousNode = NULL;
    Node *temp = NULL;

    while (currentNode != NULL && memcmp(currentNode->data, refData, this->dataSize) != 0)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == NULL)
    {
        return -1;
    }
    
    if (previousNode->next == this->lastAccessed)
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
        temp->previous = previousNode;
    }

    return 0;
}

int ListClear(List *this)
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