#pragma once
#include "Renderer.h"
#include <stdio.h>
// 10,000 seems to be the performance sweet spot
#define MAX_QUADS 10000
#define MAX_VERTICES MAX_QUADS*4
#define MAX_INDICES MAX_QUADS*6
#define MAX_TEXTURES 2

// The format of each vertex in vertex buffer
struct QuadVertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
	float texSlot;
};

class BatchRenderer : public Renderer
{
public:

	BatchRenderer(Camera* camera, Shader* shader);
	~BatchRenderer();

	// Starts the rendering for the frame
	void Start();
	// Draws a colored quad (no texture)
	void DrawQuad(glm::vec4 color, const glm::mat4& modelMatrix);
	// Renders quad with texture
	void DrawQuad(Texture* texture, const glm::mat4& modelMatrix) override;
	// Renders quad with subtexture
	void DrawQuad(Texture* texture, const SubTexture &subTexture, const glm::mat4& modelMatrix);
	// Draws a line for debugging ONLY. Not written batched, so performance is slow but it's only for debugging
	void DrawLine(glm::vec2 startPos, glm::vec2 endPos, float width = 2.0f,  glm::vec4 color = {0.0f, 1.0f, 0.0f, 1.0f});
	// Ends the rendering for the frame (maybe flushes)
	void End();

	void ChangeShader(Shader* newShader) { shader = newShader; }

#ifdef _DEBUG
	//=======TESTING=======
	int drawCalls = 0;
#endif // DEBUG


private:

	void Initialize();
	// Renders buffer
	void Flush();

	// Quad prefix in case of later line rendering
	unsigned int quadVAO;
	unsigned int quadVBO;
	unsigned int quadIBO;
	// Stores the VBO buffer and a pointer to iterate through it
	QuadVertex* quadVertices;
	QuadVertex* quadBufferPointer;
	// Stores default quad vertices to be translated
	glm::vec4 quadVertexPositions[4];

	unsigned int numIndices;
	// Stores bound textures in this draw call
	Texture* boundTextures[MAX_TEXTURES];
	unsigned int numBoundTextures;

	Camera* camera;
	Shader* shader;
	Shader* lineShader;

};

