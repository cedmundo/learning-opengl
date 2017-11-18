#include <ike/asset.h>
#include <ike/spec.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <msgpack.h>

static const char *bpath = (void *) 0;
static size_t bpathl = 0;

void ikeAssetSetBase(const char* newbase) {
    bpath = newbase;
    bpathl = strlen(newbase);
}

char *assetpath(const char *base, const char *name, const char *ext){
    size_t basel = strlen(base);
    size_t namel = strlen(name);
    size_t extl = strlen(ext);

    // Note: 2 because a leading zero and a space for a possible slash '/'
    char *absolute = calloc(namel+basel+extl+2, sizeof(char));
    if (absolute == NULL)
        return absolute;

    strcat(absolute, base);
    if ( (namel > 0 ? name[namel-1] : 0) != '/' && (base > 0 ? base[basel-1] : 0) != '/') {
        strcat(absolute, "/");
    }

    strcat(absolute, name);
    strcat(absolute, ext);
    return absolute;
}

int readFile(const char *path, char **data, size_t *len) {
    int excode = IKE_ASSET_OK;
    FILE *pfile = fopen(path, "r");
    if (pfile == NULL) {
        excode = IKE_ASSET_FAILURE; goto finalize;
    }

    size_t tlen = 0;
    fseek(pfile, 0L, SEEK_END);
    tlen = ftell(pfile);
    rewind(pfile);

    if (len != NULL) {
        *len = tlen;
    }

    *data = calloc(tlen, sizeof(char));
    size_t rlen = fread(*data, sizeof(char), tlen, pfile);
    excode = rlen != tlen;

finalize:
    if (pfile != NULL)
        fclose(pfile);

    return excode;
}

int ikeAssetGetText(const char *rpath, char **data, size_t *len) {
    char *apath = assetpath(bpath, rpath, ".txt");
    int res = readFile(apath, data, len);
    free(apath);
    return res;
}

int ikeAssetGetSpec(const char* rpath, ikeSpec* spec) {
    msgpack_zone *mempool = NULL;
    char *data = NULL;
    size_t len = 0;
    char *apath = assetpath(bpath, rpath, ".spec");
    int excode = IKE_ASSET_OK;

    if (readFile(apath, &data, &len) != IKE_ASSET_FAILURE) {
        excode = IKE_ASSET_FAILURE; goto finalize;
    }

    mempool = calloc(1, sizeof(msgpack_zone));
    msgpack_zone_init(mempool, 512);

    // Memory pool will be released when spec is released
    if (ikeSpecPut(spec, "_release", mempool) != IKE_SPEC_MAP_OK) {
        excode = IKE_ASSET_FAILURE; goto finalize;
    }

    int pr = 0;
    size_t offset = 0;
    msgpack_unpack_return ret;
    msgpack_object obj;

    ret = msgpack_unpack(data, len, &offset, mempool, &obj);
    pr = ikeSpecPutObj(spec, obj);

    while((ret == MSGPACK_UNPACK_EXTRA_BYTES || ret == MSGPACK_UNPACK_CONTINUE) && pr == IKE_SPEC_MAP_OK) {
        ret = msgpack_unpack(data, len, &offset, mempool, &obj);
        pr = ikeSpecPutObj(spec, obj);
    }

finalize:
    if (apath != NULL)
        free(apath);

    if (data != NULL)
        free(data);

    if (excode != IKE_ASSET_OK && mempool != NULL) {
        // Since we haven't created the map, we should remove memory of memory pool.
        msgpack_zone_destroy(mempool);
    }

    return excode;
}

int ikeSpecPutObj(ikeSpec *spec, msgpack_object obj) {
    if (obj.type == MSGPACK_OBJECT_MAP) {

    }

    return IKE_SPEC_MAP_OK;
}

void ikeAssetFree(char **data) {
    if (*data != NULL)
        free(*data);

    *data = NULL;
}
