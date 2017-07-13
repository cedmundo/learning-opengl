#ifndef LOGL_H
#define LOGL_H
// LOGL stands for "Learning OpenGL", it's basically a set of
// definitions, functions and structures that I might use on future
// tutorial parts.

#define LOGL_WINDOW_HEIGHT 600
#define LOGL_WINDOW_WIDTH 800

// Dumps into memory indicated file. Returns GL_TRUE if success, GL_FALSE otherwise.
GLboolean loglLoadText(const GLchar *filename, GLchar **data);

// Unloads file from memory (frees pointer)
void loglUnloadText(GLchar *data);

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

// Loads a PNG-encoded file into a linear RGBA array.
GLboolean loglLoadPNG(const GLchar *filename, GLchar **data, GLuint* width, GLuint* height);

// Unloads data from memory.
void loglUnloadPNG(GLchar *data);

#endif
