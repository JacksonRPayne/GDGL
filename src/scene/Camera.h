#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "graphics/Transform.h"
// Defines the scale of the world coordinates (y positions = -WORLD_SCALE to WORLD_SCALE)
#define WORLD_SCALE 1.0f

class Camera
{
public:
	// Takes in window width and height
	Camera(int width, int height);
	// for now return identity
	glm::mat4 GetViewMatrix() { return transform.GetViewMatrix(); }
	// hard coded for now
	glm::mat4 GetProjectionMatrix() { return projectionMatrix; }
	// Adjusts projection matrix when window is resized
	void OnResize(int width, int height);
	void AdjustProjection(float aspectRatio);

	float left;
	float right;
	float bottom;
	float top;

	Transform transform;
	glm::mat4 projectionMatrix;

};

