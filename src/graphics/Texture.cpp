#include "Texture.h"

Texture::Texture() : texID(0), width(0), height(0), channels(0), boundSlot(-1) {
	glGenTextures(1, &texID);
}

Texture::Texture(const char* path, bool png) : texID(0), width(0), height(0), channels(0), boundSlot(-1) {
	glGenTextures(1, &texID);
	Load(path, png);
}

Texture::~Texture() {
	glDeleteTextures(1, &texID);
}

// No support for texture slots (probably fine)
void Texture::Bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texID);
	boundSlot = slot;
}

void Texture::Unbind() {
	if (boundSlot < 0) return;
	glActiveTexture(GL_TEXTURE0 + boundSlot);
	glBindTexture(GL_TEXTURE_2D, 0);
	boundSlot = -1;
}

void Texture::Load(const char* path, bool alpha) {
	// Load texture image
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	// Checks for loading error
	if (!data) {
		std::stringstream msg;
		msg << "Could not load texture: " << path;
		Log::LogError(msg.str());
		stbi_image_free(data);
		return;
	}
	// Load texture data into opengl and generate mipmaps (them tiny res textures)
	Bind();
	// Loads differently if theres an alpha channel
	if (alpha) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); }
	glGenerateMipmap(GL_TEXTURE_2D);
	// Sets texture parameters (hard coded for now)
	// Nearest filtering for minimizing and magnifying
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Repeat on in every direction
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Frees image data and unbinds texture
	stbi_image_free(data);
	Unbind();
}