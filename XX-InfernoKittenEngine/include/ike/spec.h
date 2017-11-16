#ifndef IKE_SPEC_H
#define IKE_SPEC_H
#include <stdio.h>

#define IKE_SPEC_MAP_MISSING (-3) // No such element
#define IKE_SPEC_MAP_FULL (-2) // Full
#define IKE_SPEC_MAP_OMEM (-1) // Out Of Memory
#define IKE_SPEC_MAP_OK (0) // Ok

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
 * other than IKE_SPEC_MAP_OK the traversal is terminated. Also, it's highly
 * recommended to not reenter any Spec functions, or deadlock may arise.
 */
typedef int (*ikeSpecIterator)(ikeAny, ikeAny);

/* We need to keep keys and values */
typedef struct _ikeSpecElement {
	const char* key;
	int inuse;
	ikeAny data;
} ikeSpecElement;

/**
 * \brief Forward declaration for ikeSpec.
 *
 * Clients should use only ikeSpec exported functions to handle data
 * within a spec, which is basically a HashMap, implementation borrowed
 * (re-written and sighlty modified for code style propouses) from https://github.com/petewarden/c_hashmap.
 */
typedef struct _ikeSpec {
    int tablesize;
    int size;
    ikeSpecElement *data;
} ikeSpec;

/**
 * \brief Inits an ikeSpec.
 * \param spec that is going to be inited.
 */
int ikeSpecInit(ikeSpec* spec);

/**
 * \brief Iterate over items of spec.
 *
 * Iteratively call iter param with (userdata, itemdata) as argument for each
 * element data in spec.
 *
 * \param spec map to iterate.
 * \param iter function to call.
 * \param userdata first argument of call.
 * \return
 */
int ikeSpecIterate(ikeSpec* spec, ikeSpecIterator iter, ikeAny userdata);

/**
 * \brief Puts a value with specified key.
 *
 * \param spec where value is going to be stored.
 * \param key to hash.
 * \param item to store.
 * \return IKE_SPEC_MAP_OK or IKE_SPEC_MAP_OMEM.
 */
int ikeSpecPut(ikeSpec* spec, const char *key, ikeAny item);


/**
 * \brief Gets a value using specified key.
 *
 * \param spec where value is stored.
 * \param key to hash.
 * \param item (output) to copy value from map.
 * \return IKE_SPEC_MAP_OK or IKE_SPEC_MAP_MISSING.
 */
int ikeSpecGet(ikeSpec* spec, const char *key, ikeAny *item);

/**
 * \brief Remove an element from spec.
 *
 * \param spec where value is stored.
 * \param key to hash.
 * \return IKE_SPEC_MAP_OK or IKE_SPEC_MAP_MISSING.
 */
int ikeSpecRemove(ikeSpec* spec, const char *key);

/**
 * \brief Frees the memory of a spec.
 *
 * \param spec to be free.
 */
void ikeSpecFree(ikeSpec* spec);

/**
 * \brief Get the current size of a spec.
 *
 * \param spec to get size of.
 * \return count of elements.
 */
int ikeSpecLength(ikeSpec* spec);


#endif /* IKE_SPEC_H */
