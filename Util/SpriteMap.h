//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_SPRITEMAP_H
#define GALAGA_SPRITEMAP_H

#include <SDL2/SDL_rect.h>

namespace spritemap
{
    constexpr int SIZE = 18;

    constexpr SDL_Rect SHIP_WHITE =  { SIZE * 6, SIZE * 0, SIZE, SIZE };
    constexpr SDL_Rect SHIP_RED = { SIZE * 6, SIZE * 1, SIZE, SIZE };

    constexpr SDL_Rect CATCHER_TURQUOISE_OPEN = { SIZE * 6, SIZE * 2, SIZE, SIZE };
    constexpr SDL_Rect CATCHER_TURQUOISE_CLOSED = { SIZE * 7, SIZE * 2, SIZE, SIZE };

    constexpr SDL_Rect CATCHER_PURPLE_OPEN = { SIZE * 6, SIZE * 3, SIZE, SIZE };
    constexpr SDL_Rect CATCHER_PURPLE_CLOSED = { SIZE * 7, SIZE * 3, SIZE, SIZE };

    constexpr SDL_Rect MOTH_OPEN = { SIZE * 6, SIZE * 4, SIZE, SIZE };
    constexpr SDL_Rect MOTH_CLOSED = { SIZE * 7, SIZE * 4, SIZE, SIZE };

    constexpr SDL_Rect BEE_OPEN = { SIZE * 6, SIZE * 5, SIZE, SIZE };
    constexpr SDL_Rect BEE_CLOSED = { SIZE * 7, SIZE * 5, SIZE, SIZE };

    constexpr SDL_Rect PLAYER_EXPLOSION_BEGIN = { 0, SIZE * 6, 34, 34 };
    constexpr SDL_Rect PLAYER_EXPLOSION_END = { 34 * 3, SIZE * 6, 34, 34 };

    constexpr SDL_Rect PLAYER_MISSLE = { 0, SIZE * 8, SIZE, SIZE };
    constexpr SDL_Rect ENEMY_MISSLE = { SIZE * 5, SIZE * 8, SIZE, SIZE };

    constexpr SDL_Rect SCORPION = { SIZE * 6, SIZE * 9, SIZE, SIZE };
    constexpr SDL_Rect BEE_RED_OPEN = { SIZE * 6, SIZE * 10, SIZE, SIZE };
    constexpr SDL_Rect BEE_RED_CLOSED = { SIZE * 7, SIZE * 10, SIZE, SIZE };
    constexpr SDL_Rect STINGRAY = { SIZE * 6, SIZE * 11, SIZE, SIZE };
    constexpr SDL_Rect MOTHERSHIP = { SIZE * 6, SIZE * 12, SIZE, SIZE };
    constexpr SDL_Rect DRAGONFLY = { SIZE * 6, SIZE * 13, SIZE, SIZE };
    constexpr SDL_Rect FLAGSHIP = { SIZE * 6, SIZE * 15, SIZE, SIZE };

}

#endif //GALAGA_SPRITEMAP_H
