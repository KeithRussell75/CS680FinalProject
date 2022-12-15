#include "Texture.h"
#include "graphics_headers.h"

class Light
{
public:
    Light(GLint viewMatrix);

private:
    glm::vec4 m_globalAmbient;
    GLint m_lightAmbient;
    GLint m_lightDiffuse;
    GLint m_lightPosition;
    std::vector<glm::vec4> m_lightPositionViewSpace;
    GLint m_lightSpecular;



};
