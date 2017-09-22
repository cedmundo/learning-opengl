#ifndef IKE_QUAT_H
#define IKE_QUAT_H

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
 * \return a vec4 with the sum of components of a and b.
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

#endif /* IKE_QUAT_H */
