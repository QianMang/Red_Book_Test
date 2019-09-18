#pragma once
#include<iostream>
#include "vgl.h"
#include "LoadShaders.h"
class Shader
{
public:
	Shader();
	GLboolean CreateShader(ShaderInfo*);
	void UseShader();
	void SetColor(GLfloat*);
	~Shader();

private:
	GLuint shaderID;// uniformModel, uniformProjection, uniformView, pointLightCount;
};

