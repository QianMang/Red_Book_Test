//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include "vgl.h"
#include "Shader.h"
using namespace std;
enum VAO_IDs { Triangles,Triangles2,NumVAOs };
enum Buffer_IDs { ArrayBuffer,ArrayBuffer2, NumBuffers };
enum Attrib_IDs { vPosition = 0 ,vColor = 1};  //can be gotten by glGetAttribLocation(program, "XXX");
enum Route {DrawArrays = 1, DrawElements = 2 , Mutiple_objects = 3};
GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
GLuint  indexBuffer;
const GLuint  NumVertices = 6;
const GLuint NumVertices2 = 4;

//----------------------------------------------------------------------------
//
// init
//
Shader* InitShader() {
	ShaderInfo  shadersInfo[] =
	{
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};
	Shader *shader = new Shader();
	shader->CreateShader(shadersInfo);
	shader->UseShader();
	return shader;
}

void init1(void)
{
	glCreateVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	
	const GLfloat  vertices[NumVertices][2] = {
		{ -0.80f, -0.80f },{ 0.85f, -0.90f },{ -0.90f,  0.85f },  // Triangle 1
		{ 0.90f, -0.85f },{ 0.90f,  0.90f },{ -0.85f,  0.90f }   // Triangle 2
	};
	GLfloat colors[NumVertices][4] = {
		{1,0,0,0},{1,0,0,0},{1,0,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}
	};
	glCreateBuffers(1, Buffers);
//---------------------------------------------3 types of buffer storage
// 1.glBufferStorage()
	/*glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);*/

// 2.glNamedBufferStorage()
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices)+sizeof(colors), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(Buffers[ArrayBuffer], 0, sizeof(vertices), vertices);
	glNamedBufferSubData(Buffers[ArrayBuffer], sizeof(vertices), sizeof(colors), colors);

// 3.glMapNamedBuffer()
	
	//glBufferData(GL_COPY_WRITE_BUFFER, sizeof(vertices)+sizeof(colors), 0, GL_DYNAMIC_DRAW);
	//GLfloat *ptr = reinterpret_cast<GLfloat*>(glMapBufferRange(GL_COPY_WRITE_BUFFER, 0, sizeof(vertices), GL_MAP_WRITE_BIT));
	//GLfloat *ptr2 = reinterpret_cast<GLfloat*>(glMapBufferRange(GL_COPY_WRITE_BUFFER, sizeof(vertices), sizeof(colors), GL_MAP_WRITE_BIT));
	////std::copy(vertices, vertices + sizeof(vertices), ptr);
	////std::copy(colors, colors + sizeof(colors), ptr2);
	//memcpy(ptr, vertices, sizeof(vertices)-1);
	//memcpy(ptr2, colors, sizeof(colors)-1);
	//glUnmapNamedBuffer(Buffers[ArrayBuffer]);
	//glBindBuffer(GL_COPY_WRITE_BUFFER, Buffers[ArrayBuffer]);
	
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);

	InitShader();

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
	glEnableVertexAttribArray(vColor);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//int location = glGetUniformLocation(program, "myColor");
	//glUniform4f(location, 0, 1.0, 0, 1);
}

//indexd vertices
void init2() {
	glCreateVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	
	const GLfloat  vertices[NumVertices2][2] = { //4 points
		{ -0.5f, -0.5f },{ 0.5f, -0.5f },{ -0.5f,  0.5f },  
		{ 0.5f,  0.5f }  
	};
	const GLushort vertices_index[] = {
		0,1,2,
		2,1,3
	};
	GLfloat colors[NumVertices2][4] = {
		{1,0,0,1},{0,0,0,1},{0,1,1,1},{0,1,0,1}
	};
	glGenBuffers(1, Buffers); 
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices)+sizeof(colors), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glNamedBufferSubData(Buffers[ArrayBuffer],0,sizeof(vertices),vertices);
	glNamedBufferSubData(Buffers[ArrayBuffer], sizeof(vertices), sizeof(colors), colors);
	//不要用这个傻逼东西：glNamedBufferData(Buffers[ArrayBuffer], sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
	glEnableVertexAttribArray(vColor);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices_index),vertices_index, GL_STATIC_DRAW);

	Shader* shader = InitShader();
	//GLfloat color[4] = { 0,0,0,1 };
	//shader->SetColor(color);

}

void init3() {
	const GLfloat  vertices[NumVertices][2] = {
		{ -0.80f, -0.80f },{ 0.85f, -0.90f },{ -0.90f,  0.85f },  // Triangle 1
		{ 0.0f, -0.85f },{ 0.90f,  0.0f },{ -0.85f,  0.0f }   // Triangle 2
	};
	const GLfloat  vertices2[3][2] = {
		{0.9f,0.9f} ,{-0.9f,0.9f},{0.9f, 0.f}  //Triangle 3
	};
	const GLfloat colors[NumVertices][4] = {
		{1,0,0,0},{1,0,0,0},{1,0,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}
	};
	const GLfloat colors2[3][4] = {
		{0,0,1,0},{0,0,1,0},{0,0,1,0}
	};
	InitShader();
	glGenVertexArrays(NumVAOs, VAOs);

	glBindVertexArray(VAOs[Triangles]);
	//first object
	glGenBuffers(NumBuffers, Buffers);  // here need 2 buffers to create
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	
	
	//--second object
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer2]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices2) + sizeof(colors2), nullptr, GL_DYNAMIC_STORAGE_BIT);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices2), sizeof(colors2), colors2);
	

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void drawObject(int numVertices, GLuint buffer) {
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(numVertices*2*sizeof(float)));
	

	glDrawArrays(GL_TRIANGLES, 0, numVertices);
	glDisableVertexAttribArray(vPosition);
	glDisableVertexAttribArray(vColor);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//----------------------------------------------------------------------------
//
// display
//

void display1(void)
{
	static const float background[] = { 1.0f, 0.5f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, background);
	glBindVertexArray(VAOs[Triangles]);
	//drawing command
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
	
	
}

void display2(void) {
	static const float background[] = { 1.0f, 0.5f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, background);
	glBindVertexArray(VAOs[Triangles]);
	//drawing command
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_SHORT,0);
}

void display3(void) {
	static const float background[] = { 1.0f, 0.5f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, background);
	

	drawObject(NumVertices, Buffers[ArrayBuffer]);
	drawObject(3, Buffers[ArrayBuffer2]);

}

void Loop(GLFWwindow* window, void init(), void display()) {
	init();
	while (!glfwWindowShouldClose(window))
	{
		display();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}
//----------------------------------------------------------------------------
//
// main
//

//#ifdef _WIN32
//int CALLBACK WinMain(
//	_In_ HINSTANCE hInstance,
//	_In_ HINSTANCE hPrevInstance,
//	_In_ LPSTR     lpCmdLine,
//	_In_ int       nCmdShow
//)
//#else
int main(int argc, char** argv)
//#endif
{
	//---------------------------Route---------------------
	int route;
	cout << "-------------------------------------------------" << endl;
	cout << "1.two seperate traingles(glDrawArrays)" << endl;
	cout << "2.two traingles using same edge(index-glDrawElement)" << endl;
	cout << "3.multiple object to render" << endl;
	cout << "input:";
	cin >> route;


	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);
	glfwMakeContextCurrent(window);
	gl3wInit();

	
	const GLubyte* version = glGetString(GL_VERSION);
	cout << version << endl;

	
	if (route == Route::DrawArrays) {
		Loop(window,init1, display1);
	}
	else if (route == Route::DrawElements) {
		Loop(window, init2, display2);
	}
	else if (route == Route::Mutiple_objects) {
		Loop(window, init3, display3);
	}
	
	glfwDestroyWindow(window);

	glfwTerminate();
}


