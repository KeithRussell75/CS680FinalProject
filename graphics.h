#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <stack>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "sphere.h"
#include "mesh.h"
#include "light.h"
#include "skybox.h"
#include "SkyboxShader.h"

#define numVBOs 2;
#define numIBs 2;


class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void HierarchicalUpdate2(double dt);
    void RenderPlanet(Sphere* planet);
    void Render();
    void AddUpdateMoonPlanet(Sphere* ufo,bool planet, std::vector<float> Speed, std::vector<float> Dist, glm::vec3 RotVector, std::vector<float> RotSpeed, std::vector<float> Scale, double dt);

    Camera* getCamera() { return m_camera; }

  private:
    std::string ErrorString(GLenum error);

    bool collectShPrLocs();
    void ComputeTransforms (double dt, std::vector<float> speed, std::vector<float> dist,
        std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, 
        glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat);

    stack<glm::mat4> modelStack;

    Camera *m_camera;
    Shader *m_shader;
    skyshader *m_skyshader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
    GLint m_normalMatrix;
    GLint m_positionAttrib;
    GLint m_normalAttrib;
    GLint m_tcAttrib;
    GLint m_hasTexture;


    Sphere* Sun;
    Sphere* Mercury;
    Sphere* Venus;
    Sphere* Earth;
    Sphere* Moon;
    Sphere* Mars;
    Sphere* Jupiter;
    Sphere* IO;
    Sphere* Europa;
    Sphere* Ganymede;
    Sphere* Callisto;
    Sphere* Saturn;
    Sphere* Mimas;
    Sphere* Enceladus;
    Sphere* Titan;
    Sphere* Uranus;
    Sphere* Neptune;
    Sphere* Ceres;
    Sphere* Eris;
    Sphere* Haumea;

    skybox* galaxy;

    Light* m_light;

    Mesh* m_mesh;
    glm::mat4 ogMesh;


};

#endif /* GRAPHICS_H */
