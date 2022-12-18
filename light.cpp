#include "light.h"

Light::Light(glm::mat4 viewMatrix, glm::vec3 currentLightPos, glm::vec4 lightAmb){
	m_lightPosition = currentLightPos;
	transformed = glm::vec3(viewMatrix * glm::vec4(m_lightPosition, 1.0));
	m_lightPositionViewSpace[0] = transformed.x;
	m_lightPositionViewSpace[1] = transformed.y;
	m_lightPositionViewSpace[2] = transformed.z;
}

Light::Light(glm::mat4 viewMatrix, glm::vec3 currentLightPos){// glm::vec4 lightAmb, glm::vec4 lightDiff, glm::vec4 lightSpec, glm::vec4 gAmb) {
	transformed = glm::vec3(viewMatrix * glm::vec4(m_lightPosition, 1.0));
	m_lightPositionViewSpace[0] = transformed.x;
	m_lightPositionViewSpace[1] = transformed.y;
	m_lightPositionViewSpace[2] = transformed.z;

	// white light
	float globalAmbient[4] = { 0.1f, 0.1f, 0.1f, 0.1f };
	float lightAmbient[4] = { 0.1f, 0.1f, 0.1f, .1f };
	float lightDiffuse[4] = { .2f, .2f, .2f, .2f };
	float lightSpecular[4] = { .2f, .2f, .2f, .2f };

	m_lightAmbient[0] = lightAmbient[0];
	m_lightAmbient[1] = lightAmbient[1];
	m_lightAmbient[2] = lightAmbient[2];
	m_lightAmbient[3] = lightAmbient[3];
	m_lightDiffuse[0] = lightDiffuse[0];
	m_lightDiffuse[1] = lightDiffuse[1];
	m_lightDiffuse[2] = lightDiffuse[2];
	m_lightDiffuse[3] = lightDiffuse[3];
	m_lightSpecular[0] = lightSpecular[0];
	m_lightSpecular[1] = lightSpecular[1];
	m_lightSpecular[2] = lightSpecular[2];
	m_lightSpecular[3] = lightSpecular[3];
	m_globalAmbient[0] = globalAmbient[0];
	m_globalAmbient[1] = globalAmbient[1];
	m_globalAmbient[2] = globalAmbient[2];
	m_globalAmbient[3] = globalAmbient[3];

}