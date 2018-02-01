#shader vertex
#version 330 core

layout(location = 0) in vec4 inPosition;

void main() {
	gl_Position = inPosition;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 outColor;

void main() {
	outColor = vec4(1.0, 1.0, 1.0, 1.0);
};