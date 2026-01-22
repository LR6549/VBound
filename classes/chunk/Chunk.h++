//
// Created by lenny on 21.01.2026.
//

#ifndef VBOUND_Chunk_H
#define VBOUND_Chunk_H

#include <glad/glad.h>
#include "../block/Block.h++"
#include "../mesh/Mesh.h++"

#ifndef VBOUND_CHUNK_SIZE
#define VBOUND_CHUNK_SIZE 16
#endif

namespace VBND {
    class Chunk {
    private:
        bool isDirty = true;

        int cx, cz;
        Block blocks[VBOUND_CHUNK_SIZE][VBOUND_CHUNK_SIZE][VBOUND_CHUNK_SIZE];
        Mesh mesh;

    public:
        Chunk();
        ~Chunk();
    };
}


#endif //VBOUND_Chunk_H