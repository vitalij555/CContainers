#pragma once


#include <stdint.h>
#include <stdbool.h>
typedef struct List* HList;


typedef enum
{
  LIST_RESULT_OK    = 0,
  LIST_RESULT_ERROR = -1,
} LIST_RESULT;



/**
 * @brief Creates new list
 * @param[in] nodeSize node size in bytes
 * @return returns list handle or NULL in case of error
 */
HList listCreate(size_t nodeSize);


/**
 * @brief Releases memory allocated for a list
 * @param[out] hlist Pointer to a valid list handle. In case of success hlist becomes equal to NULL
 * @return LIST_RESULT_OK or LIST_RESULT_ERROR
 */
int listFree(HList* hlist);


/**
 * @brief Appends new node at the end of a list
 * @param[in] hlist Pointer to a valid list handle
 * @param[out] data pointer to a new list node
 * @return LIST_RESULT_OK or LIST_RESULT_ERROR
 */
int listPush(HList* hlist, void* data);


/**
 * @brief Adds new node at the beginning of a list
 * @param[in] hlist Pointer to a valid list handle
 * @param[out] data pointer to a new list node
 * @return LIST_RESULT_OK or LIST_RESULT_ERROR
 */
int listPushFront(HList* hlist, void* data);


/**
 * @brief Gets pointer to the first node in a list
 * @param[in] hlist Pointer to a valid list handle
 * @return pointer to a list node found
 */
void* listPopFront(HList* hlist);


/**
 * @brief Gets pointer to the last node in a list
 * @param[in] hlist Pointer to a valid list handle
 * @return pointer to element found
 */
void* listPopEnd(HList* hlist);


/**
 * @brief Returns number of nodes in the list
 * @param[in] hlist Pointer to valid list handle
 * @return node count
 */
int listGetSize(const HList* hlist);


/**
 * @brief Gets stored node's size.
 * @param[in] hlist Pointer to a valid list handle
 * @return Stored node size
 */
int listGetElementSize(const HList* hlist);


/**
 * @brief Checks if given list is empty
 * @param[in] hlist Pointer to a valid list handle.
 * @return TRUE or FALSE
 */
bool listIsEmpty(const HList* hlist);


/**
 * @brief Gets pointer to copied first element of list
 * @param[in] hlist Pointer to a valid list handle.
 * @return pointer to first element or NULL
 */
void* listGetFirst(const HList* hlist);


/**
 * @brief Iterates to the next list node and returns pointer to it
 * @param[in] hlist Pointer to a valid list handle.
 * @return pointer to the next list node
 */
void* listGetNext(const HList* hlist);


/**
 * @brief Gets pointer to first element in list
 * @param[in] hlist Pointer to a valid list handle.
 * @return pointer to first element
 *
 * @note This function returns pointer to the inner stored data, so it is prohibited to free returned memory.
 */
void* listGetFirstPtr(const HList* hlist);


/**
 * @brief Iterates to next element pointer in list
 * @param[in] hlist Pointer to a valid list handle
 * @return pointer to next element in a list
 *
 * @note This function returns pointer to the inner stored data, so it is prohibited to free returned memory
 */
void* listGetNextPtr(const HList* hlist);


/**
 * @brief Gets pointer to copy of current element
 * @param[in] hlist Pointer to a valid list handle
 * @return pointer to current node's copied data
 */
void* listGetCurrent(const HList* hlist);


/**
 * @brief Gets pointer to current node in a list
 * @param[in] hlist Pointer to a valid list handle.
 * @return pointer to current node
 *
 * @note This function returns pointer to the inner stored data, so it is prohibited to free returned memory.
 */
void* listGetCurrentPtr(const HList* hlist);


/**
 * @brief Removes current node from a list
 * @param[in] hlist Pointer to a valid list handle.
 * @return LIST_RESULT_OK or LIST_RESULT_ERROR
 */
int listEraseCurrent(HList* hlist);


/**
 * @brief Clears all contents of the list
 * @param[in] hlist Pointer to a valid list handle.
 * @return LIST_RESULT_OK or LIST_RESULT_ERROR
 */
int listClear(HList* hlist);


/**
 * @brief Merges two lists.
 * @param destinationList[in] List to be merged to
 * @param listToBeAppended[in] List that will be added to the end of destinationList
 * @return LIST_RESULT_OK or LIST_RESULT_ERROR
 *
 * @note If operation is successful listToBeAppended will be set to null
 */
int listMergeLists(HList* destinationList, HList* listToBeAppended);


/**
 * @brief Use this function for list serialization.
 * @param hlist Pointer to valid list handle.
 * @param outSerializedLength Pointer to uint32_t used to return serialized list length.
 * @return Function returns serialized representation of list or NULL on ERROR.
 *
 * @note Returned buffer should be freed if not needed anymore.
 */
void* listSerialize(HList* hlist, size_t* outSerializedLength);


/**
 * @brief Use this function for list deserialization from serialized buffer.
 * @param[in] data Buffer containing serialized list.
 * @param[in] dataLength length of the serialized data.
 * @return Returns valid handle to deserialized list or NULL otherwise.
 *
 * @note Serializable data passed as a first parameter is not freed inside function body automatically.
 */
HList listDeserialize(void* data, size_t dataLength);


/**
 * @brief Creates clone of a list.
 * @param hList List to clone.
 * @return New list handle if success or NULL otherwise.
 */
HList listClone(HList hList);


