#include "window.h"

Window createWindow() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwSwapInterval(1);

  GLFWwindow* handle = glfwCreateWindow(WIDTH, HEIGHT, "Pong", NULL, NULL);
  glfwMakeContextCurrent(handle);

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
      printf("Failed to load GLAD\n");
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  Window window;
  window.handle = handle;
  glfwGetWindowSize(handle, &window.width, &window.height);

  return window;
}

void setWindowCallbacks(GLFWwindow* window, GLFWcursorposfun mousePosCallback, GLFWscrollfun scrollCallback, GLFWmousebuttonfun mouseButtonCallback, GLFWkeyfun keyboardCallback, GLFWframebuffersizefun framebufferSizeCallback) {
  glfwSetKeyCallback(window, keyboardCallback);
  glfwSetCursorPosCallback(window, mousePosCallback);
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  glfwSetScrollCallback(window, scrollCallback);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}
