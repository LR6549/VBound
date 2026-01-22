//
// Created by lenny on 21.01.2026.
//

#ifndef VBOUND_BLOCK_H
#define VBOUND_BLOCK_H

#include <cstdint>


namespace VBND {
    class Block {
    private:
        uint8_t b_id;
        uint8_t b_hitpoints;
        bool b_isSlabHorizontal = false;
        bool b_isSlabVertical = false;

    public:
        Block(uint8_t id, uint8_t hitpoints, bool isSlabHorizontal, bool isSlabVertical);

        [[nodiscard]] uint8_t id1() const;

        [[nodiscard]] uint8_t hitpoints1() const;

        [[nodiscard]] bool isSlabHorizontal() const;

        [[nodiscard]] bool isSlabVertical() const;

        static void setId(uint8_t id);

        static void setHitpoints(uint8_t hitpoints);

        static void setIsSlabHorizontal(bool value);

        static void setIsSlabVertical(bool value);

        ~Block();
    };
}


#endif //VBOUND_BLOCK_H