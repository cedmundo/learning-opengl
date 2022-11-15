//
// Created by carlos on 5/31/22.
//

#ifndef LEARNING_OPENGL_TGA_H
#define LEARNING_OPENGL_TGA_H
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

enum tga_load_status {
    TGA_LOAD_SUCCESS,
    TGA_LOAD_NOT_A_TGA,
    TGA_LOAD_UNKNOWN_ERROR
};

enum tga_load_flags {
    TGA_LOAD_NO_FLAGS,
};

struct tga_header {
    uint8_t id_len[1];
    uint8_t colormap_type[1];
    uint8_t data_type_code[1];
    uint8_t colormap_spec[5];
    uint8_t image_spec[10];
};
static_assert(sizeof(struct tga_header) == 18, "tga_header has padding");

struct tga_image_data {
    uint8_t *image_id;
    uint8_t *colormap_data;
    uint8_t *image_data;
};

enum tga_load_status tga_load_from_file(const char *file);
#endif //LEARNING_OPENGL_TGA_H
