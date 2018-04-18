//
// Created by matt on 3/30/18.
//
#include "Sprite.h"

#include <utility>
#include <Pure2D/Util/Convert.h>
#include <Pure2D/Renderables/Texture.h>
#include <SDL2/SDL.h>


Sprite::Sprite(
    pure::Texture *texture,
    std::optional<SDL_Rect> textureRect,
    glm::vec2 size
):
    texture(texture),
    textureRect(std::move(textureRect)),
    size(size) { }


void Sprite::draw(SDL_Renderer *renderer, const Transform &transform, SDL_RendererFlip flip) const
{
    assert(textureRect != std::nullopt);
    assert(texture != nullptr);

    const SDL_Point pos = pure::vecToPoint(transform.position);
    const SDL_Point drawSize = pure::vecToPoint(size);

    SDL_Rect drawRect = { pos.x, pos.y, drawSize.x, drawSize.y };
    SDL_Point rotPoint = pure::vecToPoint(transform.origin);

    SDL_RenderCopyEx(
        renderer,
        texture->getHandle(),
        &*textureRect,
        &drawRect,
        transform.rotation,
        &rotPoint,
        flip
    );
}
