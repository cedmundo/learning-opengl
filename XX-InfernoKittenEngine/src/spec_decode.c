#include <stddef.h>
#include <ike/spec.h>
#include <ike/spec_decode.h>
#include <ike/pool.h>
#include <msgpack.h>

int ikeSpecDecodeFromMap(ikeSpec *spec, msgpack_object_map map);

int ikeSpecDecodeFromBuffer(ikeSpec *spec, const char *data, const size_t len) {
    int status = IKE_SPEC_OK;
    msgpack_zone *mempool = NULL;
    mempool = calloc(1, sizeof(msgpack_zone));
    if (mempool == NULL) {
        status = IKE_SPEC_OUT_OF_MEMORY; goto finalize;
    }

    msgpack_zone_init(mempool, MSGPACK_POOL_TINY);
    msgpack_unpack_return ret;
    msgpack_object obj;
    size_t offset = 0;

    ret = msgpack_unpack(data, len, &offset, mempool, &obj);
    if (obj.type != MSGPACK_OBJECT_MAP) {
        status = IKE_SPEC_INVALID_TYPE; goto finalize;
    }

    msgpack_object_map map = obj.via.map;
    status = ikeSpecDecodeFromMap(spec, map);

finalize:
    if (mempool != NULL) {
        msgpack_zone_destroy(mempool);
        free(mempool);
    }

    return status;
}

int ikeSpecDecodeFromMap(ikeSpec *spec, msgpack_object_map map) {
    int status = IKE_SPEC_OK;
    for(size_t i = 0;i<map.size;i++) {
        msgpack_object_kv pair = map.ptr[i];

        // Convert byte buffer to string
        msgpack_object pkey = pair.key;
        if (pkey.type != MSGPACK_OBJECT_RAW) {
            status = IKE_SPEC_INVALID_TYPE; goto finalize;
        }

        char *key = (char *) ikePoolGet(spec->pool, pkey.via.raw.size+1);
        strncpy(key, pkey.via.raw.ptr, pkey.via.raw.size);
        msgpack_object val = pair.val;
        ikeSpec child;

        switch(val.type) {
            case MSGPACK_OBJECT_BOOLEAN:
            case MSGPACK_OBJECT_POSITIVE_INTEGER:
            case MSGPACK_OBJECT_NEGATIVE_INTEGER:
                status = ikeSpecPutInt(spec, key, (int) val.via.i64); // Warning: truncation.
                break;
            case MSGPACK_OBJECT_DOUBLE:
                status = ikeSpecPutFloat(spec, key, (float) val.via.dec); // Warning: truncation.
                break;
            case MSGPACK_OBJECT_RAW:
                status = ikeSpecPutStringSize(spec, key, val.via.raw.ptr, val.via.raw.size);
                break;
            case MSGPACK_OBJECT_MAP:
                status = ikeSpecInit(&child);
                if (status != IKE_SPEC_OK) {
                    goto finalize;
                }

                status = ikeSpecDecodeFromMap(&child, val.via.map);
                if (status != IKE_SPEC_OK) {
                    goto finalize;
                }

                ikeSpecPutSpec(spec, key, &child);
                break;
            default:
                status = IKE_SPEC_INVALID_TYPE;
                goto finalize;
        }

        if (status != IKE_SPEC_OK)
            goto finalize;
    }

finalize:
    return status;
}
