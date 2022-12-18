#include "skybox.h"

skybox::skybox(){
    setupVertices();
    skyboxTexture = loadcubemap("C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/Cubemaps");
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

void skybox::setupVertices() {
    float cubeVertexPositions[108] =
    { -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, -1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
        1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f, 1.0f,  1.0f, -1.0f,
        1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, 1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f, 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(numVBO, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexPositions) * 4, cubeVertexPositions, GL_STATIC_DRAW);

}

GLuint skybox::loadcubemap(const char* mapDir){
    GLuint textureRef;
    string xp = mapDir; xp = xp + "/px.jpg";
    string xn = mapDir; xn = xn + "/nx.jpg";
    string yp = mapDir; yp = yp + "/py.jpg";
    string yn = mapDir; yn = yn + "/ny.jpg";
    string zp = mapDir; zp = zp + "/pz.jpg";
    string zn = mapDir; zn = zn + "/nz.jpg";
    textureRef = SOIL_load_OGL_cubemap(xp.c_str(), xn.c_str(), yp.c_str(), yn.c_str(), zp.c_str(), zn.c_str(),
        SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (textureRef == 0) cout << "didnt find cube map image file" << endl;
    	glBindTexture(GL_TEXTURE_CUBE_MAP, textureRef);
    // reduce seams
    	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return textureRef;
}


void skybox::display(skyshader* sky, Camera* cam) {
    
    //glDisable(GL_DEPTH_TEST);
    //glDepthMask(false);
    glDepthFunc(GL_EQUAL);

    glUseProgram(sky->GetShaderProgram());
    GLuint vLoc = glGetUniformLocation(sky->GetShaderProgram(), "v_matrix");
    GLuint projLoc = glGetUniformLocation(sky->GetShaderProgram(), "p_matrix");
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(cam->GetView()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(cam->GetProjection()));

    //glUseProgram(renderingProgram);
    glBindVertexArray(vao);

    //glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);	// cube is CW, but we are viewing the inside
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glDepthMask(true);
}