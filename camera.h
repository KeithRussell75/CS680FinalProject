#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    glm::mat4 Update();

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float fov;

  
  private:

    double x = 0.0;
    double y = 10.0;
    double z = -16.0;
    glm::mat4 projection;
    glm::mat4 view;

    float width;
    float height;
};

#endif /* CAMERA_H */
