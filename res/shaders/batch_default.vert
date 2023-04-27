#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float texSlot;

uniform mat4 view;
uniform mat4 projection;

out vec4 v_color;
out vec2 v_texCoord;
flat out float v_texSlot;

void main(){
	gl_Position = projection * view * vec4(position, 1.0);
	v_color = color;
	v_texCoord = texCoord;
	v_texSlot = texSlot;
}