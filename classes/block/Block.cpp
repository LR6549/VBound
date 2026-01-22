//
// Created by lenny on 21.01.2026.
//

#include "Block.h++"

VBND::Block::Block(uint8_t id, uint8_t hitpoints, bool isSlabHorizontal, bool isSlabVertical) : b_id(id), b_hitpoints(hitpoints), b_isSlabHorizontal(isSlabHorizontal), b_isSlabVertical(isSlabVertical) {}

[[nodiscard]] uint8_t VBND::Block::id1() const {
    return b_id;
}

[[nodiscard]] uint8_t VBND::Block::hitpoints1() const {
    return b_hitpoints;
}

[[nodiscard]] bool VBND::Block::isSlabHorizontal() const {
    return b_isSlabHorizontal;
}

[[nodiscard]] bool VBND::Block::isSlabVertical() const {
    return b_isSlabVertical;
}

void VBND::Block::setId(uint8_t id){}

void VBND::Block::setHitpoints(uint8_t hitpoints){}

void VBND::Block::setIsSlabHorizontal(bool is_slab_horizontal){}

void VBND::Block::setIsSlabVertical(bool is_slab_vertical){}

VBND::Block::~Block() = default;