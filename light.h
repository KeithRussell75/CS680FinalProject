#include "Texture.h"
#include "graphics_headers.h"
#include <iostream>


class Light
{
public:
    Light(glm::mat4 viewMatrix, glm::vec3 currentLightPos, glm::vec4 lightAmb);
    Light(glm::mat4 viewMatrix, glm::vec3 currentLightPos); // glm::vec4 lightAmb, glm::vec4 lightDiff, glm::vec4 lightSpec, glm::vec4 gAmb);
    float m_globalAmbient[4];
    float m_lightAmbient[4];
    float m_lightDiffuse[4];
    glm::vec3 m_lightPosition;
    float m_lightPositionViewSpace[3];
    float m_lightSpecular[4];

private:
    glm::vec3 transformed;
};
