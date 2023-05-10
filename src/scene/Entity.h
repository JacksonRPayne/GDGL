#pragma once

#include "graphics/Transform.h"
#include "graphics/Texture.h"
#include "graphics/SpriteRenderer.h"
#include "physics/HitBox.h"

struct HitBox;

class Entity
{
public:

	Entity();
	// Maybe add overload with glm::vec2
	Entity(float xPos, float yPos, float xScale, float yScale, float rotation, const std::string& name, int layer = 0);

	virtual ~Entity() {};

	virtual void Render(Renderer* renderer) {}
	// Overloaded with specific entity behavior
	virtual void Update(float dt) {}
	virtual void OnCollision(const HitBox &other){}


	void SetRenderingLayer(int newLayer) { layer = std::min(newLayer, MAX_LAYERS); }
	unsigned int GetRenderingLayer() { return layer; }

	Transform transform;
	std::string name;

protected:

	// Rendering layer
	unsigned int layer;
};

