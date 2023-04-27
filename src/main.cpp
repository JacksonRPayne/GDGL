#include "Game.h"

// TODO:
// =================FIX FRAMERATE CALCULATION=================
// 
// Entitity system
// -- Optimize (cpu cache)
// -- LAST DITCH NO ECS:
// ---- https://stackoverflow.com/questions/5261027/how-to-write-cache-friendly-polymorphic-code-in-c
// ---- https://gamedev.stackexchange.com/questions/138865/polymorphism-vs-cache-friendliness
// ---- Look up "compile time polymorphism"
// 
// -- FINAL OPTIONS are (best -> worst):
// -- (1) Just make a simple ecs --> vectors of each component type in array, each component has id to index in
// ------ Addcomponent functions, Entity stores an id to index into entity class
// ------ General structure would b many vectors/arrays and an "object" would be an id indexing into them
// ------ Data as array of structures not structure of arrays
// -- (2) Store parallel value type vectors for each entity type in an array, each entity type stores an index into that as it's ID
// ------ Entity vector would store pointers to entries in parallel vectors
// ------ Issue is there are going to be a lot of parallel vectors so memory will be jumping around anyway
// -- (3) Heap allocate a large chunk for Entities at the beginning (sorta like batch rendering vertex buffer) to keep contiguosity (<-- is that a word?)
// ------ Challenge: how do you keep track of memory which will be filled with different size objects? will be a headache and harder than ecs
// -- (4) Say @#$% it and heap allocate entities(who needs performance)
// ------ I can spawn a jillion zach entities and it runs ok so \_(O n O)_/
// 
// ---- ECS idea:
// -------- In order to not have to define entities over and over if used in multiple scenes, create functions
// -------- that take in an entity pointer and construct that entity. EX: void CreateZach(Entity* e){// Set up components}
// 
// Scene
// -- Deallocate entities
// -- (later) maybe add scene loader/unloader function pointers
// 
// All
// -- evaluate map data structures (make sure they're blazingly fast)
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


int main(void)
{
	Game game("Zach!");
	return game.Run();
}