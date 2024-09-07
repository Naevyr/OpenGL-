#pragma once

#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <memory>


class Application {
    private: 

        unsigned int m_width = 800;
        unsigned int m_height = 600;        


        GLFWwindow * m_window;

        std::unique_ptr<Renderer> m_renderer;


        bool m_cameraControl = false;



        void processInput(double delta);
        void processMovement(double delta,  glm::vec3 * direction, glm::vec2 * rotation, bool * speeding);
    
    public:
        Application();
        ~Application();
        void Run();

};