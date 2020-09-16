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
  {RUN_TEST_CASE(List, motivationCodeTest_Ok);}
  {RUN_TEST_CASE(List, motivation2CodeTest_Ok);}
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



TEST(List, motivationCodeTest_Ok)
{
	int data = 1000;
	int data2 = 2000;
	int* dataOut = 0;
	int* dataOut2 = 0;
	HList list = listCreate(sizeof(int));

	listPush(&list, &data);
	listPush(&list, &data2);

	dataOut = listGetFirst(&list); 
	dataOut2 = listGetNext(&list);  

  TEST_ASSERT_EQUAL_INT(1000, *(int*)dataOut);
  TEST_ASSERT_EQUAL_INT(2000, *(int*)dataOut2);

	memoryFree((void**)&dataOut);   // Frees our first integer
	memoryFree((void**)&dataOut2);  // Frees our second integer
	listFree(&list); // Frees the list and all elements left in it

  TEST_ASSERT_NULL(dataOut);
  TEST_ASSERT_NULL(dataOut2);
  TEST_ASSERT_NULL(list);
}



#define MEDIUM_STRING 64
#define LONG_STRING 128
// Test without assertions - just to be sure it compiles and prints results
TEST(List, motivation2CodeTest_Ok)
{
    typedef struct 
    {
       char country[MEDIUM_STRING];
       char city[MEDIUM_STRING];
       char street[LONG_STRING];   
       int houseNumber;
       int flat; 
       char zip[6];        
    }Address;

  Address address1 = {"Lithuania", "Vilnius", "Zirmunu", 525, 15, "09127"};
  Address address2 = {"Czech Republic", "Praha", "Resslova", 1939, 7, "2"};
  Address address3 = {"Belgium", "Brussels", "Atomiumplein", 1, 1, "B-1020"};


	HList list = listCreate(sizeof(Address));

	listPush(&list, &address1);
	listPush(&list, &address2);
  listPush(&list, &address3);

  Address* addressOut = NULL;
	addressOut = listGetFirst(&list);
  while (addressOut)
  {
    printf("\n####################\n\nCountry:%s\nCity:%s\nStreet:%s\nNr.: %d-%d  %s", 
              addressOut->country, 
              addressOut->city, 
              addressOut->street, 
              addressOut->houseNumber, 
              addressOut->flat, 
              addressOut->zip);

    memoryFree((void**)&addressOut); 
    addressOut = listGetNext(&list);
  }

 listFree(&list); // Frees the list and all elements left in it (if any)
}