#version 440 core

in vec4 color;
layout(location=0) out vec4 fColor;

uniform vec4 myColor;

void main()

{
     
		fColor = color;

}
