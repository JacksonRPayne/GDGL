# GDGL

A 2D game library built with C++ using OpenGL for hardware accelerated rendering. All features were built from scratch, using the help of GLFW, GLAD, GLM, and stb_image.

# Features:
## Batch Rendering

In order to efficiently render many quads, all vertices in the scene are batched together, and the entire scene is (ideally) drawn in
one draw call.

## Animation System

Simple system for creating and playing animations stored in a sprite sheet.

## Physics

Simple physics and collision detection added. Coming soon is quadtree/grid collision detection.
