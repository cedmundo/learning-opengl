#ifndef IKETESTING_QUAT_HELPER_H
#define IKETESTING_QUAT_HELPER_H
#include <check.h>
#include <math.h>
#include <stdio.h>

/**
 * \brief Compares two quaternions.
 *
 * Comparision is done by rounding both internal values and comparing
 * each component, one by one.
 *
 * \return 1 if matrices are aprox, 0 if aren't.
 */
static inline int quatIsAprox(quat a, quat b) {
    float *adata = a.wxyz;
    float *bdata = b.wxyz;
    static const char *pos = "WXYZ";

    for(int i=0;i<4;i++) {
        float aval = adata[i];
        float bval = bdata[i];

        if (fabs(aval - bval) > 0.01) {
            fprintf(stderr, "Value not aproximately equal at (%c)[offset %d]: a=%.4f, b=%.4f\n",
                    pos[i], i, aval, bval);
            return 0;
        }
    }
}

/*
 * \brief Prints a debug message of a quaternion
 *
 * \param quat a quaternion to be printed on stderr.
 * \param name a name to differentiate on stderr.
 */
static inline void quatPrintDebug(quat a, const char *name) {
    fprintf(stderr, "| Quat: %s\n", name);
    fprintf(stderr, "| %+04.4f, %+04.4f, %+04.4f, %+04.4f |\n", a.w, a.x, a.y, a.z);
}

#endif /* IKETESTING_QUAT_HELPER_H */

