//
// Created by lenny on 22.01.2026.
//

#ifndef VBOUND_PLAYER_H
#define VBOUND_PLAYER_H

#include <vector>

namespace VBND {
    class player {
    private:
        std::vector<float> position;

    public:
        player();
        ~player();
    };
}

#endif //VBOUND_PLAYER_H