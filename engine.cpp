

#include "engine.h"
#include "glm/ext.hpp"

float FOV = 40;

Engine::Engine(const char* name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;

}


Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT);
  if(!m_window->Initialize())
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  //for moouse control
  firstMouse = true;
  yaw = 260.0f;
  pitch = -31.0f;

  glfwSetCursorPosCallback(m_window->getWindow(), cursorPositionCallBack);


  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while (!glfwWindowShouldClose(m_window->getWindow()))
  {
      ProcessInput();
      Display(m_window->getWindow(), glfwGetTime());
      glfwPollEvents();
  }
  m_running = false;

}

void Engine::ProcessInput()
{
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->getWindow(), true);

    glfwSetScrollCallback(m_window->getWindow(), scroll_callback);
    m_graphics->getCamera()->fov = FOV;
    m_graphics->getCamera()->Update();


    // Update camera animation here.
        //mouse control
    glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        m_graphics->getCamera()->cameraPos += cameraSpeed * m_graphics->getCamera()->cameraFront;
        //m_graphics->getCamera()->cameraPos -= glm::normalize(glm::cross(m_graphics->getCamera()->cameraFront, glm::vec3(-1.0, 0.0, 0.0))) * cameraSpeed;
        m_graphics->getCamera()->Update();
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        m_graphics->getCamera()->cameraPos -= cameraSpeed * m_graphics->getCamera()->cameraFront;
        //m_graphics->getCamera()->cameraPos += glm::normalize(glm::cross(m_graphics->getCamera()->cameraFront, glm::vec3(-1.0, 0.0, 0.0))) * cameraSpeed;
        m_graphics->getCamera()->Update();
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        m_graphics->getCamera()->cameraPos -= glm::normalize(glm::cross(m_graphics->getCamera()->cameraFront, m_graphics->getCamera()->cameraUp)) * cameraSpeed;
        m_graphics->getCamera()->Update();
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        m_graphics->getCamera()->cameraPos += glm::normalize(glm::cross(m_graphics->getCamera()->cameraFront, m_graphics->getCamera()->cameraUp)) * cameraSpeed;
        m_graphics->getCamera()->Update();
    }

    //get mouse position
    double xpos, ypos;

    glfwGetCursorPos(m_window->getWindow(), &xpos, &ypos);
    //mouse calculations
    if (firstMouse)
    {
        float lastX = xpos;
        float lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;
    //see where current mouse position is
    //std::cout << yaw << std::endl;
    //std::cout << pitch << std::endl;

    //limits on yaw and pitch so that we can find the objects
    //if (pitch > -11.0f)
        //pitch = -11.0f;
    //if (pitch < -52.0f)
       // pitch = -52.0f;
    //if (yaw > 301.0f)
        //yaw = 301.0f;
    //if (yaw < 238.0f)
        //yaw = 238.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_graphics->getCamera()->cameraFront = glm::normalize(direction);
    m_graphics->getCamera()->Update();

    //using the mouse scoll wheel to zoom in and out

}


void Engine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    FOV = FOV - (float)yoffset;
    //sets limits for FOV
    if (FOV < 1.0f)
        FOV = 1.0f;
    if (FOV > 45.0f)
        FOV = 45.0f;
}






void Engine::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
 
    std::cout << "Position: (" << xpos << ":" << ypos << ")";
}

unsigned int Engine::getDT()
{
  //long long TimeNowMillis = GetCurrentTimeMillis();
  //assert(TimeNowMillis >= m_currentTimeMillis);
  //unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  //m_currentTimeMillis = TimeNowMillis;
  //return DeltaTimeMillis;
    return glfwGetTime();
}

long long Engine::GetCurrentTimeMillis()
{
  //timeval t;
  //gettimeofday(&t, NULL);
  //long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  //return ret;
    return (long long) glfwGetTime();
}

void Engine::Display(GLFWwindow* window, double time) {

    m_graphics->Render();
    m_window->Swap();
    m_graphics->HierarchicalUpdate2(time);
}

static void cursorPositionCallBack(GLFWwindow* window, double xpos, double ypos) {
    //cout << xpos << " " << ypos << endl;
}
