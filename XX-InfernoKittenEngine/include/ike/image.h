#ifndef IKE_IMAGE_H
#define IKE_IMAGE_H
#include <stddef.h>

#define IKE_IMAGE_OK (0)
#define IKE_IAMAGE_BAD_FORMAT (1)
#define IKE_IAMAGE_BAD_PIXFMT (2)

/**
 * Supported pixel formats, which contain
 * color channel profile and depth.
 */
typedef enum _ikePixelFormat {
    NONE = 0,
    GRAY16,
    GRAY8,
    GRAY4,
    RGBA8888,
    RGBA4444,
    RGB888,
    RGB444,
} ikePixelFormat;

/**
 * An interface to communicate data between OpenGL
 * and loaded data from a file or memory, commonly from
 * a ikePool filled by image encoder.
 *
 * To load an image from a file, see image_decode.h.
 */
typedef struct _ikeImage {
    char *data;
    size_t size;
    ikePixelFormat format;
    unsigned int height;
    unsigned int width;
} ikeImage;

/**
 * Only sets image's values to defaults, no memory is allocated
 * so ikeImageDestroy would be useless.
 *
 * To properly create images, just instance a new ikeImage, initialize it
 * and dump data from external encoding.
 *
 * \param ikeImage image to iniImagetialize.
 */
void ikeImageInit(ikeImage *image);

#endif
