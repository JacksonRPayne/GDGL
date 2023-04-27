#version 330 core

layout (location=0) out vec4 color;

in vec4 v_color;
in vec2 v_texCoord;
flat in float v_texSlot;

uniform sampler2D[16] textures;

void main(){
	// TODO: theres one wasted slot bc 0 doesn't bind a texture 
	switch(int(v_texSlot)){
		case -1: color = v_color; break;
		case 0: color = texture(textures[0], v_texCoord) * v_color; break;
		case 1: color = texture(textures[1], v_texCoord) * v_color; break;
		case 2: color = texture(textures[2], v_texCoord) * v_color; break;
		case 3: color = texture(textures[3], v_texCoord) * v_color; break;
		case 4: color = texture(textures[4], v_texCoord) * v_color; break;
		case 5: color = texture(textures[5], v_texCoord) * v_color; break;
		case 6: color = texture(textures[6], v_texCoord) * v_color; break;
		case 7: color = texture(textures[7], v_texCoord) * v_color; break;
		case 8: color = texture(textures[8], v_texCoord) * v_color; break;
		case 9: color = texture(textures[9], v_texCoord) * v_color; break;
		case 10: color = texture(textures[10], v_texCoord) * v_color; break;
		case 11: color = texture(textures[11], v_texCoord) * v_color; break;
		case 12: color = texture(textures[12], v_texCoord) * v_color; break;
		case 13: color = texture(textures[13], v_texCoord) * v_color; break;
		case 14: color = texture(textures[14], v_texCoord) * v_color; break;
		case 15: color = texture(textures[15], v_texCoord) * v_color; break;
	};
}