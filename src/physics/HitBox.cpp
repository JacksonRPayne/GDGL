#include "Hitbox.h"

HitBox::HitBox(): localTransform(), parentEntity(nullptr), collisionCallback(nullptr), tag(HitBoxType::None), active(true){}

HitBox::HitBox(float xPos, float yPos, float xScale, float yScale, Entity* parent, 
	void(*callback)(const HitBox& thisHitBox, const HitBox& otherHitBox), HitBoxType tag, bool active)
	: localTransform(xPos, yPos, xScale, yScale, 0.0f), parentEntity(parent), collisionCallback(callback), tag(tag), active(active){}

bool HitBox::CheckCollision(const HitBox& other) {
	if (!active || !other.active) return false;
	glm::vec2 otherPos = other.GetGlobalPosition();
	glm::vec2 pos = GetGlobalPosition();
	// Stores half size for easier border calculation
	glm::vec2 otherSize = 0.5f * other.localTransform.GetScale();
	glm::vec2 size = 0.5f * localTransform.GetScale();

	bool collision = (pos.x + size.x > otherPos.x - otherSize.x) &&
					 (pos.x - size.x < otherPos.x + otherSize.x) &&
					 (pos.y + size.y > otherPos.y - otherSize.y) &&
					 (pos.y - size.y < otherPos.y + otherSize.y);
	
	if (collision) {
		(*collisionCallback)(*this, other);
	}

	return collision;
}

bool HitBox::Contains(glm::vec2 point) {
	glm::vec2 pos = GetGlobalPosition();
	glm::vec2 size = 0.5f * localTransform.GetScale();

	return (point.x > pos.x - size.x) && (point.x < pos.x + size.x) && (point.y < pos.y + size.y) && (point.y > pos.y - size.y);
}

glm::vec2 HitBox::GetGlobalPosition() const{ 
	return parentEntity->transform.GetPosition() + localTransform.GetPosition(); 
}