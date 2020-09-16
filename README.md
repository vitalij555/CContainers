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

### Installation 

#### For Linux
install python
create virtual env and switch into it
install ninja
install meson

#### For Windows
install python
create virtual env and switch into it
install cygwin
install CMake
install ninja
install meson

#### Build
meson builddir
cd builddir
meson compile

#### Testing
./CContainersTests.exe

