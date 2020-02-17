#include <stdint.h>

#include "unity_fixture.h"
#include "containerMemory.h"

#include "List.h"



TEST_GROUP(List);


TEST_SETUP(List)
{

 }



TEST_TEAR_DOWN(List)
{

}



TEST(List, listInit_Ok)
{
  HList list = NULL;
  list = listCreate(10);
  TEST_ASSERT_NOT_NULL(list);
  listFree(&list);
 }


TEST_GROUP_RUNNER(List)
{
  {RUN_TEST_CASE(List, listInit_Ok);}
}

