#include "Zach.h"

Animation Zach::idle;
Animation Zach::walk;
Texture* Zach::textureAtlas;
Zach* Zach::grabbed = nullptr;

void ZachOnCollision(const HitBox& thisHb, const HitBox& otherHb) {
	// https://stackoverflow.com/questions/8515198/basic-aabb-collision-using-projection-vector
	// http://www.metanetsoftware.com/technique/tutorialA.html
	// --^ good references for collision resolution
	if (otherHb.tag == HitBoxType::Player) {
		// Get diff of vectors then negate then move that way
		//glm::vec2 dist = other.parentEntity->transform.GetPosition() - transform.GetPosition();
		glm::vec2 pos = thisHb.GetGlobalPosition();
		glm::vec2 otherPos = otherHb.GetGlobalPosition();
		glm::vec2 scale = 0.5f * thisHb.localTransform.GetScale();
		glm::vec2 otherScale = 0.5f * otherHb.localTransform.GetScale();

		// TODO: this is dumb
		// ^ also seems to only work if an entity spawned after pushes an entity spawned before
		float sign = 0.0f;
		if (otherPos.x > pos.x) sign = -1.0f;
		else sign = 1.0f;

		glm::vec2 interlap = (scale + otherScale) - glm::abs(pos - otherPos);
		thisHb.parentEntity->transform.Translate(sign * interlap.x, 0.0f);
	}
}

Zach::Zach(float xPos, float yPos, float xScale, float yScale, float rotation, const std::string name, int layer)
	: Entity(xPos, yPos, xScale, yScale, rotation, name, layer), subTexture(SubTexture()), animator(), physicsController(&transform)
{
	hitBox = HitBox(0.0f, 0.0f, xScale/2.0f, yScale, this, &ZachOnCollision, HitBoxType::Player);
	InitializeAnimations();
}

#pragma region MOVE_CONSTRUCTORS

Zach::Zach(Zach&& other) noexcept {
	this->transform = other.transform;
	this->animator = std::move(other.animator);
	this->subTexture = other.subTexture;
	this->walkSpeed = other.walkSpeed;
	this->physicsController = other.physicsController;
	physicsController.SetTransform(&transform);
	this->name = std::move(other.name);
	this->hitBox = other.hitBox;
	hitBox.parentEntity = this;
}

Zach& Zach::operator=(Zach&& other) noexcept {
	if (this != &other) {
		this->transform = other.transform;
		this->animator = std::move(other.animator);
		this->subTexture = other.subTexture;
		this->walkSpeed = other.walkSpeed;
		this->physicsController = other.physicsController;
		physicsController.SetTransform(&transform);
		this->name = std::move(other.name);
		this->hitBox = other.hitBox;
		hitBox.parentEntity = this;
	}

	return *this;
}
#pragma endregion

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
	// Drag and drop zachs with right click
	if (InputManager::GetMouseButton(GLFW_MOUSE_BUTTON_2)){
		glm::vec2 mousePos = InputManager::GetWorldMousePos(Window::width, Window::height, SceneManager::GetCurrentScene()->mainCamera->right, SceneManager::GetCurrentScene()->mainCamera->transform);
		if ((!grabbed || grabbed == this) && hitBox.Contains(mousePos)) {
			transform.SetPosition(mousePos);
			grabbed = this;
			return;
		}
	}
	else {
		grabbed = nullptr;
	}
	// Gravity
	if (transform.GetPosition().y < 0.5f) {
		physicsController.acceleration.y = 9.0f;
	}
	else {
		physicsController.acceleration.y = 0.0f;
		physicsController.velocity.y = 0.0f;
	}
	// Movement
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
	// Jump
	if (InputManager::GetKeyDown(GLFW_KEY_UP)) {
		physicsController.velocity.y = -2.0f;
	}

	// Updates
	physicsController.Update(dt);
	animator.Update(dt);
	subTexture = animator.GetCurrentFrame().subTexture;
}


void Zach::UpdateMultiple(float dt, std::vector<Zach>* zachs) {
	for (int i = 0; i < zachs->size(); i++) {
		(*zachs)[i].Update(dt);
	}
}