#include <ike/asset.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static const char *bpath = (void *) 0;
static size_t bpathl = 0;

void ikeAssetSetBase(const char *newbase) {
    bpath = newbase;
    bpathl = strlen(newbase);
}

char *assetpath(const char *trail){
    size_t traill = strlen(trail);

    // Note: 2 because a leading zero and a space for a possible slash '/'
    char *absolute = calloc(traill+bpathl+2, sizeof(char));

    strcat(absolute, bpath);
    if ( (traill > 0 ? trail[traill-1] : 0) != '/' && (bpath > 0 ? bpath[bpathl-1] : 0) != '/') {
        strcat(absolute, "/");
    }

    strcat(absolute, trail);
    return absolute;
}

int ikeAssetGetText(const char *rpath, char **data, size_t *len) {
    char *apath = assetpath(rpath);
    FILE *tfile = fopen(apath, "r");
    if (tfile == NULL)
        return 0;

    size_t tlen = 0;
    fseek(tfile, 0L, SEEK_END);
    tlen = ftell(tfile);
    rewind(tfile);

    if (len != NULL) {
        *len = tlen;
    }

    *data = calloc(tlen, sizeof(char));
    return fread(*data, sizeof(char), tlen, tfile) == tlen;
}

void ikeAssetFree(void **data) {
    if (*data != NULL)
        free(*data);

    *data = NULL;
}
