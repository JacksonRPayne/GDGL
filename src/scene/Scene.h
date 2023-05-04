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

	Scene(const std::string &name, Camera* mainCamera, Renderer* renderer);

	// Loads in resources and creates entities
	virtual void Load(){}
	virtual void Start() {}
	virtual void Update(float dt) {}
	virtual void End() {}
	virtual void Unload(){}

	const std::string& GetName() const { return name; } 
	// TODO: delete these OOP scum
	Camera* GetMainCamera() const { return mainCamera; }
	void SetMainCamera(Camera* camera) { mainCamera = camera; }

	// Doesn't have ownership of these
	Camera* mainCamera;
	Renderer* renderer;

	bool loaded;

protected:
	// TODO: Unload and load resources should be in scene manager and just be functions that load all the stuff and construct scene
	// -- There could b map to scene and scene loader/unloader function pointer(s)
	std::string name;
	// TODO: This is not contiguous. What do i do. :,)
		// Thoughts: preallocate some heap memory to insure entities are placed contiguously
		// and store pointer to beginning memory.

	// Keeps track of highest layer sprite
	unsigned int currMaxLayer;


};

