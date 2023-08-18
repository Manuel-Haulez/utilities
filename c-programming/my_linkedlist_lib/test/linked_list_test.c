#include "unity.h"
#include "linked_list.h"

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

static List* myList = NULL;

typedef struct element Element;
struct element
{
    int address;
};

void setUp(void)
{
    myList = ListConstruct(sizeof(Element));
}

void tearDown(void)
{
    ListDestruct(&myList);
}

// ListConstruct
void testListConstruct(void)
{
    List* newList = ListConstruct(sizeof(Element));
    TEST_ASSERT_NOT_NULL(newList)

    ListDestruct(&newList);
    TEST_ASSERT_NULL(newList);
}

void testListConstruct_WhenDataSizeIsZero_ReturnNULL(void)
{
    List* newList = ListConstruct(0);
    TEST_ASSERT_NULL(newList)

    ListDestruct(&newList);
    TEST_ASSERT_NULL(newList);
}

void testListConstruct_WhenDataSizeIsLessThenZero_ReturnNULL(void)
{
    List* newList = ListConstruct(-5);
    TEST_ASSERT_NULL(newList)

    ListDestruct(&newList);
    TEST_ASSERT_NULL(newList);
}

//ListDestruct
void testListDestruct(void)
{
    List* newList = ListConstruct(sizeof(Element));
    TEST_ASSERT_NOT_NULL(newList)

    TEST_ASSERT_EQUAL_INT(0, ListDestruct(&newList));
    TEST_ASSERT_NULL(newList)
}

void testListDestruct_WhenListIsNULL_Return(void)
{
    List* newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListDestruct(&newList));
    TEST_ASSERT_NULL(newList);
}

void testListDestruct_WhenListIsFilled(void)
{
    Element a = {1};
    Element b = {2};

    List* newList = ListConstruct(sizeof(Element));

    ListAddTail(newList, &a);
    ListAddTail(newList, &b);

    TEST_ASSERT_EQUAL_INT(0, ListDestruct(&newList));
    TEST_ASSERT_NULL(newList);
}

//ListGetHeadData
void testListGetHeadData(void)
{
    Element a = {720};
    Element b = {7000};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(720, elementPtr->address);
}

void testListGetHeadData_WhenListIsNULL_ReturnNULL(void)
{
    List* newList = NULL;
    Element* elementPtr = ListGetHeadData(newList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetHeadData_WhenListIsEmpty_ReturnNULL(void)
{
    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

//ListGetTailData
void testListGetTailData(void)
{
    Element a = {1};
    Element b = {2};
    Element c = {3};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);

    Element* elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(3, elementPtr->address);
}

void testListGetTailData_WhenListIsNULL_ReturnNULL(void)
{
    List* newList = NULL;

    Element* elementPtr = ListGetTailData(newList);
    TEST_ASSERT_NULL(elementPtr);
    ListDestruct(&newList);
}

void testListGetTailData_WhenListIsEmpty_ReturnNULL(void)
{
    Element* elementPtr = ListGetTailData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

//ListGetNextData
void testListGetNextData(void)
{
    Element a = {1};
    Element b = {2};
    Element c = {3};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL(1, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL(2, elementPtr->address);

    elementPtr = ListGetNextData(myList);

    TEST_ASSERT_EQUAL(3, elementPtr->address);
    
    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetNextData_WhenListIsNULL_ReturnNULL(void)
{
    List* newList = NULL;
    Element* elementPtr = ListGetNextData(newList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetNextData_WhenListIsEmpty_ReturnNULL(void)
{
    Element* elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetNextData_WhenFirstDataIsRequested_ReturnNULL(void)
{
    Element a = {20};

    ListAddTail(myList, &a);
    Element* elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetNextData_WhenDataIsAdded_NextDataIsReturned(void)
{
    Element a = {20};
    Element b = {240};

    ListAddTail(myList, &a);

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL(20, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);

    ListAddTail(myList, &b);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetNextData_WhenLastAccessedIsDeleted_ReturnNULL(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {360};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    ListRemove(myList, &b);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

//ListGetPreviousData
void testListGetPreviousData(void)
{
    Element a = {1};
    Element b = {2};
    Element c = {3};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);

    Element* elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL(3, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL(2, elementPtr->address);
    
    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL(1, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetPreviousData_WhenListIsNULL_ReturnNULL(void)
{
    List* newList = NULL;
    Element* elementPtr = ListGetPreviousData(newList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetPreviousData_WhenListIsEmpty_ReturnNULL(void)
{
    Element* elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetPreviousData_WhenFirstDataIsRequested_ReturnNULL(void)
{
    Element a = {20};

    ListAddTail(myList, &a);
    Element* elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetPreviousData_WhenDataIsAdded_PreviousDataIsReturned(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {360};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);

    Element* elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    ListAddHead(myList, &c);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(360, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetPreviousData_WhenLastAccessedIsDeleted_ReturnNULL(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {360};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);

    Element* elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(360, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    ListRemove(myList, &a);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

//ListAddHead
void testListAddHead(void)
{
    Element a = {20};
    Element b = {240};

    ListAddTail(myList, &a);

    TEST_ASSERT_EQUAL_INT(0, ListAddHead(myList, &b));

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);

    ListGetHeadData(myList);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);
    
    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListAddHead_WhenListIsNULL_Return(void)
{
    Element a = {20};
    List* newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListAddHead(newList, &a));
}

void testListAddHead_WhenDataIsNULL_Return(void)
{
    TEST_ASSERT_EQUAL_INT(-1, ListAddHead(myList, NULL));
    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListAddHead_WhenListIsEmpty_AddNodeToFrontOfList(void)
{
    Element a = {20};
    ListAddHead(myList, &a);

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);

    ListGetHeadData(myList);
    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

//ListAddTail
void testListAddTail(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddHead(myList, &a);
    ListAddHead(myList, &b);
    
    TEST_ASSERT_EQUAL_INT(0, ListAddTail(myList, &c));

    Element* elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);

    ListGetTailData(myList);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);
}

void testListAddTail_WhenListIsNULL_Return(void)
{
    Element a = {20};
    List* newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListAddTail(newList, &a));
}

void testListAddTail_WhenDataIsNULL_Return(void)
{
    TEST_ASSERT_EQUAL_INT(-1, ListAddTail(myList, NULL));
    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListAddTail_WhenListIsEmpty_AddNodeToEndOfList(void)
{
    Element a = {20};
    ListAddTail(myList, &a);

    Element* elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);

    ListGetHeadData(myList);
    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

//ListAddBefore
void testListAddBefore(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    TEST_ASSERT_EQUAL_INT(0, ListAddBefore(myList, &c, &b));
    
    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);
    
    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);

    elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListAddBefore_WhenListIsNULL_Return(void)
{
    Element a = {20};
    Element b = {240};

    List* newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListAddBefore(newList, &a, &b));
}

void testListAddBefore_WhenDataIsNULL_Return(void)
{
    Element a = {20};
    ListAddTail(myList, &a);
    TEST_ASSERT_EQUAL_INT(-1, ListAddBefore(myList, NULL, &a));
}

void testListAddBefore_WhenRefDataIsNULL_Return(void)
{
    Element a = {20};
    Element b = {240};
    ListAddHead(myList, &a);
    TEST_ASSERT_EQUAL_INT(-1, ListAddBefore(myList, &b, NULL));
}

void testListAddBefore_WhenRefDataIsNotFound_Return(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddTail(myList, &a);
    TEST_ASSERT_EQUAL_INT(-1, ListAddBefore(myList, &c, &b));
}

void testListAddBefore_WhenRefDataIsFirstNode_AddNodeToFrontOfList(void)
{
    Element a = {20};
    Element b = {240};

    ListAddTail(myList, &a);
    TEST_ASSERT_EQUAL_INT(0, ListAddBefore(myList, &b, &a));

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);
}

void testListAddBefore_WhenRefDataExist_AddNewNodeBetweenNodes(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    
    TEST_ASSERT_EQUAL_INT(0, ListAddBefore(myList, &c, &b));
    
    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);
}

//ListAddAfter
void testListAddAfter(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    TEST_ASSERT_EQUAL_INT(0, ListAddAfter(myList, &c, &a));
    
    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);
    
    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);

    elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);
    
    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);
    
    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListAddAfter_WhenListIsNULL_Return(void)
{
    Element a = {20};
    Element b = {240};

    List* newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListAddAfter(newList, &a, &b));
}

void testListAddAfter_WhenDataIsNULL_Return(void)
{
    Element a = {20};
    ListAddTail(myList, &a);
    TEST_ASSERT_EQUAL_INT(-1, ListAddAfter(myList, NULL, &a));
}

void testListAddAfter_WhenRefDataIsNULL_Return(void)
{
    Element a = {20};
    Element b = {240};
    ListAddHead(myList, &a);
    TEST_ASSERT_EQUAL_INT(-1, ListAddAfter(myList, &b, NULL));
}

void testListAddAfter_WhenRefDataIsNotFound_Return(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddTail(myList, &a);
    TEST_ASSERT_EQUAL_INT(-1, ListAddAfter(myList, &c, &b));
}

void testListAddAfter_WhenRefDataIsLastNode_AddNodeToEndOfList(void)
{
    Element a = {20};
    Element b = {240};

    ListAddTail(myList, &a);
    TEST_ASSERT_EQUAL_INT(0, ListAddAfter(myList, &b, &a));

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListAddAfter_WhenRefDataExist_AddNewNodeBetweenNodes(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    
    TEST_ASSERT_EQUAL_INT(0, ListAddAfter(myList, &c, &a));
    
    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);
}

//ListRemoveHead
void testListRemoveHead(void)
{
    Element a = {20};
    Element b = {240};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);

    TEST_ASSERT_EQUAL_INT(0, ListRemoveHead(myList));

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);
}

void testListRemoveHead_WhenListIsNULL_Return(void)
{
    List* newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListRemoveHead(newList));
}

void testListRemoveHead_WhenListIsEmpty_Return(void)
{
    TEST_ASSERT_EQUAL_INT(-1, ListRemoveHead(myList));
}

//ListRemoveTail
void testListRemoveTail(void)
{
    Element a = {20};
    Element b = {240};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);

    TEST_ASSERT_EQUAL_INT(0, ListRemoveTail(myList));

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);
    
    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListRemoveTail_WhenListIsNULL_Return(void)
{
    List* newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListRemoveTail(newList));
}

void testListRemoveTail_WhenListIsEmpty_Return(void)
{
    TEST_ASSERT_EQUAL_INT(-1, ListRemoveTail(myList));
}

//ListRemove
void testListRemove(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);

    TEST_ASSERT_EQUAL_INT(0, ListRemove(myList, &b));

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_EQUAL_INT(60, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListRemove_WhenListIsNull_Return(void)
{
    Element a = {20};

    List* newList = NULL;
    ListAddTail(newList, &a);

    TEST_ASSERT_EQUAL_INT(-1, ListRemove(newList, &a));
}

void testListRemove_WhenListIsEmpty_Return(void)
{
    Element a = {20};
    TEST_ASSERT_EQUAL_INT(-1, ListRemove(myList, &a));
}

void testListRemove_WhenRefDataIsNull_Return(void)
{
    Element a = {20};
    ListAddHead(myList, &a);
    TEST_ASSERT_EQUAL_INT(-1, ListRemove(myList, NULL));
}

void testListRemove_WhenRefDataIsNotFound_Return(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    
    TEST_ASSERT_EQUAL_INT(-1, ListRemove(myList, &c));
}

void testListRemove_WhenRefDataIsFirstNode_RemoveNode(void)
{
    Element a = {20};
    Element b = {240};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);

    TEST_ASSERT_EQUAL_INT(0, ListRemove(myList, &a));

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);

    elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(240, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListRemove_WhenRefDataIsLastNode_RemoveNode(void)
{
    Element a = {20};
    Element b = {240};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);

    TEST_ASSERT_EQUAL_INT(0, ListRemove(myList, &b));

    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);

    elementPtr = ListGetTailData(myList);
    TEST_ASSERT_EQUAL_INT(20, elementPtr->address);

    elementPtr = ListGetPreviousData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

//ListClear
void testListClear(void)
{
    Element a = {20};
    Element b = {240};
    Element c = {60};
    Element d = {760};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);
    ListAddTail(myList, &d);

    TEST_ASSERT_EQUAL_INT(0, ListClear(myList));
    
    Element* elementPtr = ListGetHeadData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListClear_WhenListIsNull_Return(void)
{
    List* newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListClear(newList));
}

void testListClear_WhenListIsEmpty()
{
    TEST_ASSERT_EQUAL_INT(0, ListClear(myList));
}

int main()
{
    UnityBegin();

    // ListConstruct
    MY_RUN_TEST(testListConstruct);
    MY_RUN_TEST(testListConstruct_WhenDataSizeIsZero_ReturnNULL);
    MY_RUN_TEST(testListConstruct_WhenDataSizeIsLessThenZero_ReturnNULL);

    //ListDestruct
    MY_RUN_TEST(testListDestruct);
    MY_RUN_TEST(testListDestruct_WhenListIsNULL_Return);
    MY_RUN_TEST(testListDestruct_WhenListIsFilled);
    
    //ListGetHeadData
    MY_RUN_TEST(testListGetHeadData);
    MY_RUN_TEST(testListGetHeadData_WhenListIsNULL_ReturnNULL);
    MY_RUN_TEST(testListGetHeadData_WhenListIsEmpty_ReturnNULL);

    //ListGetTailData
    MY_RUN_TEST(testListGetTailData);
    MY_RUN_TEST(testListGetTailData_WhenListIsNULL_ReturnNULL);
    MY_RUN_TEST(testListGetTailData_WhenListIsEmpty_ReturnNULL);

    //ListGetNextData
    MY_RUN_TEST(testListGetNextData);
    MY_RUN_TEST(testListGetNextData_WhenListIsNULL_ReturnNULL);
    MY_RUN_TEST(testListGetNextData_WhenListIsEmpty_ReturnNULL);
    MY_RUN_TEST(testListGetNextData_WhenFirstDataIsRequested_ReturnNULL);
    MY_RUN_TEST(testListGetNextData_WhenDataIsAdded_NextDataIsReturned);
    MY_RUN_TEST(testListGetNextData_WhenLastAccessedIsDeleted_ReturnNULL);

    //ListGetPreviousData
    MY_RUN_TEST(testListGetPreviousData);
    MY_RUN_TEST(testListGetPreviousData_WhenListIsNULL_ReturnNULL);
    MY_RUN_TEST(testListGetPreviousData_WhenListIsEmpty_ReturnNULL);
    MY_RUN_TEST(testListGetPreviousData_WhenFirstDataIsRequested_ReturnNULL);
    MY_RUN_TEST(testListGetPreviousData_WhenDataIsAdded_PreviousDataIsReturned);
    MY_RUN_TEST(testListGetPreviousData_WhenLastAccessedIsDeleted_ReturnNULL);

    //ListAddHead
    MY_RUN_TEST(testListAddHead);
    MY_RUN_TEST(testListAddHead_WhenListIsNULL_Return);
    MY_RUN_TEST(testListAddHead_WhenDataIsNULL_Return);
    MY_RUN_TEST(testListAddHead_WhenListIsEmpty_AddNodeToFrontOfList);

    //ListAddTail
    MY_RUN_TEST(testListAddTail);
    MY_RUN_TEST(testListAddTail_WhenListIsNULL_Return);
    MY_RUN_TEST(testListAddTail_WhenDataIsNULL_Return);
    MY_RUN_TEST(testListAddTail_WhenListIsEmpty_AddNodeToEndOfList);

    //ListAddBefore
    MY_RUN_TEST(testListAddBefore);
    MY_RUN_TEST(testListAddBefore_WhenListIsNULL_Return);
    MY_RUN_TEST(testListAddBefore_WhenDataIsNULL_Return);
    MY_RUN_TEST(testListAddBefore_WhenRefDataIsNULL_Return);
    MY_RUN_TEST(testListAddBefore_WhenRefDataIsNotFound_Return);
    MY_RUN_TEST(testListAddBefore_WhenRefDataIsFirstNode_AddNodeToFrontOfList);
    MY_RUN_TEST(testListAddBefore_WhenRefDataExist_AddNewNodeBetweenNodes);

    //ListAddAfter
    MY_RUN_TEST(testListAddAfter);
    MY_RUN_TEST(testListAddAfter_WhenListIsNULL_Return);
    MY_RUN_TEST(testListAddAfter_WhenDataIsNULL_Return);
    MY_RUN_TEST(testListAddAfter_WhenRefDataIsNULL_Return);
    MY_RUN_TEST(testListAddAfter_WhenRefDataIsNotFound_Return);
    MY_RUN_TEST(testListAddAfter_WhenRefDataIsLastNode_AddNodeToEndOfList);
    MY_RUN_TEST(testListAddAfter_WhenRefDataExist_AddNewNodeBetweenNodes);

    //ListRemoveHead
    MY_RUN_TEST(testListRemoveHead);
    MY_RUN_TEST(testListRemoveHead_WhenListIsNULL_Return);
    MY_RUN_TEST(testListRemoveHead_WhenListIsEmpty_Return);
    
    //ListRemoveTail
    MY_RUN_TEST(testListRemoveTail);
    MY_RUN_TEST(testListRemoveTail_WhenListIsNULL_Return);
    MY_RUN_TEST(testListRemoveTail_WhenListIsEmpty_Return);

    //ListRemove
    MY_RUN_TEST(testListRemove);
    MY_RUN_TEST(testListRemove_WhenListIsNull_Return);
    MY_RUN_TEST(testListRemove_WhenListIsEmpty_Return);
    MY_RUN_TEST(testListRemove_WhenRefDataIsNull_Return);
    MY_RUN_TEST(testListRemove_WhenRefDataIsNotFound_Return);
    MY_RUN_TEST(testListRemove_WhenRefDataIsFirstNode_RemoveNode);
    MY_RUN_TEST(testListRemove_WhenRefDataIsLastNode_RemoveNode);
    
    //ListClear
    MY_RUN_TEST(testListClear);
    MY_RUN_TEST(testListClear_WhenListIsNull_Return);
    MY_RUN_TEST(testListClear_WhenListIsEmpty);

    return UnityEnd();
}
