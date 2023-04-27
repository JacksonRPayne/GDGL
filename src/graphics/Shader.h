#pragma once
#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "system/Log.h"

class Shader
{
public:

	Shader();
	// For loading the files while declaring
	Shader(const char* vertPath, const char* fragPath);
	~Shader();
	// Activates this shader
	void Use() const;
	// Takes in shader source code files and compiles and links them
	void LoadFiles(const char* vertPath, const char* fragPath);

	// Uniforms:
	void SetVec3(const char* uniform, const glm::vec3 &value) const;
	void SetMat4(const char* uniform, const glm::mat4& value) const;
	void SetInts(const char* uniform, int count, const int* value) const; // For array of ints

private:
	// Compiles source code and links it
	void CompileShader(const char* srcVert, const char* srcFrag);
	// Finds specified uniform and returns id
	int FindUniform(const char* uniform) const;
	// opengl IDs to the vertex and fragment shader, as well as the shader program
	unsigned int vert;
	unsigned int frag;
	unsigned int program;

	bool compiled;
};



