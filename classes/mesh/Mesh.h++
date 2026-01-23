//
// Created by lenny on 22.01.2026.
//

#ifndef VBOUND_MESH_H
#define VBOUND_MESH_H

#include <vector>
#include <glad/glad.h>

namespace VBND {
    struct Vertex {
        float px, py, pz;
        float nx, ny, nz;
        float u, v;
        float texId;
    };

    class Mesh {
    public:
        Mesh();
        ~Mesh();

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint ebo = 0;

        bool uploaded = false;

        // Upload mesh to GPU
        void upload();

        // Draw mesh
        void draw() const;

        // Free GPU memory
        void destroy();

        // Clear CPU data (optional, after upload)
        void clearCPU();

        inline bool empty() const {
            return indices.empty();
        }
    };
}

#endif // VBOUND_MESH_H
