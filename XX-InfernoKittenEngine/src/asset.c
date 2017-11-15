#include <ike/asset.h>
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

char *assetpath(const char* trail, const char *ext){
    size_t traill = strlen(trail);
    size_t extl = strlen(ext);

    // Note: 2 because a leading zero and a space for a possible slash '/'
    char *absolute = calloc(traill+bpathl+extl+2, sizeof(char));

    strcat(absolute, bpath);
    if ( (traill > 0 ? trail[traill-1] : 0) != '/' && (bpath > 0 ? bpath[bpathl-1] : 0) != '/') {
        strcat(absolute, "/");
    }

    strcat(absolute, trail);
    strcat(absolute, ext);
    return absolute;
}

int ikeAssetGetText(const char *rpath, char **data, size_t *len) {
    char *apath = assetpath(rpath, ".txt");
    FILE *tfile = fopen(apath, "r");
    if (tfile == NULL)
        return IKE_ASSET_FAILURE;

    size_t tlen = 0;
    fseek(tfile, 0L, SEEK_END);
    tlen = ftell(tfile);
    rewind(tfile);

    if (len != NULL) {
        *len = tlen;
    }

    *data = calloc(tlen, sizeof(char));
    size_t rlen = fread(*data, sizeof(char), tlen, tfile);
    return rlen != tlen;
}

int ikeAssetGetSpec(const char* rpath, msgpack_sbuffer* sbuf) {
    char *apath = assetpath(rpath, ".spec");
    FILE *tfile = fopen(apath, "rb");
    if (tfile == NULL)
        return IKE_ASSET_FAILURE;

    size_t tlen = 0;
    fseek(tfile, 0L, SEEK_END);
    tlen = ftell(tfile);
    rewind(tfile);
    sbuf->size = tlen;

    sbuf->data = calloc(tlen, sizeof(char));
    return fread(sbuf->data, sizeof(char), tlen, tfile) != tlen;
}

void ikeAssetFree(char **data) {
    if (*data != NULL)
        free(*data);

    *data = NULL;
}
