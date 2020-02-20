# CContainers
Object Oriented-like containers written in pure C and suitable for simple solutions.


## Motivation

int data = 1000;
int data2 = 2000;
int dataOut = 0;
int dataOut2 = 0;
HList list = listCreate(sizeof(int));

listPush(&list, &data);
listPush(&list, &data2);

dataOut = listGetFirst(&listWithIntegers); 
dataOut2 = listGetNext(&listWithIntegers);  

memoryFree((void**)&dataOut);   // Frees our first integer
memoryFree((void**)&dataOut2);  // Frees our second integer
listFree(&list); // Frees the list and all elements left in it
  
  
## Supports following conatiners:

List.


## How to build and run tests
TODO




