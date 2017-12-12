#ifndef IKE_SPEC_H
#define IKE_SPEC_H
#include <ike/any.h>
#include <stddef.h>

#define IKE_SPEC_OK (0)
#define IKE_SPEC_OUT_OF_MEMORY (1)
#define IKE_SPEC_INVALID_TYPE (2)

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
    INT,
    FLOAT,
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
    ikeAny value;
    const char *key;
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

/**
 * \brief Gets an integer using specified key.
 *
 * \param spec where value is stored.
 * \param key to hash.
 * \param value (output) to copy value from map.
 * \return IKE_SPEC_OK or IKE_HASHMAP_MISSING.
 */
int ikeSpecGetInt(ikeSpec* spec, const char *key, int *value);

/**
 * \brief Puts an integer using specified key.
 *
 * \param spec where value is going to be stored.
 * \param key to hash.
 * \param value to store into map.
 * \return IKE_SPEC_OK or IKE_HASHMAP_OMEM.
 */
int ikeSpecPutInt(ikeSpec* spec, const char *key, int value);

/**
 * \brief Gets an float using specified key.
 *
 * \param spec where value is stored.
 * \param key to hash.
 * \param value (output) to copy value from map.
 * \return IKE_SPEC_OK or IKE_HASHMAP_MISSING.
 */
int ikeSpecGetFloat(ikeSpec* spec, const char *key, float *value);

/**
 * \brief Puts an float using specified key.
 *
 * \param spec where value is going to be stored.
 * \param key to hash.
 * \param value to store into map.
 * \return IKE_SPEC_OK or IKE_HASHMAP_OMEM.
 */
int ikeSpecPutFloat(ikeSpec* spec, const char *key, float value);

/**
 * \brief Gets an string using specified key (read-only).
 *
 * \param spec where value is stored.
 * \param key to hash.
 * \param value (output) to copy value from map.
 * \return IKE_SPEC_OK or IKE_HASHMAP_MISSING.
 */
int ikeSpecGetString(ikeSpec* spec, const char *key, const char **value);

/**
 * \brief Puts an string using specified key (read-only).
 *
 * \param spec where value is going to be stored.
 * \param key to hash.
 * \param value to store into map.
 * \return IKE_SPEC_OK or IKE_HASHMAP_OMEM.
 */
int ikeSpecPutString(ikeSpec* spec, const char *key, const char *value);

/**
 * \brief Puts size n string using specified key (read-only).
 *
 * \param spec where value is going to be stored.
 * \param key to hash.
 * \param value to store into map.
 * \param size of value.
 * \return IKE_SPEC_OK or IKE_HASHMAP_OMEM.
 */
int ikeSpecPutStringSize(ikeSpec* spec, const char *key, const char *value, size_t size);

/**
 * \brief Gets an spec using specified key (read-only).
 *
 * \param spec where value is stored.
 * \param key to hash.
 * \param value (output) to copy value from map.
 * \return IKE_SPEC_OK or IKE_HASHMAP_MISSING.
 */
int ikeSpecGetSpec(ikeSpec* spec, const char *key, ikeSpec *value);

/**
 * \brief Puts an spec using specified key (read-only).
 *
 * \param spec where value is going to be stored.
 * \param key to hash.
 * \param value to store into map.
 * \return IKE_SPEC_OK or IKE_HASHMAP_OMEM.
 */
int ikeSpecPutSpec(ikeSpec* spec, const char *key, ikeSpec *value);

#endif /* IKE_SPEC_H */
