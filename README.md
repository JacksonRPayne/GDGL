# Saidar

A 2D "game engine" built with C++ using OpenGL for rendering.

# Features:
## Batch Rendering

In order to efficiently render many quads, all vertices in the scene are batched together, and the entire scene is drawn in
one draw call. 

## Entity Component System

Coming soon. Goal is to store entities in a CPU cache friendly way.
