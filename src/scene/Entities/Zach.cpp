#include "Zach.h"

Zach::Zach(float xPos, float yPos, float xScale, float yScale, float rotation, int layer)
	: Entity(xPos, yPos, xScale, yScale, rotation, layer), textureAtlas(nullptr), subTexture(SubTexture()), animator()
{
}

Zach::Zach(float xPos, float yPos, float xScale, float yScale, float rotation, Texture* spriteAtlas, int layer)
	: Entity(xPos, yPos, xScale, yScale, rotation, layer), textureAtlas(spriteAtlas), subTexture(SubTexture(spriteAtlas, 0, 0, 128, 128)), animator()
{
	InitializeAnimations();
}

void Zach::InitializeAnimations() {
	// TODO: if you really want to spawn a lot of zachs, put this somewhere to only be called once and reference it
	// TODO: with move semantics, can I take this animation and move it all the way into the animator with no copies?
	Animation idle = Animation();
	idle.SetPlaySpeed(ANIM_SPEED);
	idle.AddFrame(Frame(SubTexture(textureAtlas, 0, 0, 128, 128)));
	idle.AddFrame(Frame(SubTexture(textureAtlas, 1 * 128, 0, 128, 128)));
	idle.AddFrame(Frame(SubTexture(textureAtlas, 2 * 128, 0, 128, 128)));
	idle.AddFrame(Frame(SubTexture(textureAtlas, 3 * 128, 0, 128, 128)));
	idle.AddFrame(Frame(SubTexture(textureAtlas, 4 * 128, 0, 128, 128)));
	idle.AddFrame(Frame(SubTexture(textureAtlas, 5 * 128, 0, 128, 128)));
	//idle.AddFrame(Frame(SubTexture(textureAtlas, 6 * 128-32, 0, 128, 128))); this one sucks
	idle.AddFrame(Frame(SubTexture(textureAtlas, 4 * 128, 0, 128, 128)));
	idle.AddFrame(Frame(SubTexture(textureAtlas, 3 * 128, 0, 128, 128)));
	idle.AddFrame(Frame(SubTexture(textureAtlas, 2 * 128, 0, 128, 128)));
	idle.AddFrame(Frame(SubTexture(textureAtlas, 1 * 128, 0, 128, 128)));

	animator.AddAnimation("Idle", idle);

	Animation walk = Animation();
	walk.SetPlaySpeed(ANIM_SPEED);
	walk.AddFrame(Frame(SubTexture(textureAtlas, 0, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 1 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 2 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 3 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 4 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 5 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 6 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 7 * 128, 128, 128, 128)));

	animator.AddAnimation("Walk", walk);
}

void Zach::SetTexture(Texture* texture) {
	textureAtlas = texture;
	subTexture.SetValues(texture, 0, 0, 128, 128);
	InitializeAnimations();
}

void Zach::Render(Renderer* renderer) {
	renderer->DrawQuad(textureAtlas, subTexture, transform.GetModelMatrix());
}

void Zach::RenderMultiple(Renderer* renderer, std::vector<Zach>* zachs) {
	for (int i = 0; i < zachs->size(); i++) {
		(*zachs)[i].Render(renderer);
	}
}

void Zach::Update(float dt) {
	if (InputManager::GetKey(GLFW_KEY_RIGHT)) {
		animator.PlayOnce("Walk", true, true);
		transform.Translate(walkSpeed * dt, 0.0f);
		transform.SetScaleX(1.0f);
	}
	else if (InputManager::GetKey(GLFW_KEY_LEFT)) {
		animator.PlayOnce("Walk", true, true);
		transform.Translate(-walkSpeed * dt, 0.0f);
		transform.SetScaleX(-1.0f);
	}
	else {
		animator.PlayOnce("Idle", true, true);
	}

	animator.Update(dt);
	subTexture = animator.GetCurrentFrame().subTexture;
}

void Zach::UpdateMultiple(float dt, std::vector<Zach>* zachs) {
	for (int i = 0; i < zachs->size(); i++) {
		(*zachs)[i].Update(dt);
	}
}