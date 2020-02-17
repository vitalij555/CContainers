#pragma once


int min(unsigned int d1, unsigned int d2);

/**
 * @brief standard ANSI C malloc function
 * @param[in] size How much memory to allocate from heap (in bytes)
 * @return returns pointer to allocated memory or NULL otherwise
 */
void* memoryAlloc(unsigned int size);


/**
 * @brief Re-allocates memory
 * @param[in] oldPointer
 * @param[in] oldSize
 * @param[in] newSize
 * @return returns pointer to allocated memory or NULL otherwise
 */
void* memoryReAlloc(void ** oldPointer, unsigned int oldSize, unsigned int newSize);


/**
 * @brief Function similar standard ANSI C free() except that it also avoids wild pointers problem.
 * @param pp Pointer to pointer to allocated memory block
 * @return returns list handle or NULL in case of error
 */
void  memoryFree(void **pp);


