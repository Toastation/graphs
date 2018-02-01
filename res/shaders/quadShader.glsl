#shader vertex
#version 330 core

layout(location = 0) in vec4 inPosition;

uniform mat4 projection;
uniform mat4 model;

void main() {
	vec4 pos = projection * model * vec4(inPosition.xy, 1.0, 1.0);
	gl_Position = vec4(pos.xy, 1.0, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 outColor;

void main() {
	outColor = vec4(1.0, 1.0, 1.0, 1.0);
};