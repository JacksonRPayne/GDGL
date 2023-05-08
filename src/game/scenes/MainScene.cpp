#include "MainScene.h"

struct MainEntities {
	MainEntities() = default;
	Zach zach;
	// NOTE/TODO: try to make these arrays as much as possible
	// Vector reallocation gets super slow with mad entities bc theyre not pointers :(
	// ^-- although when am I gonna spawn a billion entities realistically
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
	// TODO: you're gonna want to look into move semantics...
	// -- especially in the animation and animator classes, or really anything with a member thats a collection
	ResourceManager::LoadTexture("res/textures/Zach.png", "zach");
	entities.zach = std::move(Zach(0.0f, 0.0f, 1.0f, 1.0f, 0.0f));
	entities.spawnedZachs = std::vector<Zach>();
	loaded = true;
}


// TODO: to avoid OOP, you could add camera and renderer to mainscene data, and pass arguments into Start(Camera* camera, Renderer* renderer) like a constructor
void MainScene::Start() {

}

void MainScene::Update(float dt) {
	if (InputManager::GetMouseButton(GLFW_MOUSE_BUTTON_1)) {
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
	if (InputManager::GetKeyDown(GLFW_KEY_S)) {
		mainCamera->transform.ScaleFactor(2.0f, 2.0f);
	}
	else if (InputManager::GetKeyDown(GLFW_KEY_W)) {
		mainCamera->transform.ScaleFactor(0.5f, 0.5f);
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

