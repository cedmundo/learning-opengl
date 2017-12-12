#ifndef IKE_CONTENT_H
#define IKE_CONTENT_H
#include <stddef.h>

#define IKE_ASSET_OK 0
#define IKE_ASSET_FAILURE 1

// We do not care about ikeSpec right now.
typedef struct _ikeSpec ikeSpec;

/*
 * \brief Sets the root for asset for loading objects.
 *
 * \param char *path with trailing slash.
 *
 */
void ikeAssetSetBase(const char *path);

/*
 * \brief Reads the entire file into data charactrs.
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
int ikeAssetGetText(const char* file, char** data, size_t* len);

/*
 * \brief Reads a spec file.
 *
 * Reads a file and puts results into spec param, it must be pre-initialized.
 *
 * Warning: data must be destroyed using ikeSpecDestroy(...).
 *
 * \param file to read
 * \param spec to dump asset.
 * \return int 0 if success, 1 otherwise.
 */
int ikeAssetGetSpec(const char* file, ikeSpec *spec);

/*
 * \brief Releases memory for any loaded asset.
 */
void ikeAssetFree(char**);

#endif /* IKE_CONTENT_H */
