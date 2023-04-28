#pragma once
#include <vector>
#include "scene/Scene.h"
#include "system/ResourceManager.h"
#include "scene/Entities/Zach.h"
#include "system/Window.h"

class MainScene : public Scene
{
public:
	MainScene(const std::string& name, Camera* mainCamera, Renderer* renderer);
	void Start() override;
	void Update(float dt) override;
};

