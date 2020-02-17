
/*
 * Tests.c
 *
 *  Created on: 2011.09.12
 *      Author: Vitalij
 */

#include "TestRunner.h"
#include "unity_fixture.h"


//############################################################################

//void putchar(char ch)
//{
//   printf("%c", ch);
//}

//############################################################################


static void RunAllTests()
{
   {RUN_TEST_GROUP(List);}
}

//############################################################################

int TestsEntryPoint(const char* argv[])
{
   return UnityMain(0, argv, RunAllTests);
}

//############################################################################
