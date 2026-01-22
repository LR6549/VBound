//
// Created by lenny on 21.01.2026.
//

#include "Chunk.h++"

VBND::Chunk::Chunk(int chunkX, int chunkZ) : cx(chunkX), cz(chunkZ) {

}

bool VBND::Chunk::isAir(int x, int y, int z, Chunk& c) {
    if (x < 0 || y < 0 || z < 0 ||
        x >= VBND_CHUNK_SIZE || y >= VBND_CHUNK_SIZE || z >= VBND_CHUNK_SIZE)
        return true; // outside chunk = air
    return c.blocks[x][y][z].getID() == 0;
}

void VBND::generateChunk(Chunk& c) {

}


VBND::Chunk::~Chunk() = default;