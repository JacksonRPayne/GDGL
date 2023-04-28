#include "MainScene.h"


struct MainEntities {
	MainEntities() = default;
	Zach zach;
};

MainEntities entities = MainEntities();

MainScene::MainScene(const std::string& name, Camera* mainCamera, Renderer* renderer) 
	: Scene(name, mainCamera, renderer){}

void MainScene::Start() {
	ResourceManager::LoadTexture("res/textures/Zach.png", "zach");
	Zach z = Zach(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, ResourceManager::GetTexture("zach"));
	entities.zach = z;
}

void MainScene::Update(float dt) {
	//UPDATE
	entities.zach.Update(dt);

	// RENDER
	renderer->Start();
	entities.zach.Render(renderer);
	renderer->End();
}