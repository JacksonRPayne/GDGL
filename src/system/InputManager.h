#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/glm.hpp>
#include "graphics/Transform.h"

#define NUM_KEYS 1024
#define NUM_MOUSE_BUTTONS 8

#pragma once
class InputManager
{
public:

	static bool keys[NUM_KEYS];
	static bool mouseButtons[NUM_MOUSE_BUTTONS];
	static double mouseX;
	static double mouseY;

	// Simply if a key is pressed
	static bool GetKey(int key);
	// If a key was just pressed (first frame)
	static bool GetKeyDown(int key);
	// If a key was just released
	static bool GetKeyUp(int key);

	// Simply if a mouse button is pressed
	static bool GetMouseButton(int button);
	// If a mouse button was just pressed (first frame)
	static bool GetMouseButtonDown(int button);
	// If a mouse button was just released
	static bool GetMouseButtonUp(int button);

	// Convert pixel coordinates to world coordinates
	static glm::vec2 GetWorldMousePos(int windowWidth, int windowHeight, float camWidth, const Transform& camTransform);
	// Call at the end of a frame
	static void Update();

private:
	static bool lastKeys[NUM_KEYS];
	static bool lastMouseButtons[NUM_MOUSE_BUTTONS];

};