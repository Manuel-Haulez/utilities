#include "unity.h"
#include "linked_list.h"

#define MY_RUN_TEST(func) RUN_TEST(func, 0)

static List *myList = NULL;

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

void testListConstruct(void)
{
    List *newList = ListConstruct(sizeof(Element));
    TEST_ASSERT_NOT_NULL(newList)

    ListDestruct(&newList);
    TEST_ASSERT_NULL(newList);
}

void testListConstruct_WhenDataSizeIsZero_ReturnNULL(void)
{
    List *newList = ListConstruct(0);
    TEST_ASSERT_NULL(newList)

    ListDestruct(&newList);
    TEST_ASSERT_NULL(newList);
}

void testListConstruct_WhenDataSizeIsLessThenZero_ReturnNULL(void)
{
    List *newList = ListConstruct(-5);
    TEST_ASSERT_NULL(newList)

    ListDestruct(&newList);
    TEST_ASSERT_NULL(newList);
}

void testListDestruct(void)
{
    List *newList = ListConstruct(sizeof(Element));
    TEST_ASSERT_NOT_NULL(newList)

    ListDestruct(&newList);
    TEST_ASSERT_NULL(newList)
}

void testListDestruct_WhenListIsNULL_Return(void)
{
    List *newList = NULL;
    TEST_ASSERT_EQUAL_INT(-1, ListDestruct(&newList));
    TEST_ASSERT_NULL(newList);
}

void testListDestruct_WhenListIsFilled(void)
{
    Element a = {1};
    Element b = {2};

    List *newList = ListConstruct(sizeof(Element));

    ListAddTail(newList, &a);
    ListAddTail(newList, &b);

    TEST_ASSERT_EQUAL_INT(0, ListDestruct(&newList));
    TEST_ASSERT_NULL(newList);
}

void testListGetHeadData(void)
{
    Element a = {1};

    ListAddTail(myList, &a);

    Element* firstElement = ListGetHeadData(myList);

    TEST_ASSERT_EQUAL_INT(1, firstElement->address);
}

void testListGetHeadData_WhenListIsNULL_ReturnNULL(void)
{
    List *newList = NULL;

    Element* firstElement = ListGetHeadData(newList);

    TEST_ASSERT_NULL(firstElement);
    ListDestruct(&newList);
}

void testListGetHeadData_WhenListIsEmpty_ReturnNULL(void)
{
    Element* firstElement = ListGetHeadData(myList);
    TEST_ASSERT_NULL(firstElement);
}

void testListGetTailData(void)
{
    Element a = {1};
    Element b = {2};
    Element c = {3};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);

    Element* firstElement = ListGetTailData(myList);

    TEST_ASSERT_EQUAL_INT(3, firstElement->address);
}

void testListGetTailData_WhenListIsNULL_ReturnNULL(void)
{
    List *newList = NULL;

    Element* firstElement = ListGetTailData(newList);

    TEST_ASSERT_NULL(firstElement);
    ListDestruct(&newList);
}

void testListGetTailData_WhenListIsEmpty_ReturnNULL(void)
{
    Element* firstElement = ListGetTailData(myList);
    TEST_ASSERT_NULL(firstElement);
}

void testListGetNextData(void)
{
    Element a = {1};
    Element b = {2};
    Element c = {3};

    ListAddTail(myList, &a);
    ListAddTail(myList, &b);
    ListAddTail(myList, &c);

    Element* elementPtr = ListGetHeadData(myList);
    elementPtr = ListGetNextData(myList);
    elementPtr = ListGetNextData(myList);

    TEST_ASSERT_EQUAL(3, elementPtr->address);
    
    elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetNextData_WhenListIsNULL_ReturnNULL(void)
{
    List *newList = NULL;

    Element* firstElement = ListGetNextData(newList);

    TEST_ASSERT_NULL(firstElement);
    ListDestruct(&newList);
}

void testListGetNextData_WhenListIsEmpty_ReturnNULL(void)
{
    Element* elementPtr = ListGetNextData(myList);
    TEST_ASSERT_NULL(elementPtr);
}

void testListGetNextData_WhenFirstDataIsAdded_HeadIsReturned(void)
{
    Element a = {1};

    ListAddTail(myList, &a);
    Element* elementPtr = ListGetNextData(myList);

    TEST_ASSERT_EQUAL_INT(1, elementPtr->address);
}

// void testListGetNextData_WhenDataIsAdded_NextDataIsReturned(void)
// {
//     Element a = {1};
//     Element b = {2};

//     ListAddTail(myList, &a);
//     ListAddTail(myList, &b);

//     Element* elementPtr = ListGetHeadData(myList);
//     elementPtr = ListGetNextData(myList);

//     TEST_ASSERT_EQUAL_INT(2, elementPtr->address);

//     elementPtr = ListGetNextData(myList);
//     TEST_ASSERT_NULL(elementPtr);
// }

// void testListGetNextData_WhenLastAccessedIsDeleted_ReturnNULL(void)
// {
//     Element a = {1};
//     Element b = {2};

//     ListAddTail(myList, &a);
//     ListAddTail(myList, &b);

//     Element* elementPtr = ListGetHeadData(myList);
//     elementPtr = ListGetNextData(myList);

//     TEST_ASSERT_EQUAL_INT(2, elementPtr->address);
//     ListRemove(myList, &b);

//     elementPtr = ListGetNextData(myList);
//     TEST_ASSERT_EQUAL_INT(1, elementPtr->address);
//     //TEST_ASSERT_NULL(elementPtr);
// }

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
    MY_RUN_TEST(testListGetNextData_WhenFirstDataIsAdded_HeadIsReturned);
    //MY_RUN_TEST(testListGetNextData_WhenDataIsAdded_NextDataIsReturned);
    //MY_RUN_TEST(testListGetNextData_WhenLastAccessedIsDeleted_ReturnNULL);

    //ListGetPreviousData

    //ListAddHead

    //ListAddTail

    //ListAddBefore

    //ListAddAfter

    //ListRemoveHead

    //ListRemoveTail

    //ListRemove

    //ListClear
    

    return UnityEnd();
}
