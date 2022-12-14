#include "object.h"
#include "Texture.h"
#include "graphics_headers.h"

class Sphere :
    public Object
{
public:
    Sphere();


    void Render(GLint positionAttribLoc, GLint colorAttribLoc);
    void Render(GLint positionAttribLoc, GLint colorAttribLoc, GLint tcAttribLoc, GLint hasTex);

    glm::mat4 GetModel() { return model; };
    glm::mat4 GetogModel() { return ogmodel; };
    void Update(glm::mat4 matModel);

    Sphere(int prec);
    Sphere(int prec, float angle, const char* fname, int tex, float matA[], float matD[], float matS[], float matsh);

    int getNumVertices();
    int getNumIndices();
    std::vector<int> getIndices();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getTexCoords();
    std::vector<glm::vec3> getNormals();

    GLuint getTextureID(int Tex); //{ return m_texture->getTextureID(); }
    void loadnormal(const char* fname);


    float matAmbient[4];
    float matDiff[4]; 
    float matSpec[4]; 
    float matShininess;



    bool hasTex;
    bool hasNorm;

private:
    glm::vec3 pivotLocation;
    glm::mat4 model;
    glm::mat4 ogmodel;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    Texture* m_texture;
    GLuint m_TextureID;
    GLuint m_NormalTextureID;

    GLuint vao;

    float angle;

    void setupVertices();
    void setupBuffers();
    void setupModelMatrix(glm::vec3 pivotLoc, float angle, float scale);

    int numVertices;
    int numIndices;
    std::vector<int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    void init(int);
    float toRadians(float degrees);

    std::vector<float> pvalues; // vertex positions
    std::vector<float> tvalues; // texture coordinates
    std::vector<float> nvalues; // normal vectors

 

};