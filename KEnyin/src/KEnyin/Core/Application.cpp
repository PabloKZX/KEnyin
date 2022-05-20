#include "pch.hpp"
#include "KEnyin/Core/Application.hpp"
#include "spdlog/spdlog.h"
#include <GLFW/glfw3.h>
namespace KEnyin
{
    Application::Application()
    {
        ServiceLocator::get().loadServices();

        GLFWwindow* window;

        /* Initialize the library */
        int success = glfwInit();
        KECheck_Engine(success, "Failed to initialize GLFW!");

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return;
    }

    Application::~Application()
    {
        ServiceLocator::get().clearServices();
    }

    void Application::run()
    {
        KELog("Esto es un trace");
        KESuccess_Engine("Esto es un log");
        KEWarn("Esto es un warn");
        KEError_Engine("Esto es un error");
        KECritical("Esto es un error critico");

        while (true);
    }
}