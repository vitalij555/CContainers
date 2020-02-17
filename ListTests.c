#include <stdint.h>

#include "unity_fixture.h"
#include "containerMemory.h"

#include "List.h"




static HList listWithIntegers;
#define LIST_INT_FILLED_SIZE 5


TEST_GROUP(List);


TEST_SETUP(List)
{
   listWithIntegers = listCreate(sizeof(int));
}


TEST_TEAR_DOWN(List)
{
   listFree(&listWithIntegers);
}



TEST_GROUP_RUNNER(List)
{
  {RUN_TEST_CASE(List, listInit_Ok);}
  {RUN_TEST_CASE(List, getSize_Ok);}
  {RUN_TEST_CASE(List, listPushToEnd_Ok);}
  {RUN_TEST_CASE(List, listPushFront_Ok);}
  {RUN_TEST_CASE(List, listGetFirstNext_Ok);}

}


TEST(List, listInit_Ok)
{
  HList list = NULL;
  list = listCreate(10);
  TEST_ASSERT_NOT_NULL(list);
  listFree(&list);
 }



TEST(List, getSize_Ok)
{
  int size = 0;
  int data = 1245;

  size = listGetSize(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(0, size);

  listPush(&listWithIntegers, &data);

  size = listGetSize(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(1, size);
 }



TEST(List, listPushToEnd_Ok)
{
  int result = LIST_RESULT_ERROR;
  int data = 1245;
  result = listPush(&listWithIntegers, &data);
  TEST_ASSERT_EQUAL_INT(LIST_RESULT_OK, result);
 }



TEST(List, listPushFront_Ok)
{
  void* dataOut = NULL;
  int result = LIST_RESULT_ERROR;
  int data = 19876;

  result = listPushFront(&listWithIntegers, &data);
  TEST_ASSERT_EQUAL_INT(LIST_RESULT_OK, result);
  data = 59;
  result = listPushFront(&listWithIntegers, &data);
  TEST_ASSERT_EQUAL_INT(LIST_RESULT_OK, result);
  data = 120;
  result = listPush(&listWithIntegers, &data);
  TEST_ASSERT_EQUAL_INT(LIST_RESULT_OK, result);

  dataOut = listGetFirst(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(59, *(int*)dataOut);
  memoryFree((void**)&dataOut);

  dataOut = listGetNext(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(19876, *(int*)dataOut);
  memoryFree((void**)&dataOut);

  dataOut = listGetNext(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(120, *(int*)dataOut);
  memoryFree((void**)&dataOut);
 }



TEST(List, listGetFirstNext_Ok)
{
  void* dataOut = NULL;
  int data = 1245;
  listPush(&listWithIntegers, &data);
  data = 1515;
  listPush(&listWithIntegers, &data);
  data = 8;
  listPush(&listWithIntegers, &data);

  dataOut = listGetFirst(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(1245, *(int*)dataOut);
  memoryFree((void**)&dataOut);

  dataOut = listGetNext(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(1515, *(int*)dataOut);
  memoryFree((void**)&dataOut);

  dataOut = listGetNext(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(8, *(int*)dataOut);
  memoryFree((void**)&dataOut);

  dataOut = listGetNext(&listWithIntegers);
  TEST_ASSERT_NULL(dataOut);

  dataOut = listGetFirst(&listWithIntegers);
  TEST_ASSERT_EQUAL_INT(1245, *(int*)dataOut);
  memoryFree((void**)&dataOut);
 }


