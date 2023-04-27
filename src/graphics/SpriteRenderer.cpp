#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(Camera* camera, Shader* shader) : camera(camera), shader(shader) {
    // Quad vertices
    float vertices[] = {
        // pos       tex
       -0.5f, 0.5f,  0.0f,1.0f,
        0.5f,-0.5f,  1.0f,0.0f,
       -0.5f,-0.5f,  0.0f,0.0f,

       -0.5f, 0.5f,  0.0f, 1.0f,
        0.5f, 0.5f,  1.0f, 1.0f,
        0.5f,-0.5f,  1.0f, 0.0f
    };
    
    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    
    // Load vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Point to vertex attributes
    // Note: no need for multiple attributes because we can fit pos and tex into xyzw and swizzle
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void SpriteRenderer::DrawQuad(Texture* texture, const glm::mat4& modelMatrix) {
    // Activate shader and texture
    shader->Use();
    texture->Bind();
    // Set uniforms (MVP)
    shader->SetMat4("model", modelMatrix);
    shader->SetMat4("view", camera->GetViewMatrix());
    shader->SetMat4("projection", camera->GetProjectionMatrix());
    // Draw call (not super necessary to rebind VAO)
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}