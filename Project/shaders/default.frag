#version 460 core

out vec4 FragColor;

in vec2 textCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor =  mix(texture(texture1, textCoord), texture(texture2, vec2(1.0 - textCoord.x, textCoord.y)), 0.3);
};