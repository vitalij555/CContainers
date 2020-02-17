#include <stddef.h>
#include <string.h>
#include <stdint.h>

#include "List.h"
#include "containerMemory.h"



typedef struct Node Node;



struct Node
{
  Node* next;
  Node* prev;
  void* data;
 };


typedef struct
{
  int listSize;
  size_t nodeSize;
  Node *head;
  Node *tail;
  Node *current;
 }List;



static void* __getNodeData(List* list);
static void* __getCurrentNodeDataPtr(List* list);
static void* __popGenericPart(List* list, Node* nodeToPop);



HList listCreate(size_t elementSize)
{
  List* list = NULL;
  if(elementSize <= 0)
    return NULL;

  list = (List*)memoryAlloc(sizeof(List));
  if(list == NULL)
    return NULL;

  memset(list, 0, sizeof(List));
  list->nodeSize = elementSize;
  return (HList)list;
 }


static void __freeNodeMemory(Node* node)
{
   if(node != NULL)
      memoryFree((void**)&(node->data));
   memoryFree((void**)&(node));
 }


int listFree(HList* hlist)
{

   if(listClear(hlist) != LIST_RESULT_OK)
      return LIST_RESULT_ERROR;

   memoryFree((void**)hlist);
   *hlist = NULL;
   return LIST_RESULT_OK;
 }


static Node* __createEmptyNode()
{
   Node* node = NULL;
   node = (Node*)memoryAlloc(sizeof(Node));
   if(node == NULL)
      return NULL;

   memset(node, 0, sizeof(Node));
   return node;
 }


static int __copyDataToEmptyNode(List* list, Node* node, void* data)
{
   if(node == NULL || list->nodeSize <= 0)
      return LIST_RESULT_ERROR;
   node->data = memoryAlloc(list->nodeSize);
   if(node->data == NULL)
      return LIST_RESULT_ERROR;
   memcpy(node->data, data, list->nodeSize);
   return LIST_RESULT_OK;
 }


static int __attachNode(List* list, Node* prev, Node* nodeNew, Node* next)
{
   if(nodeNew == NULL)
      return LIST_RESULT_ERROR;

   if(prev == NULL && next == NULL)
   {
      if(list->listSize != 0)
         return LIST_RESULT_ERROR;

     list->head    = nodeNew;
     list->tail    = nodeNew;
     list->current = nodeNew;
   }
   else
   {
      if(prev != NULL)
         prev->next = nodeNew;
      else
         list->head = nodeNew;

      if(next != NULL)
         next->prev = nodeNew;
      else
         list->tail = nodeNew;

      nodeNew->prev = prev;
      nodeNew->next = next;
   }
  return LIST_RESULT_OK;
 }


static int __detachNodeFromList(List* list, Node* node)
{
   if(node == NULL)
      return LIST_RESULT_ERROR;

   if(node->prev != NULL)
      node->prev->next = node->next;
   else
      list->head = node->next;

   if(node->next != NULL)
      node->next->prev = node->prev;
   else
      list->tail = node->prev;

   if(list->current == node)
      list->current = node->next;

   return LIST_RESULT_OK;
 }


static void __increaseNodesCount(List* list)
{
    ++(list->listSize);
 }


static void __decreaseNodesCount(List* list)
{
   --(list->listSize);
 }


static int __createNodeWithData(List* list, Node** node, void* data)
{
   (*node) = __createEmptyNode();
   if((*node) == NULL)
      return LIST_RESULT_ERROR;

   if(__copyDataToEmptyNode(list, *node, data) != LIST_RESULT_OK)
      return LIST_RESULT_ERROR;

   return LIST_RESULT_OK;
 }


int listPush(HList* hlist, void* data)
{
   Node* node = NULL;
   List* list;

   if(hlist == NULL || (*hlist) == NULL)
      return LIST_RESULT_ERROR;
   list = (List*)*hlist;

   if(__createNodeWithData(list, &node, data) != LIST_RESULT_OK)
      return LIST_RESULT_ERROR;

   if(__attachNode(list, list->tail, node, NULL) != LIST_RESULT_OK)
      return LIST_RESULT_ERROR;

   __increaseNodesCount(list);

   return LIST_RESULT_OK;
 }


int listPushFront(HList* hlist, void* data)
{
   Node* node = NULL;
   List* list;

   if(hlist == NULL || (*hlist) == NULL)
      return LIST_RESULT_ERROR;
   list = (List*)*hlist;

   if(__createNodeWithData(list, &node, data) != LIST_RESULT_OK)
      return LIST_RESULT_ERROR;

   if(__attachNode(list, NULL, node, list->head) != LIST_RESULT_OK)
      return LIST_RESULT_ERROR;

   __increaseNodesCount(list);

   return LIST_RESULT_OK;
 }


static void* __popGenericPart(List* list, Node* nodeToPop)
{
	void* dataOut = NULL;

	if(nodeToPop == NULL || list == NULL)
		return NULL;

	if(nodeToPop->data == NULL || list->nodeSize <= 0)
	  return NULL;

	if(__detachNodeFromList(list, nodeToPop) != LIST_RESULT_OK)
	  return NULL;

	dataOut = memoryAlloc(list->nodeSize);
	if(dataOut == NULL)
	{
	   __freeNodeMemory(nodeToPop);
	   return NULL;
	 }

	memset(dataOut, 0, list->nodeSize);
	memcpy(dataOut, nodeToPop->data, list->nodeSize);

	__freeNodeMemory(nodeToPop);
	__decreaseNodesCount(list);

	return dataOut;
}


void* listPopFront(HList* hlist)
{
  Node* nodeToPop = NULL;
  List* list;

  if(hlist == NULL || (*hlist) == NULL)
    return NULL;

  list = (List*)*hlist;

  if(list->head == NULL)
    return NULL;

  nodeToPop = list->head;

  return __popGenericPart(list, nodeToPop);
 }


void* listPopEnd(HList* hlist)
{
  Node* nodeToPop = NULL;
  List* list;

  if(hlist == NULL || (*hlist) == NULL)
    return NULL;

  list = (List*)*hlist;

  if(list->tail == NULL)
    return NULL;

  nodeToPop = list->tail;

  return __popGenericPart(list, nodeToPop);
 }


int listGetSize(const HList* hlist)
{
  List* list = NULL;
  if(hlist == NULL || (*hlist) == NULL)
    return LIST_RESULT_ERROR;

  list = (List*)*hlist;
  return list->listSize;
 }


int listGetElementSize(const HList* hlist)
{
  List* list = NULL;
  if(hlist == NULL || (*hlist) == NULL)
    return LIST_RESULT_ERROR;

  list = (List*)*hlist;
  return list->nodeSize;
 }


bool listIsEmpty(const HList* hlist)
{
  int size = listGetSize(hlist);
  return(size <= 0);
 }


static void* __getNodeData(List* list)
{
  void * resultBuff;

  if(list->current == NULL || list->current->data == NULL)
    return NULL;

  resultBuff = memoryAlloc(list->nodeSize);
  if(resultBuff == NULL)
    return NULL;

  memset(resultBuff, 0, list->nodeSize);
  memcpy(resultBuff, list->current->data, list->nodeSize);
  return resultBuff;
 }


static void* __getCurrentNodeDataPtr(List* list)
{
	if(list->current == NULL || list->current->data == NULL)
	   return NULL;

	return list->current->data;
}


void* listGetFirst(const HList* hlist)
{
	List* list;

	if(hlist == NULL || (*hlist) == NULL)
	return NULL;
	list = (List*)*hlist;

	if(list->nodeSize <= 0 || ((list->current != NULL) && (list->current->data == NULL)))
	return NULL;

	list->current = list->head;

	return __getNodeData(list);
 }


void* listGetNext(const HList* hlist)
{
	List* list;

	if(hlist == NULL || (*hlist) == NULL)
	return NULL;
	list = (List*)*hlist;

	if(list->current == NULL || list->nodeSize <=0 || list->current->data == NULL)
	return NULL;

	list->current = list->current->next;

	return __getNodeData(list);
 }


void* listGetFirstPtr(const HList* hlist)
{
	List* list;

	if(hlist == NULL || (*hlist) == NULL)
	return NULL;
	list = (List*)*hlist;

	if(list->nodeSize <= 0 || ((list->current != NULL) && (list->current->data == NULL)))
	return NULL;

	list->current = list->head;

	return __getCurrentNodeDataPtr(list);
 }


void* listGetNextPtr(const HList* hlist)
{
	List* list;

	if(hlist == NULL || (*hlist) == NULL)
	return NULL;
	list = (List*)*hlist;

	if(list->current == NULL || list->nodeSize <=0 || list->current->data == NULL)
	return NULL;

	list->current = list->current->next;

	return __getCurrentNodeDataPtr(list);
 }


void* listGetCurrent(const HList* hlist)
{
	List* list;

	if(hlist == NULL || (*hlist) == NULL)
	return NULL;
	list = (List*)*hlist;

	if(list->current == NULL || list->nodeSize <=0 || list->current->data == NULL)
	return NULL;

	return __getNodeData(list);
 }


void* listGetCurrentPtr(const HList* hlist)
{
	List* list;

	if(hlist == NULL || (*hlist) == NULL)
	return NULL;
	list = (List*)*hlist;

	if(list->current == NULL || list->nodeSize <=0 || list->current->data == NULL)
	return NULL;

	return __getCurrentNodeDataPtr(list);
 }


int listEraseCurrent(HList* hlist)
{
	Node* nodeTemp;
	List* list;

	if(hlist == NULL || (*hlist) == NULL)
	return LIST_RESULT_ERROR;
	list = (List*)*hlist;

	if(list->current == NULL)
	return LIST_RESULT_OK;

	nodeTemp = list->current;
	list->current = list->current->next;

	if(__detachNodeFromList(list, nodeTemp) != LIST_RESULT_OK)
	return LIST_RESULT_ERROR;

	__freeNodeMemory(nodeTemp);
	__decreaseNodesCount(list);
	return LIST_RESULT_OK;
 }


int listClear(HList* hlist)
{
  Node* node = NULL;
  Node* nodeToFree = NULL;
  List* list;

  if(hlist == NULL || (*hlist) == NULL)
    return LIST_RESULT_ERROR;
  list = (List*)*hlist;

  node = list->head;
  while(node)
  {
    nodeToFree = node;
    node = node->next;
    __freeNodeMemory(nodeToFree);
   }
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  list->listSize = 0;

  return LIST_RESULT_OK;
}


int listMergeLists(HList* destinationList, HList* listToBeAppended)
{
	if(destinationList == NULL || (*destinationList) == NULL ||	listToBeAppended == NULL || (*listToBeAppended) == NULL)
		return LIST_RESULT_ERROR;

	List* listDest = (List*)*destinationList;
	List* listSrc = (List*)*listToBeAppended;

	if(listSrc->listSize == 0)
	{
		memoryFree((void**)&listSrc);
		(*listToBeAppended) = NULL;

		return LIST_RESULT_OK;
	 }

	if (listDest->listSize == 0)
		listDest->head = listSrc->head;
	else
	{
		listDest->tail->next = listSrc->head;
		listSrc->head->prev = listDest->tail;
	 }

	listDest->tail = listSrc->tail;
	listDest->listSize += listSrc->listSize;

	memoryFree((void**)&listSrc);
	(*listToBeAppended) = NULL;

	return LIST_RESULT_OK;
 }


void* listSerialize(HList* hlist, size_t* outSerializedLength)
{
	char* resultBuff = NULL;
	uint32_t listSize = 0;
	uint32_t elementSize = 0;
	const void* it = NULL;
	char* pBuffer = NULL;

	if((outSerializedLength == NULL) || (hlist == NULL))
	return NULL;

	*outSerializedLength = 0;

	listSize = listGetSize(hlist);
	elementSize = listGetElementSize(hlist);

	*outSerializedLength = listSize * elementSize + sizeof(uint32_t)*2;
	resultBuff = (char*)memoryAlloc(*outSerializedLength);
	if(resultBuff == NULL)
	return NULL;

	pBuffer = resultBuff;

	*((uint32_t*)(void*)pBuffer) = elementSize;
	pBuffer += sizeof(uint32_t);
	*((uint32_t*)(void*)pBuffer) = listSize;
	pBuffer += sizeof(uint32_t);

	it = listGetFirstPtr(hlist);
	while(it != NULL)
	{
	memcpy(pBuffer, it, elementSize);
	pBuffer += elementSize;
	it = listGetNextPtr(hlist);
	}

	return resultBuff;
 }


HList listDeserialize(void* data, size_t dataLength)
{
	uint32_t listSize = 0;
	uint32_t elementSize = 0;
	char* pBuffer = NULL;
	HList resultList = NULL;
	unsigned int i = 0;

	if(data == NULL || dataLength<(sizeof(uint32_t)*2) )
	 return NULL;

	pBuffer = data;

	elementSize = *((uint32_t *)(void*)pBuffer);
	pBuffer += sizeof(uint32_t);
	listSize = *((uint32_t *)(void*)pBuffer);
	pBuffer += sizeof(uint32_t);

	if(dataLength != elementSize*listSize + sizeof(uint32_t)*2)
	 return NULL;

	resultList = listCreate(elementSize);
	for(i=0; i<listSize; ++i)
	{
	  listPush(&resultList, pBuffer);
	  pBuffer += elementSize;
	}
	return resultList;
 }


HList listClone(HList hList)
{
	HList resultList;

	if(hList == NULL)
	 return NULL;

	resultList = listCreate(listGetElementSize(&hList));
	if(resultList == NULL)
	 return NULL;

	const void* element = listGetFirstPtr(&hList);
	while(element != NULL)
	{
	 if(listPush(&resultList, (void*)element) != LIST_RESULT_OK)
	 {
		listFree(&resultList);
		return NULL;
	 }
	 element = listGetNextPtr(&hList);
	}

	return resultList;
}


