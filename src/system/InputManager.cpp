#include "InputManager.h"

bool InputManager::keys[NUM_KEYS] = { 0 };
bool InputManager::lastKeys[NUM_KEYS] = { 0 };

bool InputManager::mouseButtons[NUM_MOUSE_BUTTONS] = { 0 };
bool InputManager::lastMouseButtons[NUM_MOUSE_BUTTONS] = { 0 };

double InputManager::mouseX = 0;
double InputManager::mouseY = 0;

bool InputManager::GetKey(int key) {
	return keys[key];
}

bool InputManager::GetKeyDown(int key) {
	return keys[key] && !lastKeys[key];
}

bool InputManager::GetKeyUp(int key) {
	return !keys[key] && lastKeys[key];
}

bool InputManager::GetMouseButton(int button) {
	return mouseButtons[button];
}

bool InputManager::GetMouseButtonDown(int button) {
	return mouseButtons[button] && !lastMouseButtons[button];
}

bool InputManager::GetMouseButtonUp(int button){
	return !mouseButtons[button] && lastMouseButtons[button];
}

glm::vec2 InputManager::GetWorldMousePos(int windowWidth, int windowHeight, float camRight, const Transform &camTransform) {
	// TODO: is this a matrix operation? probably
	float xNorm = ((mouseX / windowWidth)*2 - 1.0f)*camTransform.GetScale().x;
	float yNorm = ((mouseY / windowHeight)*2 - 1.0f )* camTransform.GetScale().y;;
	return  glm::vec2(xNorm * camRight + camTransform.GetPosition().x, yNorm + camTransform.GetPosition().y);
}

void InputManager::Update() {
	// TODO: will this be slow?
	std::copy(keys, keys + NUM_KEYS, lastKeys);
	std::copy(mouseButtons, mouseButtons+ NUM_MOUSE_BUTTONS, lastMouseButtons);
}