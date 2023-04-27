#pragma once
#include <map>
#include <string>
#include <sstream>
#include "Camera.h"
#include "Scene.h"

class SceneManager
{
public:

	static Scene* GetCurrentScene() { return currentScene; }
	// Scenes keep state between switches (maybe create scene reset method?)
	static void SetCurrentScene(const std::string &sceneName);
	static void AddScene(Scene* scene);

	static void Update(float dt);
	static void Render();

	// TODO: think about scene loading, should Scenes not be pointers?
	// -- SceneManager::CreateScene() -> create stack obj and copy into map
	// -- SceneManager::scenes["main"].addEntity(yadayada)
	// -- doing it this way prevents copying gigantic scene objects (esp if entities become stack allocated later)
	// -- make sure map accesses are optimized
	static std::map<std::string, Scene*> scenes;
private:

	static Scene* currentScene;
};

