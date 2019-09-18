
#version 440 core
#pragma optimize(on)
//#error __LINE__

in vec4 vPosition;
in vec4 vColor;

out vec4 color;

int test(int t){
	return t+1;
}

void main()
{
	float array[3] = float[3](1.0, 2.0 ,3.0);
    int a=1;
	int b=test(a);
	color = vColor;
	gl_Position = vPosition;

}

