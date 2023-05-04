#include "ResourceManager.h"

// Declares maps
std::unordered_map<std::string, Texture*> ResourceManager::textureMap;
std::unordered_map<std::string, Shader*> ResourceManager::shaderMap;


void ResourceManager::LoadTexture(const char* path, const std::string& name, bool alpha) {
	// Don't reload texture
	if (textureMap.count(name)) return;
	
	Texture* texture = new Texture(path, alpha);
	textureMap[name] = texture;
}


void ResourceManager::LoadShader(const char* vertPath, const char* fragPath, const std::string& name) {
	// Don't reload shader
	if (shaderMap.count(name)) return;

	Shader* shader = new Shader(vertPath, fragPath);
	shaderMap[name] = shader;
}

// TODO: add checks to see if key exists
Texture* ResourceManager::GetTexture(const std::string& name) {
	if (!textureMap.count(name)) {
		Log::LogError("Texture " + name + " not found");
	}
	return textureMap[name];
}
Shader* ResourceManager::GetShader(const std::string& name) { 
	if (!shaderMap.count(name)) {
		Log::LogError("Shader " + name + " not found");
	}
	return shaderMap[name]; 
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