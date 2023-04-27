#include "ResourceManager.h"

// Declares maps
std::map<std::string, Texture*> ResourceManager::textureMap;
std::map<std::string, Shader*> ResourceManager::shaderMap;


void ResourceManager::LoadTexture(const char* path, const std::string& name, bool alpha) {
	Texture* texture = new Texture(path, alpha);
	textureMap[name] = texture;
}


void ResourceManager::LoadShader(const char* vertPath, const char* fragPath, const std::string& name) {
	Shader* shader = new Shader(vertPath, fragPath);
	shaderMap[name] = shader;
}


void ResourceManager::FreeAll() {
	// Deallocates all textures
	for (auto const& t : textureMap) {
		UnloadTexture(t.first);
	}
	// Empties map
	textureMap.clear();
	// Deallocates all shaders
	for (auto const& s : shaderMap) {
		UnloadShader(s.first);
	}
	shaderMap.clear();
}

void ResourceManager::UnloadTexture(const std::string &name) {
	delete GetTexture(name);
}

void ResourceManager::UnloadShader(const std::string &name) {
	delete GetShader(name);
}