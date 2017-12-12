#ifndef IKE_SPEC_H
#define IKE_SPEC_H
#include <ike/any.h>

// ikePool to allocate data while growing spec.
// Anonymous typing for reference only.
typedef struct _ikePool ikePool;

// ikeHashmap to store allocation addresses of data while growing spec.
// Anonymous typing for reference only.
typedef struct _ikeHashmap ikeHashmap;

// Available serialization types.
typedef enum _ikeSpecType {
    NONE=0,
    SPEC,
    LONG,
    DOUBLE,
    STRING,
} ikeSpecType;

/**
 * \brief Specs are data descriptions for general usage.
 *
 * Spec is a _basic_ replacement for JSON or XML, it's intended to be used for
 * descriptions, such game object properties, configurations and other misc textual
 * utilities.
 *
 * Warning: do not directly write on internal pool or hashmap data, this may cause
 * data corruption or unexpected errors.
 */
typedef struct _ikeSpec {
    ikePool     *pool;
    ikeHashmap  *hashmap;
} ikeSpec;

/*
 * All stored data on spec, may contain any basic type or another nested spec.
 */
typedef struct _ikeSpecItem {
    ikeAny any;
    char *key;
    ikeSpecType type;
} ikeSpecItem;

/**
 * \brief Initializes a spec struct.
 *
 * Allocates memory for pool and hashmap to be ready to use at any time.
 * \param spec to initialize.
 * \return IKE_SPEC_OK if success, IKE_SPEC_OUT_OF_MEMORY if there is no more memory available.
 */
int ikeSpecInit(ikeSpec *spec);

/**
 * \brief Frees *all* the memory used by argumented spec.
 * \param spec to destroy.
 */
void ikeSpecDestroy(ikeSpec *spec);

#endif /* IKE_SPEC_H */
