#ifndef IKE_DISPLAY_H
#define IKE_DISPLAY_H

#define IKE_DISPLAY_FAILURE 1
#define IKE_DISPLAY_OK 0

// We don'r really care about this right now.
typedef struct GLFWwindow GLFWwindow;

/**
 * \brief Game's display.
 *
 */
typedef struct _ikeDisplay {
    int height;
    int width;
    char* title;
    GLFWwindow* window;
} ikeDisplay;

int ikeDisplayConfig(ikeDisplay *);

void ikeDisplayTerminate(ikeDisplay *);

#endif /* IKE_DISPLAY_H */
