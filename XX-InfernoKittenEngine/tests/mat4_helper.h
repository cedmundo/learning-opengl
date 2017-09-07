#ifndef IKETESTING_MAT4_HELPER_H
#define IKETESTING_MAT4_HELPER_H

/**
 * \brief Compares two matrices.
 *
 * Comparision is done by rounding both internal values and comparing
 * each component, one by one.
 *
 * \return 1 if matrices are equal, 0 if doesn't.
 */
static inline int mat4_is_aprox(mat4 a, mat4 b) {
    float *adata = a.raw;
    float *bdata = b.raw;

    for(int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            int offset = i*4+j;
            if (ROUND4(adata[offset]) != ROUND4(bdata[offset])) {
                return 0;
            }
        }
    }

    return 1;
}

#endif /* IKETESTING_MAT4_HELPER_H */

