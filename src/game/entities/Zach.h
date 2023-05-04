#pragma once
#include "scene/Entity.h"
#include "animation/Animation.h"
#include "system/InputManager.h"
#include "system/ResourceManager.h"
#define ANIM_SPEED 9.0f


// This is a demo class to demonstrate how to create specific entity behavior
class Zach : public Entity
{
public:
	Zach(){}
	Zach(float xPos, float yPos, float xScale, float yScale, float rotation, int layer = 0);

	void Render(Renderer* renderer) override;
	void Update(float dt) override;

	void SetTexture(Texture* texture);

	static void UpdateMultiple(float dt, std::vector<Zach>* zachs);
	static void RenderMultiple(Renderer* renderer, std::vector<Zach>* zachs);

	// Sets up animations for zachs
	static void LoadAnimations();
	// Destroys data in animations (if entity wont be used for a while)
	static void UnloadAnimations();

	// TODO: this is about to cause problems
	// -- I want to turn animations into pointers for an Animator
	// -- however, the state of an animations progress is stored in the animation object itself
	// -- therefore if all entities share an animation, they share its progress as well.
	// -- solution: move animation progress outside of animation object (put in animator?)
	static Animation idle;
	static Animation walk;

private:
	void InitializeAnimations();
	Animator animator;

	static Texture* textureAtlas;
	SubTexture subTexture;

	float walkSpeed = 1.0f;
};

