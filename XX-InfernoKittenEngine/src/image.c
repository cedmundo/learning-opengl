#include <ike/image.h>
#include <stddef.h>

void ikeImageInit(ikeImage *image) {
    image->data = NULL;
    image->size = (size_t) 0L;
    image->format = NONE;
    image->width = 0;
    image->height = 0;
}

