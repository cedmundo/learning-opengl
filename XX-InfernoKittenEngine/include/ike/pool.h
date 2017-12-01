#ifndef IKE_POOL_H
#define IKE_POOL_H
#include <stddef.h>

const size_t IKE_POOL_SMALL = 0;
const size_t IKE_POOL_MEDIUM = 100;
const size_t IKE_POOL_BIG = 1000;

typedef struct _ikePool {

} ikePool;

int ikePoolInit(ikePool *pool, size_t chunksize);

size_t ikePoolAvailable(ikePool *pool);

void ikePoolDestroy(ikePool *pool);

#endif /* IKE_POOL_H */
