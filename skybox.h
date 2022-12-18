#ifndef SKYBOX_H
#define SKYBOX_H

#include "graphics_headers.h"
#include <iostream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL2/SOIL2.h>
#include <fstream>

#include "SkyboxShader.h"
#include "camera.h"

#define numVAO 1
#define numVBO 2

using namespace std;

class skybox
{
public:

    skybox();

    ~skybox();

    void setupVertices(void);
	GLuint loadcubemap(const char* mapDir);
    void init();
    void display(skyshader* sky, Camera* cam);


private:
    GLuint vao;
    GLuint vbo[2];

    GLuint skyboxTexture;

};

#endif