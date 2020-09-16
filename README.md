# CContainers
Object Oriented-like containers written in pure C and suitable for simple solutions.


## Motivation

```C
int data = 1000;
int data2 = 2000;
int* dataOut = 0;
int* dataOut2 = 0;
HList list = listCreate(sizeof(int));

listPush(&list, &data);
listPush(&list, &data2);

dataOut = listGetFirst(&list); 
dataOut2 = listGetNext(&list);  

memoryFree((void**)&dataOut);   // Frees our first integer
memoryFree((void**)&dataOut2);  // Frees our second integer
listFree(&list); // Frees the list and all elements left in it
```  
  
## Supports following conatiners:

List.


## How to build and run tests

1. ### Installation 

    1. #### For Linux

        1. ##### install python

        1. ##### create virtual env and switch into it

        1. ##### install ninja

        1. ##### install meson

    1. #### For Windows

        1. ##### install python

        1. ##### create virtual env and switch into it

        1. ##### install cygwin

        1. ##### install CMake

        1. ##### install ninja

        1. ##### install meson

1. ### Building

    1. ##### meson builddir

    1. ##### cd builddir

    1. ##### meson compile

1. #### Testing
    
./CContainersTests.exe

