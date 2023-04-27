#include "Transform.h"
#include <glm/ext/matrix_transform.hpp>


Transform::Transform(): position(glm::vec2(0.0f, 0.0f)), scale(glm::vec2(1.0f,1.0f)), rotation(0), modelMatrix(glm::mat4(1.0f)){}

Transform::Transform(glm::vec2 position, glm::vec2 scale, float rotation) : position(position), scale(scale), rotation(rotation) {
	UpdateModelMatrix();
}

Transform::Transform(float xPos, float yPos, float xScale, float yScale, float rotation) : 
	position(glm::vec2(xPos, yPos)), scale(glm::vec2(xScale, yScale)), rotation(rotation) {

	UpdateModelMatrix();
}

// TODO: do we even need this func with batch rendering?
void Transform::UpdateModelMatrix() {
	// Initializes to identity mat
	modelMatrix = glm::mat4(1.0f);
	// Applies transformations to it
	modelMatrix = glm::translate(modelMatrix, glm::vec3(position, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale, 1.0f));

}
