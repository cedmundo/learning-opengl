#ifndef IKE_CONTENT_H
#define IKE_CONTENT_H
#include <stddef.h>

/*
 * \brief Sets the root for asset for loading objects.
 *
 * \param char *path with trailing slash.
 *
 */
void ikeAssetSetBase(const char *path);

/*
 * \brief Reads the entire file into data charactes.
 *
 * Reads contents of requested asset as text into output parameter data, automatically
 * allocates the required memory reporting the size with output parameter len.
 *
 * Warning: data must be free after use, see ikeAssetFree() for more information.
 *
 * \param file to read
 * \param data to dump asset.
 * \param len to dump asset length.
 * \return int 0 if success, 1 otherwise.
 */
int ikeAssetGetText(const char *file, char **data, size_t *len);

/*
 * \brief Releases memory for any loaded asset.
 */
void ikeAssetFree(void **);

#endif /* IKE_CONTENT_H */
