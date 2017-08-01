#include <camera.h>
#include <lmath/lmath.h>
#include <GLFW/glfw3.h>

void loglCameraUpdateAspect(loglCamera *camera) {
    int width, height;
    glfwGetWindowSize(camera->window, &width, &height);
    camera->aspect = (float)width/(float)height;
    camera->winWidth = width;
    camera->winHeight = height;
}

void loglCameraInit(loglCamera *camera, GLFWwindow *window) {
    camera->transform.pos = vec3_zero;
    camera->front = vec3_make(0.f, 0.f, -1.f);
    camera->up = vec3_up;
    camera->window = window;
    camera->fov = lmath_radians(45.0f);
    camera->near = 0.1f;
    camera->far = 100.0f;
    camera->isFirstMouse = 1;

    loglCameraUpdateAspect(camera);
    camera->lastMousePos = vec2_make(camera->winWidth/2, camera->winHeight/2);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void loglCameraUpdate(loglCamera *camera, float dt) {
    GLFWwindow *window = camera->window;
    float cameraSpeed = 2.5f * dt;
    vec3 pos = camera->transform.pos;
    loglCameraUpdateAspect(camera);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->transform.pos = vec3_add(pos, vec3_scale(camera->front, cameraSpeed));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->transform.pos = vec3_add(pos, vec3_scale(camera->front, -cameraSpeed));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->transform.pos = vec3_add(pos, vec3_scale(vec3_norm(vec3_mul_cross(camera->front, camera->up)), -cameraSpeed));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->transform.pos = vec3_add(pos, vec3_scale(vec3_norm(vec3_mul_cross(camera->front, camera->up)), cameraSpeed));

    double mxpos, mypos;
    glfwGetCursorPos(window, &mxpos, &mypos);
    if (camera->isFirstMouse) {
        camera->lastMousePos = vec2_make(mxpos, mypos);
        camera->isFirstMouse = 0;
    }

    double lastx = (double) camera->lastMousePos.x;
    double lasty = (double) camera->lastMousePos.y;
    double mxoff = mxpos - lastx;
    double myoff = lasty - mypos;

    float sensitivity = 0.05;
    mxoff *= sensitivity;
    myoff *= sensitivity;

    vec3 rot = camera->transform.rot;
    rot.yaw += mxoff;
    rot.pitch += myoff;
    if (rot.pitch > 89.0f)
        rot.pitch = 89.0f;
    if (rot.pitch < -89.0f)
        rot.pitch = -89.0f;

    vec3 front;
    front.x = cosf(lmath_radians(rot.yaw)) * cosf(lmath_radians(rot.pitch));
    front.y = sinf(lmath_radians(rot.pitch));
    front.z = sinf(lmath_radians(rot.yaw)) * cosf(lmath_radians(rot.pitch));

    camera->front = vec3_norm(front);
    camera->transform.rot = rot;
    camera->lastMousePos = vec2_make((float)mxpos, (float)mypos);
}

mat4 loglCameraGetView(loglCamera const *camera) {
    return mat4_look_at(camera->transform.pos, vec3_add(camera->transform.pos, camera->front), camera->up);
}

mat4 loglCameraGetProjection(loglCamera const *camera){
    return mat4_make_perspective(camera->fov, camera->aspect, camera->near, camera->far);
}
