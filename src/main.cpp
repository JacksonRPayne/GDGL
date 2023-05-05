#include "game/Game.h"

// TODO: 
// Animations:
// -- Move state of animation into animator
// -- Animations should be pointers -- there's no point duplicating them for every object using it
// -- maybe make animdata struct with state data for current animation, and pass that into Animation methods
// 
// Move semantics:
// -- Figure out best way to deal with stack objects, and initializing
// -- values in the entity structs for each scene
// -- The only part of the code that *really* needs to be on the stack for CPU optimization 
// -- are the entities, so don't go crazy with the move semantics.
// -- The system of storing entities in vectors kinda moves most data to the heap anyway, but at this point
// -- it just makes sense to keep it stack allocated, and hope it performs better. If I run into issues with it,
// -- it's probably ok to just heap allocate the entities object, as long as all entities are in one object to be contiguous
// 
// Scene
// -- Convert to struct of function pointers? (or anything light weight and non OOP)
// 
// Collision detection
// -- Hitbox class
// -- That tree data structure (quadtree i believe)
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