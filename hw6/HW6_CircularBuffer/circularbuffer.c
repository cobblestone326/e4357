#include "circularbuffer.h"


#define IS_BUFFER_SIZE_POWER_OF_TWO 1
#define BUFFER_SIZE 8
#define BUFFER_MASK 0x7
#define NUM_OF_ELEMS (BUFFER_SIZE-1)

/**< Init Ciruclar Buffer */
CircularBuffer* CircularBufferInit(CircularBuffer** pQue, int size) {
    int sz = size*sizeof(KeyType)+sizeof(CircularBuffer);
    *pQue = (CircularBuffer*) malloc(sz);
    if(*pQue) {
        //printf("Init CircularBuffer: keys[%d] (%d)\n", size, sz);
        if( !(size & (size-1)) ) {
            (*pQue)->size=size;
            (*pQue)->mask=size-1;
            (*pQue)->writePointer = 0;
            (*pQue)->readPointer = 0;
        } else {
            //printf("Error Size:%d is not power of TWO!\n", size);
        }
    }
    return *pQue;
}
