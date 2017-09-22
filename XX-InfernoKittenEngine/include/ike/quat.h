#ifndef IKE_QUAT_H
#define IKE_QUAT_H
#include <math.h>

/**
 * \brief Quaternion representation.
 *
 * A defined union to hold references of A1, A2, A3 and A4 components of a quaterion A, also accessibe
 * as 4-dimetion array.
 */
typedef union {
    struct {
        float w;
        float x; // xi
        float y; // yj
        float z; // zk
    };
    float wxyz[4];
} quat;

static const quat quatIdentity = {1, 0, 0, 0};

/**
 * \brief Makes a quat using x, y, z and w components.
 *
 * Make a vector which components are equal to x, y, z and w params.
 * \param w new quaternion's W component.
 * \param x new quaternion's X component.
 * \param y new quaternion's Y component.
 * \param z new quaternion's Z component.
 * \return newly created quaternion (stack).
 */
static inline quat quatMake(float w, float x, float y, float z) {
    quat r;
    r.w = w;
    r.x = x;
    r.y = y;
    r.z = z;
    return r;
}

/**
 * \brief Add two quaternions.
 *
 * Adds two quat variables, returning the result as a new vector (on stack).
 * \param quat a is the left operand.
 * \param quat b is the right operand.
 * \return a quaternion with the sum of components of a and b.
 */
static inline quat quatAdd(const quat a, const quat b) {
    quat r;
    r.w = a.w + b.w;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

/**
 * \brief Scales a quat.
 *
 * Multiplies all components by factor s, returning result as a new vector (on stack).
 * \param quat a is the vector to scale.
 * \param s is the scalar factor.
 * \return the scalation result.
 */
static inline quat quatScale(const quat a, const float s) {
    quat r;
    r.x = a.x * s;
    r.y = a.y * s;
    r.z = a.z * s;
    r.w = a.w * s;
    return r;
}

/**
 * \brief Multiplies two quaternions.
 *
 * Multiplies two quat variables, returning the result as a new quaternion.
 * \param quat a is the left operand.
 * \param quat b is the right operand.
 * \return multiplication result.
 */
static inline quat quatMul(const quat a, const quat b) {
    quat r;
    r.w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z;
    r.x = a.w*b.x + a.x*b.w - a.y*b.z + a.z*b.y;
    r.y = a.w*b.y + a.x*b.z + a.y*b.w - a.z*b.x;
    r.z = a.w*b.z - a.x*b.y + a.y*b.x + a.z*b.w;
    return r;
}

/**
 * \brief Normalizes a quaternion.
 *
 * Normalize all components of a quaternion.
 * \param quat to normalize.
 * \return a normalized quaternion from param a.
 */
static inline quat quatNorm(const quat a) {
    quat r;
    float m = sqrtf(a.w*a.w + a.x*a.x + a.y*a.y + a.z*a.z);
    r.w = a.w/m;
    r.x = a.x/m;
    r.y = a.y/m;
    r.z = a.z/m;
    return r;
}

/**
 * \brief Conjugate a quaternion.
 *
 * Conjugates a quaternion.
 * \param quat to conjugate.
 * \return a conjugated quaternion from param a.
 */
static inline quat quatConjugate(const quat a) {
    quat r;
    r.w = a.w;
    r.x = -a.x;
    r.y = -a.y;
    r.z = -a.z;
    return r;
}

#endif /* IKE_QUAT_H */
