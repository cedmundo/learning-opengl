#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <msgpack.h>

#define strarg(target, ol) do{ol=strlen(optarg);target=calloc(ol, sizeof(char));strncpy(target, optarg, ol);}while(0);
#define intarg(target) do{target=atoi(optarg);}while(0);
char *assetpath(const char *base, const char* name, const char *ext);

int main(int argc, char *argv[]){
    int opt = 0, height = 800, width = 600, ibuf = 0, excode = 0;
    size_t titlel = 0, basel = 0;
    FILE* output = NULL;
    char* title = NULL;
    char* base = NULL;
    char* opath = NULL;

    while ((opt = getopt (argc, argv, "ha:t:H:W:")) != -1) {
        switch (opt) {
            case ':':
            case '?':
            case 'h':
                printf("Usage: %s [OPTIONS]\n", argv[0]);
                printf("  -a assets                 assets base folder (required)\n");
                printf("  -t title                  window title (required)\n");
                printf("  -H height                 window height\n");
                printf("  -W width                  window width\n");
                printf("  -h, --help                print this help and exit\n");
                printf("\n");
                excode = 1; goto finalize;
            case 'a':
                strarg(base, titlel);
                break;
            case 't':
                strarg(title, basel);
                break;
            case 'H':
                intarg(height);
                break;
            case 'W':
                intarg(width);
                break;
            default:
                fprintf(stderr, "%s: invalid option -- %c\n", argv[0], opt);
                fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
                excode = 1; goto finalize;
        }
    }

    if (base == NULL) {
        fprintf(stderr, "%s: required option -- a\n", argv[0]);
        excode = 1; goto finalize;
    }

    if (title == NULL) {
        fprintf(stderr, "%s: required option -- t\n", argv[0]);
        excode = 1; goto finalize;
    }

    msgpack_sbuffer sbuf;
    msgpack_packer pk;

    msgpack_sbuffer_init(&sbuf); ibuf = 1;
    msgpack_packer_init(&pk, &sbuf, msgpack_sbuffer_write);

    msgpack_pack_int(&pk, height);
    msgpack_pack_int(&pk, width);
    msgpack_pack_raw(&pk, titlel);
    msgpack_pack_raw_body(&pk, title, titlel);

    opath = assetpath(base, "display", ".spec");
    output = fopen(opath, "w");
    if (output == NULL) {
        excode = 1; goto finalize;
    }

    fwrite(sbuf.data, sizeof(char), sbuf.size, output);
    printf("Configuration written: %dx%d - '%s' on '%s'.\n", height, width, title, opath);

finalize:
    if (ibuf != 0)
        msgpack_sbuffer_destroy(&sbuf);

    if (title != NULL)
        free(title);

    if (base != NULL)
        free(base);

    if (opath != NULL)
        free(opath);

    if (output != NULL)
        fclose(output);

    return excode;
}

char *assetpath(const char *base, const char* name, const char *ext){
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
