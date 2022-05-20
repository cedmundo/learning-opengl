//
// Created by Carlos on 16/05/2022.
//
#include <stdio.h>
#include <stdlib.h>

char *load_text_file(const char *name) {
    FILE *file = fopen(name, "r");
    if (file == NULL) {
        return NULL;
    }

    size_t file_size = 0L;
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = calloc(sizeof(char), file_size);
    size_t read_size = fread(data, sizeof(char), file_size, file);
    if (read_size == 0) {
        fclose(file);
        free(data);
        return NULL;
    }

    return data;
}

void unload_text_file(char *data) {
    if (data != NULL) {
        free(data);
    }
}