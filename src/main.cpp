#include "game/Game.h"

// TODO: 
// 
// Line Rendering
// -- Give the batch renderer line rendering functionality  
// -- for hitbox and quadtree debugging
// -- SHOULD NOT BE BATCHED:
// ---- I don't want to have to heap allocate a line vertex buffer, that's dumb
// ---- render lines sorta how the SpriteRenderer does it
// 
// Collision detection
// -- That tree data structure (quadtree i believe)
// -- Or just grid collision?
// 
// Animations:
// -- Reimplement queueing system
// -- Change function names to be more clear
// 
// Audio
// -- Library or from scratch?
// 


int main(void)
{
	Game game("Zach!");
	return game.Run();
}