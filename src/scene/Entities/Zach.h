#pragma once
#include "scene/Entity.h"
#include "animation/Animation.h"
#include "system/InputManager.h"
#define ANIM_SPEED 9.0f


// This is a demo class to demonstrate how to create specific entity behavior
class Zach : public Entity
{
public:
	Zach():textureAtlas(nullptr){}
	Zach(float xPos, float yPos, float xScale, float yScale, float rotation, int layer = 0);
	Zach(float xPos, float yPos, float xScale, float yScale, float rotation, Texture* spriteAtlas, int layer = 0);

	void Render(Renderer* renderer) override;
	void Update(float dt) override;

	void SetTexture(Texture* texture);

private:
	void InitializeAnimations();
	Animator animator;

	Texture* textureAtlas;
	SubTexture subTexture;

	float walkSpeed = 1.0f;
};

