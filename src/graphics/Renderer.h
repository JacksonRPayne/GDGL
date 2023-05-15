#pragma once
#include "scene/Camera.h"
#include "Texture.h"
#include "Shader.h"


// Superclass of renderers, not meant to be instantiated as an object
class Renderer
{
public:

	// Start and end functions creates an API that supports batch rendering

	// Starts the rendering for the frame
	virtual void Start();
	virtual void DrawQuad(glm::vec4 color, const glm::mat4& modelMatrix){}
	// Renders quad with texture
	virtual void DrawQuad(Texture* texture, const glm::mat4 &modelMatrix){}
	// Renders quad with subtexture
	virtual void DrawQuad(Texture* texture, const SubTexture& subTexture, const glm::mat4& modelMatrix) {}
	virtual void DrawLine(glm::vec2 startPos, glm::vec2 endPos, float width = 2.0f, glm::vec4 color = { 0.0f, 1.0f, 0.0f, 1.0f }) {};
	// Ends the rendering for the frame (maybe flushes)
	virtual void End();

	virtual void ChangeShader(Shader& newShader) { }


};

