#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include <vector>

#include "graphics_headers.h"

class skyshader
{
  public:
    skyshader();
    ~skyshader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);
    GLint GetAttribLocation(const char* pAttribName);
    GLuint GetShaderProgram() { return m_shaderProg; };


  private:
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;
};

#endif  /* SHADER_H */
