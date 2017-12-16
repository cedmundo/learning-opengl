#ifndef IKE_IMAGE_DECODE_H
#define IKE_IMAGE_DECODE_H
#include <stddef.h>

// We do not care about ikeImage right now.
typedef struct _ikeImage ikeImage;

// We do not care about ikePool right now.
typedef struct _ikePool ikePool;

/**
 * \brief Decodes an image from a buffer reference.
 *
 * It will decode supported image formats from a byte array, (currently PNG only).
 *
 * \param image to dump raw pixel data.
 * \param pool to make controlled allocations.
 * \param data encoded (and compressed) pixel data.
 * \param len length of data.
 */
int ikeImageDecodeFromBuffer(ikeImage *image, ikePool *pool, const char *data, const size_t len);

#endif /* IKE_IMAGE_DECODE_H */
