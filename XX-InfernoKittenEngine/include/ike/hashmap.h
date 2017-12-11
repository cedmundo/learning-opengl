#ifndef IKE_SPEC_H
#define IKE_SPEC_H
#include <stdio.h>

#define IKE_HASHMAP_MISSING (-3) // No such element
#define IKE_HASHMAP_FULL (-2) // Full
#define IKE_HASHMAP_OMEM (-1) // Out Of Memory
#define IKE_HASHMAP_OK (0) // Ok

#ifndef IKE_ANY
#define IKE_ANY
/**
 * \brief Any arbitary type.
 *
 * Used to handle abstract types without touching its data at all.
 */
typedef void* ikeAny;
#endif

/**
 * \brief Iterator callback.
 *
 * This callback must return a map status code, if it returns anything
 * other than IKE_HASHMAP_OK the traversal is terminated. Also, it's highly
 * recommended to not reenter any Hashmap functions, or deadlock may arise.
 */
typedef int (*ikeHashmapIterator)(ikeAny, ikeAny);

/* We need to keep keys and values */
typedef struct _ikeHashmapElement {
	const char* key;
	int inuse;
	ikeAny data;
} ikeHashmapElement;

/**
 * \brief Forward declaration for ikeHashmap.
 *
 * Clients should use only ikeHashmap exported functions to handle data
 * within a hashmap, which is basically a Hashmap, implementation borrowed
 * (re-written and sighlty modified for code style propouses) from https://github.com/petewarden/c_hashmap.
 */
typedef struct _ikeHashmap {
    int tablesize;
    int size;
    ikeHashmapElement *data;
} ikeHashmap;

/**
 * \brief Inits an ikeHashmap.
 * \param hashmap that is going to be inited.
 */
int ikeHashmapInit(ikeHashmap* hashmap);

/**
 * \brief Iterate over items of hashmap.
 *
 * Iteratively call iter param with (userdata, itemdata) as argument for each
 * element data in hashmap.
 *
 * \param hashmap map to iterate.
 * \param iter function to call.
 * \param userdata first argument of call.
 * \return
 */
int ikeHashmapIterate(ikeHashmap* hashmap, ikeHashmapIterator iter, ikeAny userdata);

/**
 * \brief Puts a value with hashmapified key.
 *
 * \param hashmap where value is going to be stored.
 * \param key to hash.
 * \param item to store.
 * \return IKE_HASHMAP_OK or IKE_HASHMAP_OMEM.
 */
int ikeHashmapPut(ikeHashmap* hashmap, const char *key, ikeAny item);

/**
 * \brief Gets a value using hashmapified key.
 *
 * \param hashmap where value is stored.
 * \param key to hash.
 * \param item (output) to copy value from map.
 * \return IKE_HASHMAP_OK or IKE_HASHMAP_MISSING.
 */
int ikeHashmapGet(ikeHashmap* hashmap, const char *key, ikeAny *item);

/**
 * \brief Gets an integer using hashmapified key.
 *
 * \param hashmap where value is stored.
 * \param key to hash.
 * \param item (output) to copy value from map.
 * \return IKE_HASHMAP_OK or IKE_HASHMAP_MISSING.
 */
int ikeHashmapGetInt(ikeHashmap* hashmap, const char *key, int *item);

/**
 * \brief Gets a float using hashmapified key.
 *
 * \param hashmap where value is stored.
 * \param key to hash.
 * \param item (output) to copy value from map.
 * \return IKE_HASHMAP_OK or IKE_HASHMAP_MISSING.
 */
int ikeHashmapGetFloat(ikeHashmap* hashmap, const char *key, float *item);

/**
 * \brief Gets a double using hashmapified key.
 *
 * \param hashmap where value is stored.
 * \param key to hash.
 * \param item (output) to copy value from map.
 * \return IKE_HASHMAP_OK or IKE_HASHMAP_MISSING.
 */
int ikeHashmapGetDouble(ikeHashmap* hashmap, const char *key, double *item);

/**
 * \brief Gets a string using hashmapified key.
 *
 * \param hashmap where value is stored.
 * \param key to hash.
 * \param item (output) to copy value from map.
 * \return IKE_HASHMAP_OK or IKE_HASHMAP_MISSING.
 */
int ikeHashmapGetString(ikeHashmap* hashmap, const char *key, char **item);

/**
 * \brief Remove an element from hashmap.
 *
 * \param hashmap where value is stored.
 * \param key to hash.
 * \return IKE_HASHMAP_OK or IKE_HASHMAP_MISSING.
 */
int ikeHashmapRemove(ikeHashmap* hashmap, const char *key);

/**
 * \brief Frees the memory of a hashmap.
 *
 * \param hashmap to be free.
 */
void ikeHashmapFree(ikeHashmap* hashmap);

/**
 * \brief Get the current size of a hashmap.
 *
 * \param hashmap to get size of.
 * \return count of elements.
 */
int ikeHashmapLength(ikeHashmap* hashmap);


#endif /* IKE_SPEC_H */
