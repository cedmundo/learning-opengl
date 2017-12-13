#include <GLFW/glfw3.h>
#include <ike/timer.h>
#include <stdatomic.h>

static _Atomic(double) _ikeEllapsedTime = 0.0;
static _Atomic(double) _ikeDeltaTime = 0.0;
static _Atomic(double) _ikeCurrentFrameTime = 0.0;
static _Atomic(double) _ikeLastFrameTime = 0.0;

void ikeGlobalTimerUpdate() {
    atomic_store(&_ikeCurrentFrameTime, glfwGetTime());
    atomic_store(&_ikeDeltaTime, atomic_load(&_ikeCurrentFrameTime) - atomic_load(&_ikeLastFrameTime));
    atomic_store(&_ikeLastFrameTime, atomic_load(&_ikeCurrentFrameTime));
    atomic_store(&_ikeEllapsedTime, atomic_load(&_ikeEllapsedTime) + atomic_load(&_ikeDeltaTime));
}

double ikeDeltaTime() {
    return atomic_load(&_ikeDeltaTime);
}

double ikeEllapsedTime() {
    return atomic_load(&_ikeEllapsedTime);
}
