#include "Window.h"

int Window::width;
int Window::height;

// Called on window resize
void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // Camera resize callback
    SceneManager::GetCurrentScene()->GetMainCamera()->OnResize(width, height);
    Window::width = width;
    Window::height = height;
}

// Called whenever a key is pressed or released
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Sets pressed boolean for pressed or released key
    InputManager::keys[key] = action;
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    InputManager::mouseX = xpos;
    InputManager::mouseY = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    InputManager::mouseButtons[button] = action;
}


Window::Window(int width, int height, const char* name) : name(name){
	window = glfwCreateWindow(width, height, name, NULL, NULL);
    Window::width = width;
    Window::height = height;
    // Check for window making error
    if (!window)
    {
        Log::LogError("Error initializing window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Specify OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


void Window::Init() {
    // Create openGL viewport size of window
    glViewport(0, 0, width, height);
    // Sets window resize callback
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    // Set keypress callback
    glfwSetKeyCallback(window, keyCallback);
    // Set mouse move callback
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    // On mouse button press
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

}