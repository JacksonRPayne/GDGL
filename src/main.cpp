#include "game/Game.h"

// TODO: 
// Move semantics:
// -- Figure out best way to deal with stack objects, and initializing
// -- values in the entity structs for each scene
// 
// Scene
// -- Convert to struct of function pointers? (or anything light weight and non OOP)
// 
// Animation/Animator
// -- Complete refactor, organize and document
// 
// Collision detection
// -- Hitbox class
// -- That tree data structure
// 
// "Physics"
// -- Velocity values for entity
// 
// Audio
// -- Library or from scratch?
// 


// NOTE:
// -- I could make this project like: backbone = OOP, game on top = functional
// -- Backbone is more like an API, but game on top feels like everything should be public/global/functional

int main(void)
{
	Game game("Zach!");
	return game.Run();
}