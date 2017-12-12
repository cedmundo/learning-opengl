#include <ike/asset.h>
#include <ike/spec.h>
#include <ike/spec_decode.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int ikeAssetGetSpec(const char* rpath, ikeSpec *spec) {
    char *apath = assetpath(bpath, rpath, ".spec");
    char *data = NULL;
    int status = IKE_ASSET_OK;
    size_t len = 0L;

    int res = readFile(apath, &data, &len);
    if (res != IKE_ASSET_OK) {
        status = IKE_ASSET_FAILURE; goto finalize;
    }

    res = ikeSpecDecodeFromBuffer(spec, data, len);
    if (res != IKE_SPEC_OK) {
        status = IKE_ASSET_FAILURE; goto finalize;
    }

finalize:
    free(apath);

    if (data != NULL)
        free(data);

    return res;
}

void ikeAssetFree(char **data) {
    if (*data != NULL)
        free(*data);

    *data = NULL;
}
