#ifndef IKE_PRESENTER_H
#define IKE_PRESENTER_H
#include <ike/vec4.h>

#define IKE_PRESENTER_STOPPED (0)
#define IKE_PRESENTER_RUNNING (1)

#define IKE_PRESENTER_OK (0)
#define IKE_PRESENTER_BAD_CONFIG (1)
#define IKE_PRESENTER_OUT_OF_MEMORY (2)
#define IKE_PRESENTER_API_ERROR (3)
#define IKE_PRESENTER_GL_ERROR (4)

// We do not care of this at all right now.
typedef struct GLFWwindow GLFWwindow;

/**
 * \brief Presenter handles window events and rendering buffers.
 *
 * Main piece of a game, presenter will render scenes, show them on
 * windows and handle input.
 */
typedef struct _ikePresenter {
    vec4 clearColor;
    int height;
    int width;
    const char *title;
    GLFWwindow *window;
} ikePresenter;

/**
 * \brief Initializes a presenter.
 *
 * \param casset name of the spec asset of configuration.
 * \return IKE_PRESENTER_OK or IKE_PRESENTER_BAD_CONFIG in case of bad configuration.
 */
int ikePresenterInit(const char *casset);

/**
 * \brief Properly destroy a presenter.
 *
 * Releases internal memory and pools and calls destructor for window.
 */
void ikePresenterDestroy();

/**
 * \brief Returns the global presenter.
 */
ikePresenter *ikeGetPresenter();

/**
 * \brief Returns either presenter is running or not.
 * \return (1) if presenter is running, (0) if don't.
 */
int ikePresenterRunning();

/**
 * \brief Updates timer and input handling.
 */
void ikePresenterUpdate();

/**
 * \brief Returns (1/true) if presenter is ready to do a frame.
 */
int ikePresenterShouldFrame();

/**
 * \brief Setups a pre-rendering state on presenter.
 */
void ikePresenterPrepareFrame();

/**
 * \brief Swaps buffers of presenter and polls events.
 * \return IKE_PRESENTER_OK, IKE_PRESENTER_API_ERROR or IKE_PRESENTER_GL_ERROR
 */
int ikePresenterCommitFrame();

#endif /* IKE_PRESENTER_H */
