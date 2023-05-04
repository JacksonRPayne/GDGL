#include "SceneManager.h"


std::unordered_map<std::string, Scene*> SceneManager::scenes;
Scene* SceneManager::currentScene = nullptr;

void SceneManager::Update(float dt) {
	currentScene->Update(dt);
}


void SceneManager::AddScene(Scene* scene) {
	scenes[scene->GetName()] = scene;
	if (currentScene == nullptr) {
		if (!scene->loaded) scene->Load();
		currentScene = scene;
	}
}

void SceneManager::SetCurrentScene(const std::string& sceneName) {
	// Scene doesn't exist in map
	if (!scenes.count(sceneName)) {
		std::stringstream msg;
		msg << "Scene " << sceneName << " not found.";
		Log::LogError(msg.str());
		return;
	}

	// Pass on projection to next camera (in case of window resize between scenes)
	float aspectRatio = currentScene->GetMainCamera()->right / WORLD_SCALE;

	if(currentScene) currentScene->End(); // Ends last scene
	currentScene = scenes[sceneName]; // Actual scene change
	// Loads scene if necessary
	if (!currentScene->loaded) {
		currentScene->Load();
	}
	currentScene->GetMainCamera()->AdjustProjection(aspectRatio);
	currentScene->Start();
}