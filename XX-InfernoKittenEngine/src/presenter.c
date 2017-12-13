#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ike/presenter.h>
#include <ike/spec.h>
#include <ike/asset.h>
#include <ike/vec4.h>
#include <ike/timer.h>
#include <stdio.h>

static ikePresenter presenter;
void ikeFramebufferSizeCallback(GLFWwindow* window, int width, int height);

int ikePresenterInit(const char *casset) {
    int status = IKE_PRESENTER_OK, code = 0;
    presenter.window = NULL;
    presenter.clearColor = vec4Make(0.f, 0.f, 0.f, 1.f);

    ikeSpec config;
    code = ikeSpecInit(&config);
    if (code == IKE_SPEC_OUT_OF_MEMORY) {
        status = IKE_PRESENTER_OUT_OF_MEMORY; goto finalize;
    } else if (code != IKE_SPEC_OK) {
        status = IKE_PRESENTER_BAD_CONFIG; goto finalize;
    }

    code = ikeAssetGetSpec(casset, &config);
    if (code == IKE_SPEC_OUT_OF_MEMORY) {
        status = IKE_PRESENTER_OUT_OF_MEMORY; goto finalize;
    } else if (code != IKE_SPEC_OK) {
        status = IKE_PRESENTER_BAD_CONFIG; goto finalize;
    }

    if(GL_FALSE == glfwInit()) {
        status = IKE_PRESENTER_API_ERROR; goto finalize;
    }

    code = ikeSpecGetInt(&config, "height", &presenter.height);
    if (code != IKE_SPEC_OK || presenter.height == 0) {
        status = IKE_PRESENTER_BAD_CONFIG; goto finalize;
    }

    code = ikeSpecGetInt(&config, "width", &presenter.width);
    if (code != IKE_SPEC_OK || presenter.width == 0) {
        status = IKE_PRESENTER_BAD_CONFIG; goto finalize;
    }

    code = ikeSpecGetString(&config, "title", &presenter.title);
    if (code != IKE_SPEC_OK || presenter.title == NULL) {
        status = IKE_PRESENTER_BAD_CONFIG; goto finalize;
    }

    int hresizable = 1,
        hvisible = 1,
        hdecorated = 1,
        hfocused = 1,
        hfloating = 0,
        hmaximized = 0;

    code = ikeSpecGetInt(&config, "resizable", &hresizable);
    if (code == IKE_SPEC_OK) {
        glfwWindowHint(GLFW_RESIZABLE, hresizable);
    }

    code = ikeSpecGetInt(&config, "visible", &hvisible);
    if (code == IKE_SPEC_OK) {
        glfwWindowHint(GLFW_VISIBLE, hvisible);
    }

    code = ikeSpecGetInt(&config, "decorated", &hdecorated);
    if (code == IKE_SPEC_OK) {
        glfwWindowHint(GLFW_DECORATED, hdecorated);
    }

    code = ikeSpecGetInt(&config, "focused", &hfocused);
    if (code == IKE_SPEC_OK) {
        glfwWindowHint(GLFW_FOCUSED, hfocused);
    }

    code = ikeSpecGetInt(&config, "floating", &hfloating);
    if (code == IKE_SPEC_OK) {
        glfwWindowHint(GLFW_FLOATING, hfloating);
    }

    code = ikeSpecGetInt(&config, "maximized", &hmaximized);
    if (code == IKE_SPEC_OK) {
        glfwWindowHint(GLFW_MAXIMIZED, hmaximized);
    }

    // TODO: OSX Fix to OpenGL context.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    presenter.window = glfwCreateWindow(presenter.width, presenter.height, presenter.title, NULL, NULL);
    if (presenter.window == NULL) {
        status = IKE_PRESENTER_API_ERROR; goto finalize;
    }

    // Configure some callbacks.
    glfwMakeContextCurrent(presenter.window);
    glfwSetFramebufferSizeCallback(presenter.window, ikeFramebufferSizeCallback);

    // Configure GL API and viewport
    if (GL_FALSE == gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        status = IKE_PRESENTER_GL_ERROR; goto finalize;
    }

    glViewport(0, 0, presenter.width, presenter.height);

finalize:
    ikeSpecDestroy(&config);
    return status;
}

ikePresenter *ikeGetPresenter() {
    return &presenter;
}

void ikePresenterDestroy() {
    if (presenter.window != NULL) {
        glfwDestroyWindow(presenter.window);
        presenter.window = NULL;
    }

    glfwTerminate();
}

void ikeFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    presenter.width = width;
    presenter.height = height;
    glViewport(0, 0, width, height);
}

int ikePresenterRunning() {
    return GL_FALSE == glfwWindowShouldClose(presenter.window) ? IKE_PRESENTER_RUNNING : IKE_PRESENTER_STOPPED;
}

void ikePresenterUpdate() {
    ikeGlobalTimerUpdate();
    // TODO: Input update
}

int ikePresenterShouldFrame() {
    return GL_FALSE;
}

void ikePresenterPrepareFrame() {
    vec4 cc = presenter.clearColor;
    glClearColor(cc.r, cc.g, cc.b, cc.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

int ikePresenterCommitFrame() {
    int status = IKE_PRESENTER_OK;
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL error code: %d\n", err);
        status = IKE_PRESENTER_GL_ERROR;
    }

    // Swap buffers and check events
    glfwSwapBuffers(presenter.window);
    glfwPollEvents();
    return status;
}

