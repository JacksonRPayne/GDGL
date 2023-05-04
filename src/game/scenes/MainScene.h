#pragma once
#include <vector>
#include "scene/Scene.h"
#include "system/ResourceManager.h"
#include "game/entities/Zach.h"
#include "system/Window.h"

class MainScene : public Scene
{
public:
	MainScene(const std::string& name, Camera* mainCamera, Renderer* renderer);
	void Load() override;
	void Start() override;
	void Update(float dt) override;
	void End() override;
	void Unload() override;
};

