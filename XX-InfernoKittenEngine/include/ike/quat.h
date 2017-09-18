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
        float x;
        float y;
        float z;
        float w;
    };
    float xyzw[4];
} quat;

static const quat quatIdentity = {0, 0, 0, 1};

/**
 * \brief Add two quaternions.
 *
 * Adds two vec4 variables, returning the result as a new vector (on stack).
 * \param vec4 a is the left operand.
 * \param vec4 b is the right operand.
 * \return a vec4 with the sum of components of a and b.
 */
static inline quat quatAdd(const quat a, const quat b) {
    quat r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    r.w = a.w + b.w;
    return r;
}

/**
 * \brief Makes a quat using x, y, z and w components.
 *
 * Make a vector which components are equal to x, y, z and w params.
 * \param x new quaternion's X component.
 * \param y new quaternion's Y component.
 * \param z new quaternion's Z component.
 * \param w new quaternion's W component.
 * \return newly created quaternion (stack).
 */
static inline quat quatMake(float x, float y, float z, float w) {
    quat r;
    r.x = x;
    r.y = y;
    r.z = z;
    r.w = w;
    return r;
}


#endif /* IKE_QUAT_H */
