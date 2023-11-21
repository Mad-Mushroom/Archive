#include "main.h"

ConsoleClass Console;

GLFWwindow* window;

bool CreateWindow(int SizeX, int SizeY, const char* title){
    window = glfwCreateWindow(SizeX, SizeY, title, NULL, NULL);
    if(window == NULL){
        cout << "Failed to create GLFW window!" << endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, SizeX, SizeY);
    return true;
}

int main(int argc, char* argv[]){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // Mac

    Init();

    while (!glfwWindowShouldClose(window)){
        redraw(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}