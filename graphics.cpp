#include "graphics.h"

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
	// Used for the linux OS
#if !defined(__APPLE__) && !defined(MACOSX)
  // cout << glewGetString(GLEW_VERSION) << endl;
	glewExperimental = GL_TRUE;

	auto status = glewInit();

	// This is here to grab the error that comes from glew init.
	// This error is an GL_INVALID_ENUM that has no effects on the performance
	glGetError();

	//Check for error
	if (status != GLEW_OK)
	{
		std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
		return false;
	}
#endif

	// Init Camera
	m_camera = new Camera();
	if (!m_camera->Initialize(width, height))
	{
		printf("Camera Failed to Initialize\n");
		return false;
	}

	// Set up the shaders
	m_shader = new Shader();
	if (!m_shader->Initialize())
	{
		printf("Shader Failed to Initialize\n");
		return false;
	}

	// Add the vertex shader
	if (!m_shader->AddShader(GL_VERTEX_SHADER))
	{
		printf("Vertex Shader failed to Initialize\n");
		return false;
	}

	// Add the fragment shader
	if (!m_shader->AddShader(GL_FRAGMENT_SHADER))
	{
		printf("Fragment Shader failed to Initialize\n");
		return false;
	}
	
	// Connect the program
	if (!m_shader->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}
	
	// Populate location bindings of the shader uniform/attribs
	if (!collectShPrLocs()) {
		printf("Some shader attribs not located!\n");
	}


	// Set up the skyshaders
	m_skyshader = new skyshader();
	if (!m_skyshader->Initialize())
	{
		printf("skyshader Failed to Initialize\n");
		return false;
	}
	
	// Add the vertex skyshader
	if (!m_skyshader->AddShader(GL_VERTEX_SHADER))
	{
		printf("Vertex skyshader failed to Initialize\n");
		return false;
	}
	
	// Add the fragment skyshader
	if (!m_skyshader->AddShader(GL_FRAGMENT_SHADER))
	{
		printf("Fragment skyshader failed to Initialize\n");
		return false;
	}
	
	// Connect the program
	if (!m_skyshader->Finalize())
	{
		printf("Program to Finalize\n");
		return false;
	}
	
	// Populate location bindings of the skyshader uniform/attribs
	if (!collectShPrLocs()) {
		printf("Some skyshader attribs not located!\n");
	}
	
	// Starship
	m_mesh = new Mesh(glm::vec3(0.0f, 0.0f, 0.0f), "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/assets/SpaceShip-1.obj", "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/assets/SpaceShip-1.png");
	ogMesh = m_mesh->GetModel();

	float matAmbient[4] = { 15., 15.0, 15.0, 15.0 };
	float matDiff[4] = { 2.0, 2., 2., 1.0 };
	float matSpec[4] = { 3.0, 3.0, 3.0, 1.0 };
	float matShininess = 20.0;

	// The Sun
	Sun = new Sphere(85, 0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/2k_sun.jpg",DIFFUSE_TEXTURE, matAmbient, matDiff, matSpec, matShininess);
	
	float matAmbient2[4] = { 5., 5.0, 5.0, 5.0 };
	float matDiff2[4] = { 2.0, 2., 2., 1.0 };
	float matSpec2[4] = { 10.0, 10.0, 10.0, 1.0 };
	float matShininess2 = 20.0;
	//Mercury
	Mercury = new Sphere(68, 0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Mercury.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	
	//Venus
	Venus = new Sphere(45,0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Venus.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);

	// The Earth
	Earth = new Sphere(45,-23.5, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/2k_earth_daymap.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	// The moon
	Moon = new Sphere(45, 0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/2k_moon.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);

	// Mars
	Mars = new Sphere(45,25, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Mars.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	
	//Jupiter
	Jupiter = new Sphere(45,3.13, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Jupiter.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	IO = new Sphere(45, 0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/IO.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	Europa = new Sphere(45, 0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Europa.png", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	Ganymede = new Sphere(45, 0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Ganymede.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	Callisto = new Sphere(45, 0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Callisto.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	
	//Saturn
	Saturn = new Sphere(45,26.73, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Saturn.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	//auto error3 = glGetError();
	//Mimas = new Sphere(45, 26.73, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Mimas.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	//auto error4 = glGetError();
	Enceladus = new Sphere(45, 0.0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Enceladus.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	//auto error5 = glGetError();
	//Uranus
	Uranus = new Sphere(45,98, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Uranus.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);

	//Neptune
	Neptune = new Sphere(45,28, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Neptune.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	
	Haumea = new Sphere(45,0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Haumea.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	Ceres = new Sphere(45,0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Ceres.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	Eris = new Sphere(45,0, "C:\\Users/Russell Keith/source/repos/FinalProject/CS680FinalProject/PlanetaryTextures/Eris.jpg", DIFFUSE_TEXTURE, matAmbient2, matDiff2, matSpec2, matShininess2);
	
	galaxy = new skybox();

	//enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return true;
}

void Graphics::AddUpdateMoonPlanet(Sphere* ufo, bool planet, std::vector<float> Speed, std::vector<float> Dist, glm::vec3 RotVector, std::vector<float> RotSpeed, std::vector<float> Scale, double dt) {
	
	glm::mat4 localTransform;

	localTransform = modelStack.top();				// start with planet corrdinates
	localTransform *= glm::translate(glm::mat4(1.f),glm::vec3(cos(Speed[0] * dt) * Dist[0], sin(Speed[1] * dt) * Dist[1], sin(Speed[2] * dt) * Dist[2]));
	modelStack.push(localTransform);			// store moon coordinate
	localTransform *= glm::rotate(ufo->GetogModel(), RotSpeed[0] * (float)dt, RotVector);
	localTransform *= glm::scale(glm::vec3(Scale[0], Scale[1], Scale[2]));
	if (ufo != NULL)
		ufo->Update(localTransform);
	if (!planet) {
		modelStack.pop(); //back to planet coordinates
	}
}


void Graphics::HierarchicalUpdate2(double dt) {

	//m_camera->Update();
	std::vector<float> speed, dist, rotSpeed, scale;
	glm::vec3 rotVector;
	glm::mat4 localTransform;

	// position of the sun	
	modelStack.push(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)));  // sun's coordinate
	localTransform = modelStack.top();		// The sun origin
	localTransform *= glm::rotate(glm::mat4(1.0f), (float)dt, glm::vec3(0.f, 1.f, 0.f));
	localTransform *= glm::scale(glm::vec3(2, 2, 2));
	if (Sun != NULL) {
		Sun->Update(localTransform);
	}

	// position of the mesh
	speed = { 0.0, 2.0, 2.0 };
	dist = { 0.0, 2.0, 2.0 };
	rotVector = { 0.0, 0.0, 1.0 };
	rotSpeed = { .75, .75, .75 };
	scale = { .01, .01, .01 };
	localTransform = modelStack.top();				// start with sun's coordinate
	localTransform *= glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt - (180 / 3.14)) * dist[1], sin(speed[2] * dt + (180 / 3.14)) * dist[2])); // y and z movement opposite phase
	modelStack.push(localTransform);			// store planet-sun coordinate
	localTransform *= glm::rotate(ogMesh, rotSpeed[0] * (float)dt, rotVector);
	localTransform *= glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
	if (m_mesh != NULL) {
		m_mesh->Update(localTransform);
		modelStack.pop();						//pop mesh's corrdinates
	}

	// position of Mercury
	speed = { -.75, -75, -.75 };
	dist = { 3.0, 0.0, 3.0 };
	rotVector = { 0.0, 1.0, 0.0 };
	rotSpeed = { -1., 0.075, -1. };
	scale = { .27, .27, .27 };
	this->AddUpdateMoonPlanet(Mercury, true, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();//back to suns coordinates


	// position of Venus
	speed = { -0.5, -0.5, -0.5 };
	dist = { 7.0, 0.0, 7.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -.5, 1.0 };
	scale = { .5f, .5f, .5f };
	this->AddUpdateMoonPlanet(Venus, true, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();//back to suns coordinates


	// position of Earth
	speed = { -.4, -.4, -.4 };
	dist = { 10.0, 0.0, 10.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -2.0, 1.0 };
	scale = { .5f, .5f, .5f };
	this->AddUpdateMoonPlanet(Earth, true, speed, dist, rotVector, rotSpeed, scale, dt);
	//modelStack.pop(); //back to suns coordinates
	
	// position of moon
	speed = { -1., -1., -1. };
	dist = { 1.5, 0.0, 1.5 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -.4, 1.0 };
	scale = { .125f, .125f, .125f };
	this->AddUpdateMoonPlanet(Moon, false, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();


	// position of Mars
	speed = { -.3, -.3, -.3 };
	dist = { 14.0, 0.0, 14.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -2.0, 1.0 };
	scale = { .45f, .45f, .45f };
	this->AddUpdateMoonPlanet(Mars, true, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();//back to suns coordinates


	// position of Jupiter
	speed = { -.2, -.2, -.2 };
	dist = { 25.0, 0.0, 25.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, .8, 1.0 };
	scale = { .8f, .8f, .8f };
	this->AddUpdateMoonPlanet(Jupiter, true, speed, dist, rotVector, rotSpeed, scale, dt);
	//modelStack.pop();//back to suns coordinates
	
	//position of IO
	speed = { -2., -2., -2. };
	dist = { 1.5, 0.25, 1.5 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -.4, 1.0 };
	scale = { .125f, .125f, .125f };
	this->AddUpdateMoonPlanet(IO, false, speed, dist, rotVector, rotSpeed, scale, dt);

	//Europa
	speed = { -1., -1., -1. };
	dist = { 2.5, -.5, 2.5 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -.4, 1.0 };
	scale = { .125f, .125f, .125f };
	this->AddUpdateMoonPlanet(Europa, false, speed, dist, rotVector, rotSpeed, scale, dt);

	//Ganymede;
	speed = { -.75, -.75, -.75 };
	dist = { 3.5, 0, 3.5 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -.4, 1.0 };
	scale = { .125f, .125f, .125f };
	this->AddUpdateMoonPlanet(Ganymede, false, speed, dist, rotVector, rotSpeed, scale, dt);

	//Callisto
	speed = { -.5, -.5, -.5 };
	dist = { 4.75, 2, 4.75 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -.4, 1.0 };
	scale = { .125f, .125f, .125f };
	this->AddUpdateMoonPlanet(Callisto, false, speed, dist, rotVector, rotSpeed, scale, dt);

	modelStack.pop();//back to suns coordinates


	// position of Saturn
	speed = { -.15, -.15, -.15 };
	dist = { 32.0, 0.0, 32.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, 0.9, 1.0 };
	scale = { .75f, .75f, .75f };
	this->AddUpdateMoonPlanet(Saturn, true, speed, dist, rotVector, rotSpeed, scale, dt);
	//modelStack.pop();//back to suns coordinates

	//Mimas
	//speed = { -1.5, -1.5, -1.5 };
	//dist = { 2.5, 2.5, 2.5 };
	//rotVector = { 0., -1., 0.0 };
	//rotSpeed = { -1.0, -.4, 1.0 };
	//scale = { .125f, .125f, .125f };
	//this->AddUpdateMoonPlanet(Mimas, false, speed, dist, rotVector, rotSpeed, scale, dt);

	//Enceladus
	speed = { -.5, -.5, -.5 };
	dist = { 3.75, 3.75, 3.75 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, -.4, 1.0 };
	scale = { .125f, .125f, .125f };
	this->AddUpdateMoonPlanet(Enceladus, false, speed, dist, rotVector, rotSpeed, scale, dt);

	modelStack.pop();//back to suns coordinates

	// position of Uranus
	speed = { -.12, -.12, -.12 };
	dist = { 38.0, 0.0, 38.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, 1.5, 1.0 };
	scale = { .75f, .75f, .75f };
	this->AddUpdateMoonPlanet(Uranus, true, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();//back to suns coordinates

	// position of Neptune
	speed = { -.1, -.1, -.1 };
	dist = { 45.0, 0.0, 45.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, 1.0, 1.0 };
	scale = { .75f, .75f, .75f };
	this->AddUpdateMoonPlanet(Neptune, true, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();//back to suns coordinates

	//Haumea
	speed = { -.2, -.05, -.2 };
	dist = { 50.0, 20.0, 50.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, 1.0, 1.0 };
	scale = { .5f, .5f, .5f };
	this->AddUpdateMoonPlanet(Haumea, true, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();//back to suns coordinates

	//Ceres
	speed = { -.1, -.05, -.1 };
	dist = { 55.0, 35.0, 55.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, 1.0, 1.0 };
	scale = { .5f, .5f, .5f };
	this->AddUpdateMoonPlanet(Ceres, true, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();//back to suns coordinates
	
	//Eris
	speed = { -.2, -.1, -.2 };
	dist = { 60.0, -15.0, 45.0 };
	rotVector = { 0., -1., 0.0 };
	rotSpeed = { -1.0, 1.0, 1.0 };
	scale = { 1.f, 1.f, 1.f };
	this->AddUpdateMoonPlanet(Eris, true, speed, dist, rotVector, rotSpeed, scale, dt);
	modelStack.pop();


	modelStack.pop();	// empy stack
	

}


void Graphics::ComputeTransforms(double dt, std::vector<float> speed, std::vector<float> dist, 
	std::vector<float> rotSpeed, glm::vec3 rotVector, std::vector<float> scale, glm::mat4& tmat, glm::mat4& rmat, glm::mat4& smat) {
	tmat = glm::translate(glm::mat4(1.f),
		glm::vec3(cos(speed[0] * dt) * dist[0], sin(speed[1] * dt) * dist[1], sin(speed[2] * dt) * dist[2])
	);
	rmat = glm::rotate(glm::mat4(1.f), rotSpeed[0] * (float)dt, rotVector);
	smat = glm::scale(glm::vec3(scale[0], scale[1], scale[2]));
}

void Graphics::RenderPlanet(Sphere* planet) {
	float matambient[4];
	float matdiff[4];
	float matspec[4];

	for (int i = 0; i < 4; i++) {
		matambient[i] = planet->matAmbient[i];
		matdiff[i] = planet->matDiff[i];
		matspec[i] = planet->matSpec[i];
	}

	// material ambient
	GLuint mAmbLoc = glGetUniformLocation(m_shader->GetShaderProgram(), "material.ambient");
	glProgramUniform4fv(m_shader->GetShaderProgram(), mAmbLoc, 1, matambient);

	//material diffuse
	GLuint mDiffLoc = glGetUniformLocation(m_shader->GetShaderProgram(), "material.diffuse");
	glProgramUniform4fv(m_shader->GetShaderProgram(), mDiffLoc, 1, matdiff);

	//material specular
	GLuint mSpecLoc = glGetUniformLocation(m_shader->GetShaderProgram(), "material.spec");
	glProgramUniform4fv(m_shader->GetShaderProgram(), mSpecLoc, 1, matspec);

	//material Shininess
	GLuint mShineLoc = glGetUniformLocation(m_shader->GetShaderProgram(), "material.shininess");
	glProgramUniform1f(m_shader->GetShaderProgram(), mShineLoc, planet->matShininess);


	if (planet != NULL) {
		GLuint hasN = m_shader->GetUniformLocation("hasNormalMap");
		//glUniform1i(m_hasTexture, false);

		//create the invtranspose matrix for normal in shader
		glUniformMatrix3fv(m_normalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(glm::mat3(m_camera->GetView() * planet->GetModel())))));
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(planet->GetModel()));

		if (planet->hasTex) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, planet->getTextureID(DIFFUSE_TEXTURE));
			GLuint sampler = m_shader->GetUniformLocation("samp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUseProgram(m_shader->GetShaderProgram());
			glUniform1i(sampler, 0);
			glUniform1i(hasN, false);
			planet->Render(m_positionAttrib, m_normalAttrib, m_tcAttrib, m_hasTexture);
		}
	}
}


void Graphics::Render()
{
	
	//clear the screen
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Start the correct program
	m_skyshader->Enable();
	m_shader->Enable();
	

	// Send in the projection and view to the shader (stay the same while camera intrinsic(perspective) and extrinsic (view) parameters are the same
	glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
	glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

	galaxy->display(m_skyshader,m_camera);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glUseProgram(m_shader->GetShaderProgram());
	if (m_mesh != NULL) {
		glUniform1i(m_hasTexture, false);
		glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mesh->GetModel()));
		if (m_mesh->hasTex) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_mesh->getTextureID());
			GLuint sampler = m_shader->GetUniformLocation("samp");
			if (sampler == INVALID_UNIFORM_LOCATION)
			{
				printf("Sampler Not found not found\n");
			}
			glUniform1i(sampler, 0);
			m_mesh->Render(m_positionAttrib, m_normalAttrib, m_tcAttrib, m_hasTexture);
		}
	}

	RenderPlanet(Sun);
	RenderPlanet(Mercury);
	RenderPlanet(Venus);
	RenderPlanet(Earth);
	RenderPlanet(Moon);
	RenderPlanet(Mars);
	RenderPlanet(Jupiter);
	RenderPlanet(IO);
	RenderPlanet(Europa);
	RenderPlanet(Ganymede);
	RenderPlanet(Callisto);
	RenderPlanet(Saturn);
	//RenderPlanet(Mimas);
	RenderPlanet(Enceladus);
	RenderPlanet(Uranus);
	RenderPlanet(Neptune);
	RenderPlanet(Haumea);
	RenderPlanet(Ceres);
	RenderPlanet(Eris);

	// Get any errors from OpenGL
	auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		string val = ErrorString(error);
		std::cout << "Error initializing OpenGL! " << error << ", " << val << std::endl;
	}
}


bool Graphics::collectShPrLocs() {
	bool anyProblem = true;
	// Locate the projection matrix in the shader
	m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
	if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_projectionMatrix not found\n");
		anyProblem = false;
	}
	
	// Locate the view matrix in the shader
	m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
	if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_viewMatrix not found\n");
		anyProblem = false;
	}

	// Locate the model matrix in the shader
	m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
	if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_modelMatrix not found\n");
		anyProblem = false;
	}
	
	// Locate the normal matrix in the shader
	m_normalMatrix = m_shader->GetUniformLocation("normMatrix");
	if (m_normalMatrix == INVALID_UNIFORM_LOCATION)
	{
		printf("m_normalMatrix not found\n");
		anyProblem = false;
	}
	
	// Locate the normal vertex attribute
	m_normalAttrib = m_shader->GetAttribLocation("v_normal");
	if (m_normalAttrib == -1)
	{
		printf("v_normal attribute not found\n");
		anyProblem = false;
	}
	
	// Locate the position vertex attribute
	m_positionAttrib = m_shader->GetAttribLocation("v_position");
	if (m_positionAttrib == -1)
	{
		printf("v_position attribute not found\n");
		anyProblem = false;
	}
	
	// Locate the texture vertex attribute
	m_tcAttrib = m_shader->GetAttribLocation("texCoord");
	if (m_tcAttrib == -1)
	{
		printf("texCoord attribute not found\n");
		anyProblem = false;
	}


	glm::vec3 currentLightPos = { 0.0, 0.0, 0.0 };

	glm::mat4 view = m_camera->GetView();
	m_light = new Light(view, currentLightPos);// , lightAmbient, lightDiffuse, lightSpecular, globalAmbient);


	//globalAmbient
	GLuint globalAmbLoc = glGetUniformLocation(m_shader->GetShaderProgram(), "GlobalAmbient");
	if (globalAmbLoc == INVALID_UNIFORM_LOCATION) {
		printf("globalAmbient element not found\n");
		return false;
	}
	glProgramUniform4fv(m_shader->GetShaderProgram(), globalAmbLoc, 1, m_light->m_globalAmbient);

	//ambient
	GLuint lightALoc = glGetUniformLocation(m_shader->GetShaderProgram(), "light.ambient");
	if (lightALoc == INVALID_UNIFORM_LOCATION) {
		printf("Shader LightAmbient element not found\n");
		return false;
	}
	glProgramUniform4fv(m_shader->GetShaderProgram(), lightALoc, 1, m_light->m_lightAmbient);

	//diffuse
	GLuint lightDLoc = glGetUniformLocation(m_shader->GetShaderProgram(), "light.diffuse");
	if (lightDLoc == INVALID_UNIFORM_LOCATION) {
		printf("Shader LightDiffuse element not found\n");
		return false;
	}
	glProgramUniform4fv(m_shader->GetShaderProgram(), lightDLoc, 1, m_light->m_lightDiffuse);

	//specular
	GLuint lightSLoc = glGetUniformLocation(m_shader->GetShaderProgram(), "light.spec");
	if (lightSLoc == INVALID_UNIFORM_LOCATION) {
		printf("Shader lightSLoc element not found\n");
		return false;
	}
	glProgramUniform4fv(m_shader->GetShaderProgram(), lightSLoc, 1, m_light->m_lightSpecular);

	//lightPosLoc
	GLuint lightPosLoc = glGetUniformLocation(m_shader->GetShaderProgram(), "light.position");
	glProgramUniform3fv(m_shader->GetShaderProgram(), lightPosLoc, 1, m_light->m_lightPositionViewSpace);
	
	m_hasTexture = m_shader->GetUniformLocation("hasTexture");
	if (m_hasTexture == INVALID_UNIFORM_LOCATION) {
		printf("hasTexture uniform not found\n");
		anyProblem = false;
	}


	return anyProblem;
}

std::string Graphics::ErrorString(GLenum error)
{
	if (error == GL_INVALID_ENUM)
	{
		return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
	}

	else if (error == GL_INVALID_VALUE)
	{
		return "GL_INVALID_VALUE: A numeric argument is out of range.";
	}

	else if (error == GL_INVALID_OPERATION)
	{
		return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
	}

	else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
	{
		return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
	}

	else if (error == GL_OUT_OF_MEMORY)
	{
		return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
	}
	else
	{
		return "None";
	}
}

