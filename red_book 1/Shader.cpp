#include "Shader.h"



Shader::Shader()
{
	shaderID = 0;
	/*uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;

	pointLightCount = 0;*/
}

GLboolean Shader::CreateShader(ShaderInfo* shaderInfo)
{
	shaderID = LoadShaders(shaderInfo);
	return true;
}



void Shader::UseShader()
{
	glUseProgram(shaderID);
}

Shader::~Shader()
{
}
