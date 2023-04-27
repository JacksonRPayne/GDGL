#pragma once

#include "graphics/Transform.h"
#include "graphics/Texture.h"
#include "graphics/SpriteRenderer.h"


class Entity
{
public:

	Entity();
	// Maybe add overload with glm::vec2
	Entity(float xPos, float yPos, float xScale, float yScale, float rotation, int layer=0);

	virtual ~Entity() {};

	virtual void Render(Renderer* renderer) {}
	// Overloaded with specific entity behavior
	virtual void Update(float dt) {}

	void SetRenderingLayer(int newLayer) { layer = std::min(newLayer, MAX_LAYERS); }
	unsigned int GetRenderingLayer() { return layer; }

	Transform transform;

protected:

	// Rendering layer
	unsigned int layer;
};

