//
// Created by lenny on 22.01.2026.
//

#include "Mesh.h++"

#include <cstddef>   // offsetof
#include <iostream>

VBND::Mesh::Mesh() = default;

VBND::Mesh::~Mesh() {
    destroy();
}

void VBND::Mesh::upload() {
    if (uploaded) {
        return;
    }

    if (vertices.empty() || indices.empty()) {
        std::cerr << "Mesh upload failed: empty vertex or index buffer\n";
        return;
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(uint32_t),
        indices.data(),
        GL_STATIC_DRAW
    );

    constexpr GLsizei stride = sizeof(Vertex);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        stride,
        (void*)offsetof(Vertex, px)
    );

    // Normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        stride,
        (void*)offsetof(Vertex, nx)
    );

    // UV
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE,
        stride,
        (void*)offsetof(Vertex, u)
    );

    // Texture ID (layer index)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(
        3, 1, GL_FLOAT, GL_FALSE,
        stride,
        (void*)offsetof(Vertex, texId)
    );

    glBindVertexArray(0);

    uploaded = true;
}

void VBND::Mesh::draw() const {
    if (!uploaded || vao == 0) {
        return;
    }

    glBindVertexArray(vao);
    glDrawElements(
        GL_TRIANGLES,
        static_cast<GLsizei>(indices.size()),
        GL_UNSIGNED_INT,
        nullptr
    );
    glBindVertexArray(0);
}

void VBND::Mesh::destroy() {
    if (ebo) {
        glDeleteBuffers(1, &ebo);
        ebo = 0;
    }
    if (vbo) {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }
    if (vao) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }

    uploaded = false;
}

void VBND::Mesh::clearCPU() {
    vertices.clear();
    indices.clear();
    vertices.shrink_to_fit();
    indices.shrink_to_fit();
}
