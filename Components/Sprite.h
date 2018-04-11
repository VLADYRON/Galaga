//
// Created by matt on 3/30/18.
//

#ifndef GALAGA_SPRITE_H
#define GALAGA_SPRITE_H

#include <glm/vec2.hpp>
#include <optional>
#include <SDL2/SDL_rect.h>
#include <Pure2D/Renderables/Renderable.h>
#include <SDL2/SDL_system.h>
#include "Transform.h"

namespace pure
{
    class Texture;
}

struct Sprite
{
    pure::Texture* texture;
    std::optional<SDL_Rect> textureRect;
    glm::vec2 size;

    explicit Sprite(
        pure::Texture* texture = nullptr,
        std::optional<SDL_Rect> textureRect = std::nullopt,
        glm::vec2 size = glm::vec2(0)
    );

    void draw(SDL_Renderer* renderer, const Transform& transform, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

};

#endif //GALAGA_SPRITE_H
