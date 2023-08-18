/**
 * @file linked_list.h
 * @author Manuel Haulez
 * @brief Generic doubly linked list implementation
 * @version 0.1 2023-08-10 Initial version
 * @version 0.2 2023-08-18 Finalised unit tests
 * @date 2023-08-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <string.h>

typedef struct list List;

List* ListConstruct(int dataSize);
int ListDestruct(List**);

void* ListGetHeadData(List*);
void* ListGetTailData(List*);
void* ListGetNextData(List*);
void* ListGetPreviousData(List*);

int ListAddHead(List*, void* data);
int ListAddTail(List*, void* data);
int ListAddBefore(List*, void* data, void* refData);
int ListAddAfter(List*, void* data, void* refData);

int ListRemoveHead(List*);
int ListRemoveTail(List*);
int ListRemove(List*, void* refData);
int ListClear(List*);

#endif