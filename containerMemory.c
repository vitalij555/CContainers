#include <string.h>
#include <stdlib.h>

#include "containerMemory.h"


//########################################################################################

int min(unsigned int d1, unsigned int d2) {
  return d1 < d2 ? d1 : d2;
}

//########################################################################################

void* memoryAlloc(unsigned int size)
{
   return malloc(size);
}

//########################################################################################

void* memoryReAlloc(void ** oldPointer, unsigned int oldSize, unsigned int newSize)
{
   void * newPtr = NULL;

   if(oldPointer == NULL || *oldPointer == NULL)
      return NULL;

   newPtr = memoryAlloc(newSize);
   if(newPtr != NULL)
   {
      memcpy(newPtr, *oldPointer, min(oldSize,newSize));
      memoryFree(oldPointer);
   }

   return newPtr;
}

//########################################################################################

void  memoryFree(void **pp)
{
   if(pp == NULL || *pp == NULL)
      return;

   free(*pp);
   *pp = NULL;
}


//########################################################################################
