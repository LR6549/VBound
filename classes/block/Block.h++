//
// Created by lenny on 21.01.2026.
//

#ifndef VBOUND_BLOCK_H
#define VBOUND_BLOCK_H

#include <cstdint>
#include <string>

enum Class {

};

namespace VBND {
    class Block {
    private:
        uint8_t b_id;
        uint8_t b_hitpoints;

    public:
        Block(uint8_t id, uint8_t hitpoints);

        [[nodiscard]] uint8_t getID() const;

        [[nodiscard]] uint8_t getHitpoints() const;

        static void setId(uint8_t id);

        static void setHitpoints(uint8_t hitpoints);

        ~Block();
    };
}


#endif //VBOUND_BLOCK_H