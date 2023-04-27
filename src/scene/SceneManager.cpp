#include "SceneManager.h"


std::map<std::string, Scene*> SceneManager::scenes;
Scene* SceneManager::currentScene = nullptr;

void SceneManager::Update(float dt) {
	currentScene->Update(dt);
}

void SceneManager::Render() {
	currentScene->Render();
}

void SceneManager::AddScene(Scene* scene) {
	scenes[scene->GetName()] = scene;
	if (currentScene == nullptr) {
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
	currentScene = scenes[sceneName]; // Actual scene change
	currentScene->GetMainCamera()->AdjustProjection(aspectRatio);
}