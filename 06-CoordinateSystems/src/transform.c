#include <transform.h>
#include <lmath/mat4.h>

mat4 logl_transform_get_model(loglTransform *transform) {
    mat4 t, r, rx, ry, rz, s, m;

    s = mat4_make_scale(transform->sca);
    t = mat4_make_translation(transform->pos);
    rx = mat4_make_rotation_x(transform->rot.x);
    ry = mat4_make_rotation_y(transform->rot.y);
    rz = mat4_make_rotation_z(transform->rot.z);
    r = mat4_mul(rx, mat4_mul(ry, rz));

    return mat4_mul(r, mat4_mul(t, s));
}
