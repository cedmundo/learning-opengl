#include <ike/spec.h>
#include <ike/pool.h>
#include <ike/hashmap.h>
#include <ike/mathutil.h>
#include <stdlib.h>
#include <string.h>

#define TEMPLATE_PUT(_ctype, _itype, _spec, _key, _val) _ctype *_vcpy = (_ctype *) ikePoolGet(_spec->pool, sizeof(_ctype)); \
    *_vcpy = _val; \
    ikeSpecItem *_item = (ikeSpecItem *) ikePoolGet(_spec->pool, sizeof(ikeSpecItem)); \
    _item->type = _itype; \
    _item->value = _vcpy; \
    _item->key = _key; \
    int _code = ikeHashmapPut(_spec->hashmap, _key, _item); \
    if (_code == IKE_HASHMAP_OK) { \
        return IKE_SPEC_OK; \
    } else { \
        return IKE_SPEC_OUT_OF_MEMORY; \
    }

#define TEMPLATE_GET(_ctype, _itype, _spec, _key, _val) ikeSpecItem *_item; \
    int _code = ikeHashmapGet(_spec->hashmap, _key, (void **) &_item); \
    if (_code == IKE_HASHMAP_OK) { \
        if (_item->type != _itype) { \
            return IKE_SPEC_INVALID_TYPE; \
        } \
        *_val = *((_ctype *) _item->value); \
        return IKE_SPEC_OK; \
    } else { \
        return _code; \
    }


// Iterates over a hashmap looking for nested specs to destroy.
int ikeNestedSpecDestructor(ikeAny item, ikeAny hashmap);

int ikeSpecInit(ikeSpec *spec) {
    // Default values for spec.
    int status = IKE_SPEC_OK;
    int code = 0;
    spec->pool = malloc(sizeof(ikePool));
    if (spec->pool == NULL) {
        code = IKE_SPEC_OUT_OF_MEMORY; goto finalize;
    }

    spec->hashmap = malloc(sizeof(ikeHashmap));
    if (spec->hashmap == NULL) {
        code = IKE_SPEC_OUT_OF_MEMORY; goto finalize;
    }

    code = ikePoolInit(spec->pool, IKE_POOL_SMALL);
    if (code == IKE_POOL_OUT_OF_MEMORY) {
        code = IKE_SPEC_OUT_OF_MEMORY; goto finalize;
    }

    code = ikeHashmapInit(spec->hashmap);
    if (code == IKE_HASHMAP_OMEM) {
        code = IKE_SPEC_OUT_OF_MEMORY; goto finalize;
    }

finalize:
    if (code != IKE_SPEC_OK)
        ikeSpecDestroy(spec);

    return status;
}

void ikeSpecDestroy(ikeSpec *spec) {
    ikeHashmapIterate(spec->hashmap, ikeNestedSpecDestructor, NULL);

    if (spec->pool != NULL) {
        ikePoolDestroy(spec->pool);
        free(spec->pool);
        spec->pool = NULL;
    }

    if (spec->hashmap != NULL) {
        ikeHashmapDestroy(spec->hashmap);
        free(spec->hashmap);
        spec->hashmap = NULL;
    }
}

int ikeNestedSpecDestructor(ikeAny _unused0, ikeAny aitem) {
    ikeSpecItem *item = (ikeSpecItem *) aitem;
    if (item->type == SPEC) {
        ikeSpecDestroy(item->value);
    }

    return IKE_HASHMAP_OK;
}

int ikeSpecGetInt(ikeSpec* spec, const char *key, int *value) {
    TEMPLATE_GET(int, INT, spec, key, value);
}

int ikeSpecPutInt(ikeSpec* spec, const char *key, int value) {
    TEMPLATE_PUT(int, INT, spec, key, value);
}

int ikeSpecGetFloat(ikeSpec* spec, const char *key, float *value) {
    TEMPLATE_GET(float, FLOAT, spec, key, value);
}

int ikeSpecPutFloat(ikeSpec* spec, const char *key, float value) {
    TEMPLATE_PUT(float, FLOAT, spec, key, value);
}

int ikeSpecGetString(ikeSpec* spec, const char *key, const char **value) {
    ikeSpecItem *item;
    int code = ikeHashmapGet(spec->hashmap, key, (void **) &item);
    if (code == IKE_HASHMAP_OK) {
        if (item->type != STRING) {
            return IKE_SPEC_INVALID_TYPE;
        }
        *value = (char *)item->value;
        return IKE_SPEC_OK;
    } else {
        return code;
    }
}

int ikeSpecPutString(ikeSpec* spec, const char *key, const char *value) {
    size_t len = strlen(value);
    char *ccpy = (char *) ikePoolGet(spec->pool, len+1);
    strncpy(ccpy, value, len);

    ikeSpecItem *item = (ikeSpecItem *) ikePoolGet(spec->pool, sizeof(ikeSpecItem));
    item->type = STRING;
    item->value = ccpy;
    item->key = key;
    int code = ikeHashmapPut(spec->hashmap, key, item);
    if (code == IKE_HASHMAP_OK) {
        return IKE_SPEC_OK;
    } else {
        return IKE_SPEC_OUT_OF_MEMORY;
    }
}

int ikeSpecGetSpec(ikeSpec* spec, const char *key, ikeSpec *value) {
    TEMPLATE_GET(ikeSpec, SPEC, spec, key, value);
}

int ikeSpecPutSpec(ikeSpec* spec, const char *key, ikeSpec *ref) {
    ikeSpec value = *ref;
    TEMPLATE_PUT(ikeSpec, SPEC, spec, key, value);
}

