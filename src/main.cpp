#include "Game.h"

// TODO:
// =================FIX FRAMERATE CALCULATION=================
// 
// Entitity system
// -- NO ECS
// -- One last idea thats not heap allocating each entity:
// ---- Move polymorphism to scene: scene has virtual Start and Update
// ---- and each scene is constructed in a seperate struct. Each entity is
// ---- hard coded in on the stack and manually call each ones Update in scene update >0o0<
// 
// Scene
// -- Convert to struct of function pointers (or anything light weight and functional)
// 
// All
// -- evaluate map data structures (make sure they're blazingly fast)
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