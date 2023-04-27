#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "system/Window.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "system/InputManager.h"
#include "system/ResourceManager.h"
#include "scene/Camera.h"
#include "graphics/SpriteRenderer.h"
#include "graphics/Transform.h"
#include "scene/Entity.h"
#include "system/Log.h"
#include "scene/SceneManager.h"
#include "scene/Scene.h"
#include "graphics/BatchRenderer.h"
#include "scene/Entities/Zach.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Game
{
public:
	Game(const std::string &name);
	int Run();
	int TEST_RUN();

private:
	std::string name;

};

