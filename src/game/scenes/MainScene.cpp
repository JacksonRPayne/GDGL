#include "MainScene.h"

struct MainEntities {
	MainEntities() = default;
	Zach zach;
	std::vector<Zach> spawnedZachs;

	void Update(float dt) {
		zach.Update(dt);
		Zach::UpdateMultiple(dt, &spawnedZachs);
	}

	void Render(Renderer* renderer) {
		renderer->Start();

		zach.Render(renderer);
		Zach::RenderMultiple(renderer, &spawnedZachs);

		renderer->End();
	}

};

static MainEntities entities = MainEntities();


MainScene::MainScene(const std::string& name, Camera* mainCamera, Renderer* renderer) 
	: Scene(name, mainCamera, renderer){}


void MainScene::Load() {
	ResourceManager::LoadTexture("res/textures/Zach.png", "zach");
	// TODO: you're gonna want to look into move semantics...
	// -- especially in the animation and animator classes, or really anything with a member thats a collection
	entities.zach = Zach(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, ResourceManager::GetTexture("zach"));
	entities.spawnedZachs = std::vector<Zach>();
	loaded = true;
}


// TODO: to avoid OOP, you could add camera and renderer to mainscene data, and pass arguments into Start(Camera* camera, Renderer* renderer) like a constructor
void MainScene::Start() {

}

void MainScene::Update(float dt) {
	if (InputManager::GetMouseButtonDown(GLFW_MOUSE_BUTTON_1)) {
		glm::vec2 mousePos = InputManager::GetWorldMousePos(Window::width, Window::height, mainCamera->right, mainCamera->transform);
		Zach zach = Zach(mousePos.x, mousePos.y, 1.0f, 1.0f, 0.0f, ResourceManager::GetTexture("zach"));
		entities.spawnedZachs.push_back(zach);
	}

	if (InputManager::GetKeyDown(GLFW_KEY_L)) {
		SceneManager::SetCurrentScene("main");
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
	//ResourceManager::UnloadTexture("zach");
	loaded = false;
}

// TODO: NOTE: Unload scene:
// -- How do we get rid of the memory allocated from static MainEntities entities ?
// -- One idea:
// SceneUnload(){
// entities.field1 = nothing;
// entities.field2 = nothing;
// etc;
// }
// But question: what is nullptr equivalent of stack allocated object that I can set these to?? Do i HAVE to call default constructors?
// Aha (maybe): call destructor *explicitly* ? SceneUnload(){ entities.~MainEntities(); }

