#ifndef IKE_POOL_H
#define IKE_POOL_H
#include <stddef.h>

#define IKE_POOL_TINY ((size_t) 512)
#define IKE_POOL_SMALL ((size_t) 1024)
#define IKE_POOL_MEDIUM ((size_t) 64*1024)
#define IKE_POOL_BIG ((size_t) 64*1024*1024)

#define IKE_POOL_OK 0
#define IKE_POOL_OUT_OF_MEMORY 2

// NOTE: This is a 4 byte boundary align, if your platform
// requires anyother memory aligment please implement that here.
//
// TODO?: Define a MACRO to use build configuration aligment.
#define IKE_POOL_ALIGMENT (4)
#define ikePoolMemoryAlign(s) ((s+(IKE_POOL_ALIGMENT-1)) & 0xfffffffc)

/**
 * Memory block.
 *
 * \brief A registered block of memory that contains a
 * reference to its initial point, the free space
 * available and the end of block.
 */
typedef struct _ikePoolBlock {
    struct _ikePoolBlock *next;
    char *start; // start of block
    char *free; // next free block
    char *end; // block + block size
} ikePoolBlock;

/**
 * A memory pool.
 *
 * \brief A root of linked list of blocks,
 * used to register requested memory chunks.
 *
 * Memory must be freed using ikePoolDestroy.
 */
typedef struct _ikePool {
    ikePoolBlock *first, *current;
    size_t chunksize;
} ikePool;

/**
 * Initializes a block of memory.
 *
 * \brief Initializes a memory chunk setting its internal state to
 * initial and requesting memory (through malloc) with size of
 * chunksize to contain data.
 *
 * Note: Memory will be automatically set to zero using memset.
 *
 * \param block of memory to initialize (distinct to null).
 * \param chunksize the size of memory request.
 * \return IKE_POOL_OK if success, IKE_POOL_OUT_OF_MEMORY if there's not enough memory.
 */
int ikePoolBlockInit(ikePoolBlock *block, size_t chunksize);

/**
 * Returns available memory of a block.
 *
 * \brief Calculates and returns the available memory on bytes.
 * \param block to calculate.
 * \return size on bytes, 0 if there are no available memory.
 */
size_t ikePoolBlockAvailable(ikePoolBlock *block);

/**
 * Returns total memory of a block.
 *
 * \brief Calculates and returns the total memory requested by the block.
 * \param block to calculate.
 * \return size on bytes, 0 if there are no allocated memory.
 */
size_t ikePoolBlockTotalSize(ikePoolBlock *block);

/**
 * Initializes a memory pool to its default values.
 *
 * \brief Sets default internal values of a memory pool, also
 * allocates memory for the first block.
 * \param pool to setup.
 * \param chunksize to use evenly on each block request.
 * \return IKE_POOL_OK if success, IKE_POOL_OUT_OF_MEMORY if there's not enough memory (for first block).
 */
int ikePoolInit(ikePool *pool, size_t chunksize);

/**
 * Returns the current available memory of the pool.
 *
 * \param pool to calculate.
 * \return size on bytes, 0 if there are no available memory.
 */
size_t ikePoolAvailable(ikePool *pool);

/**
 * Returns the current total memory of the pool.
 *
 * \param pool to calculate.
 * \return size on bytes, 0 if there are no allocated memory.
 */
size_t ikePoolTotalSize(ikePool *pool);

/**
 * Destroys a memory pool automatically freeing all allocated chunks.
 */
void ikePoolDestroy(ikePool *pool);

/**
 * Returns a pointer to usable memory into the current memory block
 * with a size of second parameter. If size is bigger than current chunksize then
 * allocator will create a new block with the requested size so be aware of declare
 * a rasonable chunksize for pool on initialization.
 *
 * \param pool to lock memory.
 * \param size of required allocation.
 * \return an aligned pointer to usable memory, NULL if no memory is available on pool and could not allocate new one.
 *
 */
void *ikePoolGet(ikePool *pool, size_t size);

/**
 * Resets a pool to be used again without freeing its memory blocks.
 * \param pool to be recycled.
 */
void ikePoolRecycle(ikePool *pool);

#endif /* IKE_POOL_H */
