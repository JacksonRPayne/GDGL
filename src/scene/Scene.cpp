#include "Scene.h"


Scene::Scene(std::string name, Camera* mainCamera, Renderer* renderer) : 
	name(name), renderer(renderer), entities(std::vector<Entity*>()), mainCamera(mainCamera){
	Initialize();
}

Scene::Scene(std::string name, Camera* mainCamera, Renderer* renderer, std::vector<Entity*> entities) :
	name(name), renderer(renderer), entities(entities), mainCamera(mainCamera){
	Initialize();
}

void Scene::Initialize() {
	// Initializes rendering layers
	for (int i = 0; i < MAX_LAYERS; i++) {
		renderingLayers[i] = std::vector<Entity*>();
	}
}

void Scene::AddEntity(Entity* entity) { 
	unsigned int layer = entity->GetRenderingLayer();
	// Increases max layer if need be
	if (layer > currMaxLayer) {
		currMaxLayer = layer;
	}
	// Adds entity to render and update vectors
	entities.push_back(entity);
	renderingLayers[layer].push_back(entity);
}

void Scene::Update(float dt) {
	// Updates each entity
	for(Entity* e: entities)
	{
		e->Update(dt);
	}
}

void Scene::Render() {
	renderer->Start();
	// Only loops through layers it has to
	for (unsigned int i = 0; i <= currMaxLayer; i++) {
		for (Entity* e : renderingLayers[i]) {
			e->Render(renderer);
		}

	}
	renderer->End();
}