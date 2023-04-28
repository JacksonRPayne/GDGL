#include "MainScene.h"

struct MainEntities {
	MainEntities() = default;
	Zach zach;
	//std::vector<Zach> spawnedZachs;
};

static MainEntities entities = MainEntities();

MainScene::MainScene(const std::string& name, Camera* mainCamera, Renderer* renderer) 
	: Scene(name, mainCamera, renderer){}

void MainScene::Start() {
	ResourceManager::LoadTexture("res/textures/Zach.png", "zach");
	entities.zach = Zach(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, ResourceManager::GetTexture("zach"));
	// TODO: I think the issue is still with the operator overload
	// -- I THINK THE ISSUE IS I NEED TO DEFINE VALID COPY CONSTRUCTOR
	// stack allocating is almost more complicated than heap allocating :'(
	//entities.spawnedZachs = std::vector<Zach>();
}

void MainScene::Update(float dt) {
	/*if (InputManager::GetMouseButton(GLFW_MOUSE_BUTTON_1)) {
		glm::vec2 mousePos = InputManager::GetWorldMousePos(Window::width, Window::height, mainCamera->right, mainCamera->transform);
		Zach zach = Zach(mousePos.x, mousePos.y, 1.0f, 1.0f, 0.0f, ResourceManager::GetTexture("Zach.png"));
		entities.spawnedZachs.push_back(zach);
	}*/
	// START RENDER
	renderer->Start();
	// ZACH
	entities.zach.Update(dt);
	entities.zach.Render(renderer);
	// SPAWNED
	/*for (Zach z : entities.spawnedZachs) {
		z.Update(dt);
		z.Render(renderer);
	}*/
	renderer->End();
}