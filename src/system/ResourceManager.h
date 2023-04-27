#pragma once
#include <map>
#include <string>
#include "graphics/Shader.h"
#include "graphics/Texture.h"


class ResourceManager
{
public:

	// For loading shaders and textures and storing them in their maps
	static void LoadShader(const char* vertPath, const char* fragPath, const std::string& name);
	// Alpha pre set to true as PNG will be most common
	static void LoadTexture(const char* path, const std::string& name, bool alpha = true);

	// TODO: add checks to see if key exists
	static Texture* GetTexture(const std::string& name) { return textureMap[name]; }
	static Shader* GetShader(const std::string& name) { return shaderMap[name]; }

	// Deallocates all resources
	static void FreeAll();
	// For now these functions do not delete from map, simply deallocate
	static void UnloadTexture(const std::string& name);
	static void UnloadShader(const std::string& name);
private:
	// Takes in a name and returns a shader/texture
	// TODO: make these store pointers instead for less copying
	static std::map<std::string, Texture*> textureMap;
	static std::map<std::string, Shader*> shaderMap;

};

