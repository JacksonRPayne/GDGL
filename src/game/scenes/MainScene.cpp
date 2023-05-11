#include "MainScene.h"

struct MainEntities {
	MainEntities() = default;
	Zach zach;
	Baby baby;
	std::vector<Zach> spawnedZachs;
	// NOTE/TODO: try to make these arrays as much as possible
	// Vector reallocation gets super slow with mad entities bc theyre not pointers :(
	// ^-- although when am I gonna spawn a billion entities realistically
	void Update(float dt) {
		zach.Update(dt);
		baby.Update(dt);
		Zach::UpdateMultiple(dt, &spawnedZachs);
	}

	void Render(Renderer* renderer) {
		renderer->Start();

		//zach.Render(renderer);
		baby.Render(renderer);
		Zach::RenderMultiple(renderer, &spawnedZachs);

		renderer->End();
	}
};

static MainEntities entities = MainEntities();


MainScene::MainScene(const std::string& name, Camera* mainCamera, Renderer* renderer) 
	: Scene(name, mainCamera, renderer){}


void MainScene::Load() {

	ResourceManager::LoadTexture("res/textures/Zach.png", "zach");
	ResourceManager::LoadTexture("res/textures/Baby.png", "baby");
	entities.zach = std::move(Zach(0.0f, 0.5f, 1.0f, 1.0f, 0.0f));
	entities.baby = Baby(1.0f, 0.5f, 0.5f, 0.5f, 0.0f);
	entities.spawnedZachs.reserve(100);
	loaded = true;
}


// TODO: to avoid OOP, you could add camera and renderer to mainscene data, and pass arguments into Start(Camera* camera, Renderer* renderer) like a constructor
void MainScene::Start() {

}

void MainScene::Update(float dt) {
	if (InputManager::GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
		glm::vec2 mousePos = InputManager::GetWorldMousePos(Window::width, Window::height, mainCamera->right, mainCamera->transform);
		entities.spawnedZachs.emplace_back(mousePos.x, mousePos.y, 1.0f, 1.0f, 0.0f);
	}

	if (InputManager::GetKeyDown(GLFW_KEY_L)) {
		SceneManager::SetCurrentScene("main");
	}

	if (InputManager::GetKey(GLFW_KEY_D)) {
		mainCamera->transform.Translate(2 * dt, 0.0f);
	}
	else if (InputManager::GetKey(GLFW_KEY_A)) {
		mainCamera->transform.Translate(-2 *dt, 0.0f);
	}
	if (InputManager::GetKey(GLFW_KEY_S)) {
		mainCamera->transform.Scale(2.0f*dt, 2.0f * dt);
	}
	else if (InputManager::GetKey(GLFW_KEY_W)) {
		mainCamera->transform.Scale(-2.0f * dt, -2.0f * dt);
	}

	// Collision checks
	for (int i = 0; i < entities.spawnedZachs.size(); i++) {
		entities.zach.hitBox.CheckCollision(entities.spawnedZachs[i].hitBox);
		for (int j = 0; j < entities.spawnedZachs.size(); j++) {
			if (j == i) continue;
			entities.spawnedZachs[i].hitBox.CheckCollision(entities.spawnedZachs[j].hitBox);
		}
	}
	// UPDATE:
	entities.Update(dt);

	// RENDER
	entities.Render(renderer);

}

void MainScene::End() {
	Unload();
}

void MainScene::Unload() {
	// Unload all the stuff
	entities = MainEntities();
	// Not totally necessary -- should only really be called if entity is only in this scene
	Zach::UnloadAnimations();
	//ResourceManager::UnloadTexture("zach");
	loaded = false;
}

