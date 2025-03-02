#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoords;

out vec3 normal;
out vec3 fragPos;
out vec2 textureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	fragPos = vec3(model * vec4(position, 1.0));
	normal = mat3(transpose(inverse(model))) * normals;
	textureCoords = texCoords;
	
	gl_Position = projection * view * model * vec4(position, 1.0);
};