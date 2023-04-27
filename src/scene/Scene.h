#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Entity.h"
#include "Camera.h"
#include "graphics/SpriteRenderer.h"

class Scene
{
public:

	Scene(std::string name, Camera* mainCamera, Renderer* renderer);
	Scene(std::string name, Camera* mainCamera, Renderer* renderer, std::vector<Entity*> entities);

	void AddEntity(Entity* entity);
	void SetMainCamera(Camera* camera) { mainCamera = camera; }

	void Update(float dt);

	void Render();

	const std::string& GetName() const { return name; } 
	Camera* GetMainCamera() const { return mainCamera; }

	// TODO: deallocate entities. The issue is if it's in destructor it's gonna make scene construction hard

private:
	// TODO: Unload and load resources should be in scene manager and just be functions that load all the stuff and construct scene
	// -- There could b map to scene and scene loader/unloader function pointer(s)
	void Initialize();

	std::string name;
	// TODO: This is not contiguous. What do i do. :,)
		// Thoughts: preallocate some heap memory to insure entities are placed contiguously
		// and store pointer to beginning memory.
	std::vector<Entity*> entities;
	std::vector<Entity*> renderingLayers[MAX_LAYERS];

	// Keeps track of highest layer sprite
	unsigned int currMaxLayer;

	// Doesn't have ownership of these
	Camera* mainCamera;
	Renderer* renderer;
};

