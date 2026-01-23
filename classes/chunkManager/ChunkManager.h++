//
// Created by lenny on 23.01.2026.
//

#ifndef VBOUND_CHUNKMANAGER_H
#define VBOUND_CHUNKMANAGER_H

#include "../block/Block.h++"
#include "../chunk/Chunk.h++"
#include "../mesh/Mesh.h++"
#include "../player/Player.h++"
#include <vector>

namespace VBND {
    class ChunkManager {
    private:
        std::vector<Chunk> chunks = {};
        Player* player = nullptr;
        int seed;

        void generateChunk(Chunk& c);

        void generateMesh(Chunk& c);

    public:
        ChunkManager(Player* pPlayer, int seed);
        ~ChunkManager();

        void updateChunks();

        void renderChunks();
    };
}

#endif //VBOUND_CHUNKMANAGER_H