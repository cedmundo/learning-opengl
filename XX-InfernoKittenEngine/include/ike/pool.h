#ifndef IKE_POOL_H
#define IKE_POOL_H
#include <stddef.h>

#define IKE_POOL_SMALL ((size_t) 1024)
#define IKE_POOL_MEDIUM ((size_t) 64*1024)
#define IKE_POOL_BIG ((size_t) 64*1024*1024)

#define IKE_POOL_OK 0
#define IKE_POOL_OUT_OF_MEMORY 2

typedef struct _ikePoolBlock {
    struct _ikePoolBlock *next;
    char *start; // start of block
    char *free; // mext free block
    char *end; // block + block size
} ikePoolBlock;

typedef struct _ikePool {
    ikePoolBlock *first, *current;
    size_t chunksize;
} ikePool;

int ikePoolBlockInit(ikePoolBlock *block, size_t chunksize);
size_t ikePoolBlockAvailable(ikePoolBlock *block);
size_t ikePoolBlockTotalSize(ikePoolBlock *block);

int ikePoolInit(ikePool *pool, size_t chunksize);
size_t ikePoolAvailable(ikePool *pool);
size_t ikePoolTotalSize(ikePool *pool);
void ikePoolDestroy(ikePool *pool);

#endif /* IKE_POOL_H */
