#pragma once
#include <string>
#include "scene/Entity.h"
#include "graphics/Transform.h"

class Entity;

// Groups hitboxes into types
enum class HitBoxType {
	None = 0,
	Ground = 1,
	Player = 2
};

struct HitBox
{
	HitBox();
	HitBox(float xPos, float yPos, float xScale, float yScale, Entity* parent,
		void(*callback)(const HitBox& thisHitBox, const HitBox& otherHitBox),  HitBoxType tag=HitBoxType::None, bool active=true);

	// Checks collision with another hitbox and calls parent entity callback
	bool CheckCollision(const HitBox& other);
	// Checks if hitbox contains point
	bool Contains(glm::vec2 point);
	// Gets the position in relation to the world
	glm::vec2 GetGlobalPosition() const;

	bool active;
	// Stores the position in relation to the parent entity
	Transform localTransform;
	Entity* parentEntity;
	HitBoxType tag;
	// Calls function on a collision
	void(*collisionCallback)(const HitBox& thisHitBox, const HitBox& otherHitBox);
};

