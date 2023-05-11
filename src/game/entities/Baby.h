#pragma once
#include "scene/Entity.h"
#include "system/ResourceManager.h"

class Baby : public Entity
{
public:
	Baby() : texture(nullptr){}
	Baby(float xPos, float yPos, float xScale, float yScale, float rotation, const std::string name = "Baby", int layer = 0);
	//Baby& operator=(Baby&& other) noexcept;
	//Baby(Baby&& other);

	void Render(Renderer* renderer) override;
	void Update(float dt) override;

	//HitBox hitBox;

private:
	Texture* texture;
};

