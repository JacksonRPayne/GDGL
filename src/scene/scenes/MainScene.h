#pragma once
#include "scene/Scene.h"
#include "system/ResourceManager.h"
#include "scene/Entities/Zach.h"


class MainScene : public Scene
{
public:
	MainScene(const std::string& name, Camera* mainCamera, Renderer* renderer);
	void Start() override;
	void Update(float dt) override;
};

