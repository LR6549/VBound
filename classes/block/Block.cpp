//
// Created by lenny on 21.01.2026.
//

#include "Block.h++"

VBND::Block::Block(uint8_t id, uint8_t hitpoints) : b_id(id), b_hitpoints(hitpoints) {}

[[nodiscard]] uint8_t VBND::Block::getID() const {
    return b_id;
}

[[nodiscard]] uint8_t VBND::Block::getHitpoints() const {
    return b_hitpoints;
}

void VBND::Block::setId(uint8_t id){}

void VBND::Block::setHitpoints(uint8_t hitpoints){}

VBND::Block::~Block() = default;