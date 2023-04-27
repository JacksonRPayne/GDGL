#version 330 core

out vec4 color;

in vec2 texCoord;

uniform sampler2D Texture;

void main(){
	color = texture(Texture, texCoord);
}