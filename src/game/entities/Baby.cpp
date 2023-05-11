#include "Baby.h"

Baby::Baby(float xPos, float yPos, float xScale, float yScale, float rotation, const std::string name, int layer)
	: Entity(xPos, yPos, xScale, yScale, rotation, name, layer) {
	texture = ResourceManager::GetTexture("baby");
}


void Baby::Render(Renderer* renderer) {
	renderer->DrawQuad(texture, transform.GetModelMatrix());
}

void Baby::Update(float dt) {

}