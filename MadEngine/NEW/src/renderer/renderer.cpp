#include "renderer.h"

void redraw(GLFWwindow *window){
    Update();
    glfwSwapBuffers(window);
    glfwPollEvents();
}