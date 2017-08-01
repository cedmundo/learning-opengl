#include <transform.h>
#include <lmath/mat4.h>

mat4 loglTransformGetModel(loglTransform *transform) {
    mat4 t, r, rx, ry, rz, s, m;

    s = mat4_make_scale(transform->sca);
    rx = mat4_make_rotation_x(transform->rot.x);
    ry = mat4_make_rotation_y(transform->rot.y);
    rz = mat4_make_rotation_z(transform->rot.z);
    m = mat4_mul(s, rx);
    m = mat4_mul(m, ry);
    m = mat4_mul(m, rz);
    t = mat4_make_translation(transform->pos);
    m = mat4_mul(m, t);
    return m;
}
