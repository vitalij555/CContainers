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
  
Another example. This time with struct:

```C
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
    addressOut = listGetFirst(&list);
  }

 listFree(&list); // Frees the list and all elements left in it (if any)
}
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

