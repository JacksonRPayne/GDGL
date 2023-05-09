#pragma once
#include <glm/glm.hpp>
#include "graphics/Transform.h"

class PhysicsController
{
public:
	PhysicsController() : transform(nullptr){}
	PhysicsController(Transform* transform);
	
	void Update(float dt);

	void Translate(glm::vec2 translation);
	void Translate(float xTrans, float yTrans) { Translate(glm::vec2(xTrans, yTrans)); }
	void SetTransform(Transform* t) { transform = t; }

	glm::vec2 velocity;
	glm::vec2 acceleration;

private:
	Transform* transform;

};

