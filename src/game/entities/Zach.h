#pragma once
#include "system/Window.h"
#include "scene/Entity.h"
#include "animation/Animation.h"
#include "system/InputManager.h"
#include "system/ResourceManager.h"
#include "physics/PhysicsController.h"
#include "physics/HitBox.h"
#define ANIM_SPEED 9.0f


// This is a demo class to demonstrate how to create specific entity behavior
class Zach : public Entity
{
public:
	Zach(){}
	Zach(float xPos, float yPos, float xScale, float yScale, float rotation, const std::string name="Zach", int layer = 0);
	Zach& operator=(Zach&& other) noexcept;
	Zach(Zach&& other) noexcept;

	void Render(Renderer* renderer) override;
	void Update(float dt) override;

	void SetTexture(Texture* texture);

	static void UpdateMultiple(float dt, std::vector<Zach>* zachs);
	static void RenderMultiple(Renderer* renderer, std::vector<Zach>* zachs);

	// Sets up animations for zachs
	static void LoadAnimations();
	// Destroys data in animations (if entity wont be used for a while)
	static void UnloadAnimations();

	static Animation idle;
	static Animation walk;
	// Used to track if theres a zach being held by mouse
	static Zach* grabbed;

	HitBox hitBox;

private:
	void InitializeAnimations();
	Animator animator;
	PhysicsController physicsController;

	static Texture* textureAtlas;
	SubTexture subTexture;

	float walkSpeed = 1.0f;
};

