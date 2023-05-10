#include "Entity.h"

Entity::Entity() : transform(Transform()), layer(0){}

Entity::Entity(float xPos, float yPos, float xScale, float yScale, float rotation, const std::string& name, int layer)
	: transform(Transform(xPos, yPos, xScale, yScale, rotation)), layer(layer), name(name) {}
