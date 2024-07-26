#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/include/glad/gl.h>
#include <glfw/include/GLFW/glfw3.h>

#define WIDTH  800
#define HEIGHT 600

struct Window {
  GLFWwindow* handle;
  ushort width, height;
};

GLFWwindow* createWindow();
void setWindowCallbacks(GLFWwindow* window, GLFWcursorposfun mousePosCallback, GLFWscrollfun scrollCallback, GLFWmousebuttonfun mouseButtonCallback, GLFWkeyfun keyboardCallback, GLFWframebuffersizefun framebufferSizeCallback);

#endif /* WINDOW_H */
