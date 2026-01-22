//
// Created by lenny on 21.01.2026.
//

#ifndef VBOUND_Chunk_H
#define VBOUND_Chunk_H

#include <glad/glad.h>
#include "../block/Block.h++"
#include "../mesh/Mesh.h++"

#ifndef VBND_CHUNK_SIZE
#define VBND_CHUNK_SIZE 16
#endif

#ifndef VBND_CHUNK_HEIGHT
#define VBND_CHUNK_HEIGHT 16
#endif

namespace VBND {
    class Chunk {
    private:
        bool isDirty = true;

        int cx, cz;
        //++ X (width) | Y (height) | z (length)
        Block blocks[VBND_CHUNK_SIZE][VBND_CHUNK_HEIGHT][VBND_CHUNK_SIZE];
        Mesh mesh;

    public:
        Chunk();
        ~Chunk();

        static bool isAir(int x, int y, int z, Chunk& c);

        void generateChunk(Chunk& c);

        void generateMesh(Chunk& c, Mesh& m);

        int convertWorldToChunk(int x, int z, Chunk& c);

        int convertChunkToWorld(int x, int z, Chunk& c);

        Block* getBlock(int x, int y, int z, Chunk& c);
    };
}


#endif //VBOUND_Chunk_H