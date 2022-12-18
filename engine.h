#ifndef ENGINE_H
#define ENGINE_H


#include <assert.h>
#include "window.h"
#include "graphics.h"
//#include "skybox.h"

static void cursorPositionCallBack(GLFWwindow*, double xpos, double ypos);

class Engine
{
  public:
    Engine(const char*  name, int width, int height);
    
    ~Engine();
    bool Initialize();
    void Run();
    void ProcessInput();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    void Display(GLFWwindow*, double);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow*, double xoffset, double yoffset);

  
  private:
    // Window related variables
    Window *m_window;    
    const char* m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;

    //mouse control
    double lastX;
    double lastY;
    bool firstMouse;
    float yaw;
    float pitch;

    Graphics *m_graphics;

    bool m_running;
    //skybox* galaxy;
};

#endif // ENGINE_H
