#include "Scene.h"

Scene::Scene(const std::string& name, Camera* mainCamera, Renderer* renderer) :
	name(name), renderer(renderer), mainCamera(mainCamera), currMaxLayer(0){
}

