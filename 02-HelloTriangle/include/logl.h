#ifndef LOGL_H
#define LOGL_H
// LOGL stands for "Learning OpenGL", it's basically a set of
// definitions, functions and structures that I might use on future
// tutorial parts.

#define LOGL_WINDOW_HEIGHT 600
#define LOGL_WINDOW_WIDTH 800

#define LOGL_DEFAULT_VSHADER "#version 330 core\nlayout(location = 0) in vec3 aPos;\nvoid main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }"
#define LOGL_DEFAULT_FSHADER "#version 330 core\nout vec4 FragColor;\nvoid main(){ FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }"

// General input processing, such escape and wireframe on/off
void loglProcessInput(GLFWwindow *);

// Implements frambuffer_size_callback from glfw
void loglResizeCb(GLFWwindow *, GLint, GLint);

// Compiles a shader (vertex or fragment specified on type) stored in a standard string (source).
// Returns false if any errors occur (also reports the result by stdout).
GLboolean loglCompileShaderStr(GLuint* id, GLint type, const GLchar* source);

// Create a new shader program linking a given vertex and fragment shader.
// Returns false if any errors occur (also reports the result by stdout).
GLboolean loglGetShaderProgram(GLuint *outProgramId, GLuint vShader, GLuint fShader);

// Gets or sets the global drawing mode for project (not thread safe).
GLuint loglDrawingMode(GLuint value, GLboolean setval);
#endif
