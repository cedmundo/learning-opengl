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

    size_t len = 0;
    ikePoolBlock *cur = pool->first;
    while (cur != NULL) {
        len += ikePoolBlockTotalSize(cur);
        cur = cur->next;
    }

    return len;
}

void *ikePoolGet(ikePool *pool, size_t size) {
    ikePoolBlock *tmp = NULL;
    char *ptr = NULL;
    int res = 0;

    // Align memory to prevent hardware issues.
    size = ikePoolMemoryAlign(size);

    // Allocate a bigger chunk if required size
    // is major than current chunksize.
    if (size > pool->chunksize) {
        tmp = malloc(sizeof(ikePoolBlock));
        res = ikePoolBlockInit(tmp, pool->chunksize);
        if (res != IKE_POOL_OK) {
            if (tmp != NULL)
                free(tmp);

            return NULL;
        }

        // If there is recycled memory use it,
        // only insert bigger chunk.
        if (pool->current->next != NULL) {
            tmp->next = pool->current->next;
        }

        // Insert block on the chain.
        pool->current->next = tmp;
        pool->current = tmp;
    }

    tmp = pool->current;
    ptr = tmp->free; // Usable memory.
    tmp->free += size; // Point to next block.

    // Check if current block is exhausted.
    if (tmp->free >= tmp->end) {
        // Is the next block already allocated?
        if (tmp->next != NULL) {
            // Re-use block.
            tmp->next->free = tmp->next->start;
            pool->current = tmp->next;
        } else {
            // Extend the pool with a new block.
            tmp->next = malloc(sizeof(ikePoolBlock));
            res = ikePoolBlockInit(tmp->next, size);
            if (res != IKE_POOL_OK) {
                if (tmp->next != NULL)
                    free(tmp->next);

                return NULL;
            }

            pool->current = tmp->next;
        }

        // Set ptr to the first location in the new block.
        ptr = pool->current->free;
        pool->current->free += size;
    }

    return ptr;
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

void ikePoolRecycle(ikePool *pool) {
    pool->current = pool->first;
    pool->current->free = pool->current->start;
}
