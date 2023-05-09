#include "Zach.h"

Animation Zach::idle;
Animation Zach::walk;
Texture* Zach::textureAtlas;

Zach::Zach(float xPos, float yPos, float xScale, float yScale, float rotation, int layer)
	: Entity(xPos, yPos, xScale, yScale, rotation, layer), subTexture(SubTexture()), animator(), physicsController(&transform)
{
	InitializeAnimations();
}

Zach::Zach(Zach&& other) noexcept {
	std::cout << "Zach move constructor" << '\n';
	this->transform = other.transform;
	this->animator = std::move(other.animator);
	this->subTexture = other.subTexture;
	this->walkSpeed = other.walkSpeed;
	this->physicsController = other.physicsController;
	physicsController.SetTransform(&transform);
}

Zach& Zach::operator=(Zach&& other) noexcept {
	std::cout << "Zach move assignment" << '\n';
	if (this != &other) {
		this->transform = other.transform;
		this->animator = std::move(other.animator);
		this->subTexture = other.subTexture;
		this->walkSpeed = other.walkSpeed;
		this->physicsController = other.physicsController;
		physicsController.SetTransform(&transform);

	}

	return *this;
}

void Zach::LoadAnimations() {
	// Loads atlas for all Zachs
	if(!textureAtlas) textureAtlas = ResourceManager::GetTexture("zach");
	// Creates idle animation
	idle = Animation();
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
	
	// Creates walk animation
	walk = Animation();
	walk.SetPlaySpeed(ANIM_SPEED);
	walk.AddFrame(Frame(SubTexture(textureAtlas, 0, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 1 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 2 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 3 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 4 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 5 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 6 * 128, 128, 128, 128)));
	walk.AddFrame(Frame(SubTexture(textureAtlas, 7 * 128, 128, 128, 128)));
}

void Zach::UnloadAnimations() {
	idle = Animation();
	walk = Animation();
}

void Zach::InitializeAnimations() {
	if (!idle.GetFrames().size()) Zach::LoadAnimations();
	// TODO: with move semantics, can I take this animation and move it all the way into the animator with no copies? 
	animator.AddAnimation("Idle", &idle);
	animator.AddAnimation("Walk", &walk);
}

void Zach::SetTexture(Texture* texture) {
	textureAtlas = texture;
	subTexture.SetValues(texture, 0, 0, 128, 128);
	InitializeAnimations();
}

void Zach::Render(Renderer* renderer) {
	renderer->DrawQuad(Zach::textureAtlas, subTexture, transform.GetModelMatrix());
}

void Zach::RenderMultiple(Renderer* renderer, std::vector<Zach>* zachs) {
	for (int i = 0; i < zachs->size(); i++) {
		(*zachs)[i].Render(renderer);
	}
}

void Zach::Update(float dt) {

	physicsController.acceleration.x = 0.1f;

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

	physicsController.Update(dt);
	animator.Update(dt);
	subTexture = animator.GetCurrentFrame().subTexture;
}

void Zach::UpdateMultiple(float dt, std::vector<Zach>* zachs) {
	for (int i = 0; i < zachs->size(); i++) {
		(*zachs)[i].Update(dt);
	}
}