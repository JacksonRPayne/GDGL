#pragma once
#include "Renderer.h"

// The number of rendering layers
#define MAX_LAYERS 16


//==================================================
//===============ANTIQUATED=========================
//==================================================
// Use BatchRenderer instead
class SpriteRenderer : public Renderer
{
public:

	SpriteRenderer(Camera* camera, Shader* shader);

	void DrawQuad(Texture* texture, const glm::mat4& modelMatrix) override;

	void ChangeShader(Shader* newShader) { shader = newShader; }

private:
	Camera* camera;
	Shader* shader;
	unsigned int VAO;
};

