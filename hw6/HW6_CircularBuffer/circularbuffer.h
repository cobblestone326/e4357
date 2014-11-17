#ifndef __CIRCULAR_BUFFER
#define __CIRCULAR_BUFFER
#include "mbed.h"
/* Implement a circularbuffer library with the following API interface */

/**< Circular Buffer Types */
typedef unsigned char INT8U;
typedef INT8U KeyType ;
typedef struct {  
    INT8U writePointer ; /**< write pointer */  
    INT8U readPointer ;  /**< read pointer */  
    INT8U size;         /**< size of circular buffer */
    INT8U mask;         /**< bit Mask of circular buffer size*/   
    KeyType keys[0];    /**< Element of ciruclar buffer */
} CircularBuffer ; 
CircularBuffer* CircularBufferInit(CircularBuffer** pQue, int size);
inline int CircularBufferIsFull(CircularBuffer* que) {
   if (que->readPointer == 0) {
        if (que->writePointer == que->mask) {
            return true;
        } else {
            return false;
        }
    } else {
        if (que->readPointer - que->writePointer == 1) {
            return true;
        } else {
            return false;
        }
    }
}
inline int CircularBufferIsEmpty(CircularBuffer* que) {
    return que->readPointer == que->writePointer;
}
inline void CircularBufferEnque(CircularBuffer* que, KeyType k) { 
    if (CircularBufferIsFull(que)) return;
    (que->keys)[que->writePointer] = k;
    que->writePointer += 1;
    if (que->writePointer == que->size) que->writePointer = 0;
}
inline KeyType* CircularBufferDeque(CircularBuffer* que, KeyType* pK) {
    if (CircularBufferIsEmpty(que)) {
        return pK;
    }
    *pK = (que->keys)[que->readPointer];
    que->readPointer += 1;
    if (que->readPointer == que->size) que->readPointer = 0;
    return pK;
}


#endif