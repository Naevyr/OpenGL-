#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>


#include "Application.h"
#include "UI/UI.h"


void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);





Application::Application()
{


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    

    m_window = glfwCreateWindow(m_width, m_height, "OpenGL+", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }


    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

   
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw;
    }   

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(debugCallback, 0);
    glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE );
    glfwSetInputMode(m_window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    
    glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    


    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 430");


   
    m_renderer.Init(m_width, m_height);

}


Application::~Application() {
    glfwTerminate();
}


void Application::Run() 
{

    MaterialDefinition defsTextured;
    defsTextured.albedoPath = "resources/textures/albedo.png";
    defsTextured.normalPath = "resources/textures/normal.png";
    defsTextured.lightingEnabled = true;

    auto cube = Mesh("resources/3D/cube.obj",m_renderer.LoadMaterial(defsTextured));
    

    
    
    Scene scene;
    Environment environment;
    environment.globalIllumination = glm::vec3(.1, .4, 1.0);
    environment.globalIlluminationIntensity = .2;
    environment.skyboxPath = "resources/textures/skybox";

    auto skybox = Mesh("resources/3D/cube.obj",m_renderer.LoadSkyboxMaterial("resources/textures/skybox"));
    skybox.setScale(glm::vec3(300,300,300));

    
    environment.skybox = skybox;


    scene.SetEnvironment(environment);
    
    scene.AddMesh(cube);

    
    MaterialDefinition defaultMaterial = MaterialDefinition();
    defaultMaterial.lightingEnabled = true;

    Mesh plane = Mesh("resources/3D/cube.obj",m_renderer.LoadMaterial(defaultMaterial));

    plane.setPosition(glm::vec3(0, -3, 0));
    plane.setScale(glm::vec3(10, 0.1, 10));
    scene.AddMesh(plane);
    
    scene.GetCamera().setPosition(glm::vec3(0, 0, -25));
    


    Light light;
    light.color = glm::vec3(1, 0, 1);
    light.position = glm::vec3(0, 10, 0);
    light.intensity = 1.0f;
    light.type = LightType::DIRECTIONAL;
    light.direction = glm::normalize(glm::vec3(0.000001, -1, 0));
    scene.AddLight(light);
    scene.AddLight(light);



    double previousTime = glfwGetTime();
    bool toggleSpeed = false;

    PostProcessingEffects effects;


    while (!glfwWindowShouldClose(m_window))
    {
        
   


        float currentTime = glfwGetTime();

        double delta =  currentTime - previousTime;

        processInput(delta);



        glm::vec3 direction = glm::vec3(0);
        glm::vec2 rotation = glm::vec2(0);
  
        processMovement(delta, &direction,&rotation,&toggleSpeed);
        

        scene.GetCamera().movementInput(direction, delta);
        scene.GetCamera().rotationInput(rotation, delta);
        scene.GetCamera().setSpeeding(toggleSpeed);


        m_renderer.Render(scene,effects);



     
        UI::Render(scene,effects);
      
        glfwSwapBuffers(m_window);
        glfwPollEvents();

    
        previousTime = currentTime;
    }
}




void Application::processInput(double deltaTime)
{

    int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT);
    
    if(state == GLFW_PRESS)
    {
        m_cameraControl = true;
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }else
    {
        m_cameraControl = false;
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

}

void Application::processMovement(double deltaTime, glm::vec3 * direction, glm::vec2 * rotation, bool * toggleSpeed) {

    if(!m_cameraControl)
        return;

    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos );
    
    *rotation = glm::vec2((xpos   - m_width / 2) * deltaTime * 100,  (ypos  - m_height/ 2 ) * deltaTime * 100);


    glfwSetCursorPos(m_window, m_width / 2, m_height / 2);

    if(glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        *direction += glm::vec3(0, 0, 1);
    
    if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        *direction += glm::vec3(0, 0, -1);

    if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        *direction += glm::vec3(1, 0, 0);


    if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        *direction += glm::vec3(-1, 0, 0);    

    if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        *direction += glm::vec3(-1, 0, 0);    

    if(glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        *toggleSpeed = true;
    else
        *toggleSpeed = false;
}      



// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
    std::cout << message << std::endl;

}