#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
    //--Init the view and projection matrices
    //  if you will be having a moving camera the view matrix will need to more dynamic
    //  ...Like you should update it before you render more dynamic 
    //  for this project having them static will be fine
    //view = glm::lookAt( glm::vec3(x, y, z), //Eye Position
                        //glm::vec3(0.0, 0.0, 0.0), //Focus point
                        //glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up
  
    cameraPos = glm::vec3(0.0f, 10.0f, 16.0f);
    cameraFront = glm::vec3(0.0f, -.625f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0);
    width = w;
    height = h;
    view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);

    projection = glm::perspective( glm::radians(40.f), //the FoV typically 90 degrees is good which is what this is set to
                                    width/height, //Aspect Ratio, so Circles stay Circular
                                    0.01f, //Distance to the near plane, normally a small value like this
                                    100.0f); //Distance to the far plane, 
    return true;
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}

glm::mat4 Camera::Update() {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(glm::radians(fov), // FoV 
        width / height, //Aspect Ratio, so Circles stay Circular
        0.01f, //Distance to the near plane, normally a small value like this
        100.0f); //Distance to the far plane, 
    return view;
}