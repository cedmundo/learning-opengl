#ifndef IKETESTING_MAT4_HELPER_H
#define IKETESTING_MAT4_HELPER_H
#include <math.h>
#include <stdio.h>

/**
 * \brief Compares two matrices.
 *
 * Comparision is done by rounding both internal values and comparing
 * each component, one by one.
 *
 * \return 1 if matrices are equal, 0 if doesn't.
 */
static inline int mat4IsAprox(mat4 a, mat4 b) {
    float *adata = a.raw;
    float *bdata = b.raw;
    static const char *pos = "XYZW";

    for(int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            int offset = i*4+j;
            float aval = adata[offset];
            float bval = bdata[offset];

            if (fabs(aval - bval) > 0.01) {
                fprintf(stderr, "Value not aproximately equal at (%c,%c)[offset %d]: a=%.4f, b=%.4f\n",
                        pos[i], pos[j], offset, aval, bval);
                return 0;
            }
        }
    }

    return 1;
}

/*
 * \brief Prints a debug message of a matrix
 *
 * \param mat a matrix to be printed on stderr.
 */
static inline void mat4PrintDebug(mat4 a, const char *name) {
    fprintf(stderr, "| Matrix: %s\n", name);
    fprintf(stderr, "| %+04.4f, %+04.4f, %+04.4f, %+04.4f |\n", a.xx, a.xy, a.xz, a.xw);
    fprintf(stderr, "| %+04.4f, %+04.4f, %+04.4f, %+04.4f |\n", a.yx, a.yy, a.yz, a.yw);
    fprintf(stderr, "| %+04.4f, %+04.4f, %+04.4f, %+04.4f |\n", a.zx, a.zy, a.zz, a.zw);
    fprintf(stderr, "| %+04.4f, %+04.4f, %+04.4f, %+04.4f |\n", a.wx, a.wy, a.wz, a.ww);
    fprintf(stderr, "\n");
}

#endif /* IKETESTING_MAT4_HELPER_H */

