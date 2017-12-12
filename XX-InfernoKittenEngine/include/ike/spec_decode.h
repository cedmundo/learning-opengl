#ifndef IKE_SPEC_DECODE_H
#define IKE_SPEC_DECODE_H
#include <stddef.h>
#define MSGPACK_POOL_TINY 512

// We do not care about ikeSpec right now.
typedef struct _ikeSpec ikeSpec;

/**
 * \brief Decodes a spec from a byte buffer.
 *
 * It will decode supported types for spec from a byte buffer using msgpack format.
 * Not supported types will terminate the processing and function will return IKE_SPEC_INVALID_TYPE.
 *
 * \param spec to dump data.
 * \param data buffer.
 * \param len size of buffer.
 * \return IKE_SPEC_OK, IKE_SPEC_INVALID_TYPE or IKE_SPEC_OUT_OF_MEMORY
 */
int ikeSpecDecodeFromBuffer(ikeSpec *spec, char *data, size_t len);

#endif /* IKE_SPEC_DECODE_H */
