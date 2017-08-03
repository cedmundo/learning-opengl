#include <transform.h>
#include <lmath/mat4.h>

mat4 loglTransformGetModel(loglTransform *transform) {
    mat4 t, s, r, rx, ry, rz;

    t = mat4_make_translation(transform->pos);
    s = mat4_make_scale(transform->sca);
    rx = mat4_make_rotation_x(transform->rot.x);
    ry = mat4_make_rotation_y(transform->rot.y);
    rz = mat4_make_rotation_z(transform->rot.z);
    r = mat4_mul(t, rx);
    r = mat4_mul(r, ry);
    r = mat4_mul(r, rz);

    return mat4_mul(s, r);
}

