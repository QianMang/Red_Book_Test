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

void Shader::SetColor(GLfloat* color)
{
	glUniform1fv(glGetUniformLocation(shaderID, "myColor"), 4, color);
}

Shader::~Shader()
{
}
