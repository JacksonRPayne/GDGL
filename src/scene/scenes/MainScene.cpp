#include "MainScene.h"

struct MainEntities {
	MainEntities() = default;
	Zach zach;
	//std::vector<Zach> spawnedZachs;
	// ^note: to allow for multiple of an entity to be renderered and updated in a scene without annoying code rewriting
	// but also avoiding OOP, for each entity define 2 *functions* (not methods) that takes in a vector of that entity type
	// and updates/renders it. Ex: void UpdateZachs(const std::vector<Zach> &zachs, float dt), and render would be similar
};

static MainEntities entities = MainEntities();

MainScene::MainScene(const std::string& name, Camera* mainCamera, Renderer* renderer) 
	: Scene(name, mainCamera, renderer){}

// TODO: to avoid OOP, you could add camera and renderer to mainscene data, and pass arguments into Start(Camera* camera, Renderer* renderer) like a constructor
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
