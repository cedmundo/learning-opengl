#include <ike/pool.h>
#include <stdlib.h>

int ikePoolBlockInit(ikePoolBlock *block, size_t chunksize) {
    char *mem = NULL;

    // Allocate and empty memory for block
    mem = calloc(1, chunksize);
    if (mem == NULL)
        return IKE_POOL_OUT_OF_MEMORY;

    block->start = mem;
    block->free = mem;
    block->next = NULL;
    block->end = mem+chunksize;
    return IKE_POOL_OK;
}

size_t ikePoolBlockAvailable(ikePoolBlock *block) {
    return block->end - block->free;
}

size_t ikePoolBlockTotalSize(ikePoolBlock *block) {
    return block->end - block->start;
}

int ikePoolInit(ikePool *pool, size_t chunksize) {
    pool->first = NULL;
    pool->current = NULL;
    pool->chunksize = chunksize;

    // Expand pool by default to first chunk.
    pool->first = malloc(sizeof(ikePoolBlock));
    if (pool->first == NULL) {
        return IKE_POOL_OUT_OF_MEMORY;
    }

    int bires = ikePoolBlockInit(pool->first, chunksize);
    if (bires != IKE_POOL_OK) {
        if (pool->first != NULL)
            free(pool->first);
        return bires;
    }

    pool->current = pool->first;
    return IKE_POOL_OK;
}

size_t ikePoolAvailable(ikePool *pool) {
    if (pool->current == NULL)
        return (size_t) 0L;

    return ikePoolBlockAvailable(pool->current);
}

size_t ikePoolTotalSize(ikePool *pool) {
    if (pool->current == NULL)
        return (size_t) 0L;

    return ikePoolBlockAvailable(pool->current);
}

void ikePoolDestroy(ikePool *pool) {
    ikePoolBlock *tmp, *cur = pool->first;
    while (cur != NULL) {
        tmp = cur->next;
        free(cur->start);
        free(cur);
        cur = tmp;
    }

    pool->first = NULL;
    pool->current = NULL;
}
