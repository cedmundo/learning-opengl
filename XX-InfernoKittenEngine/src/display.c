#include <ike/display.h>
#include <ike/asset.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <msgpack.h>
#include <GLFW/glfw3.h>

int ikeDisplayConfig(ikeDisplay *display) {
    // Initialize to zero.
    display->title = NULL;
    display->height = 0;
    display->width = 0;
    display->window = NULL;

    msgpack_sbuffer sbuf;
    msgpack_sbuffer_init(&sbuf);

    // Dump file data
    if (ikeAssetGetHashMap("display", &sbuf) != IKE_ASSET_OK){
        return IKE_DISPLAY_FAILURE;
    }

    size_t offset = 0;
    msgpack_unpack_return ret;
    msgpack_zone mempool;
    msgpack_zone_init(&mempool, 2048);

    msgpack_object obj;
    ret = msgpack_unpack(sbuf.data, sbuf.size, &offset, &mempool, &obj);
    if (ret == MSGPACK_UNPACK_EXTRA_BYTES) {
        display->height = obj.via.i64;
    } else goto finalize;

    ret = msgpack_unpack(sbuf.data, sbuf.size, &offset, &mempool, &obj);
    if (ret == MSGPACK_UNPACK_EXTRA_BYTES) {
        display->width = obj.via.i64;
    } else goto finalize;

    ret = msgpack_unpack(sbuf.data, sbuf.size, &offset, &mempool, &obj);
    if (ret == MSGPACK_UNPACK_SUCCESS) {
        display->title = calloc(obj.via.raw.size+1, sizeof(char));
        strncpy(display->title, obj.via.raw.ptr, obj.via.raw.size);
    } else goto finalize;

finalize:
    msgpack_zone_destroy(&mempool);
    msgpack_sbuffer_destroy(&sbuf);
    return ret == MSGPACK_UNPACK_SUCCESS ? IKE_DISPLAY_OK : IKE_DISPLAY_FAILURE;
}

void ikeDisplayTerminate(ikeDisplay *display) {
    if (display->title != NULL) {
        free(display->title);
        display->title = NULL;
    }

    if (display->window != NULL) {
        glfwDestroyWindow(display->window);
        display->window = NULL;
    }
}
