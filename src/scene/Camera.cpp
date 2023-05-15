#include "Camera.h"

Camera::Camera(int width, int height) : transform(Transform()), bottom(WORLD_SCALE), top(-WORLD_SCALE){
	OnResize(width, height);
}
void Camera::OnResize(int width, int height) {
	// Adjusts to fit new aspect ratio
	AdjustProjection((float)width / (float)height);
}

void Camera::AdjustProjection(float aspectRatio) {
	left = -aspectRatio * WORLD_SCALE;
	right = aspectRatio * WORLD_SCALE;
	projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}