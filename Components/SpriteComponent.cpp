//
// Created by matt on 3/30/18.
//
#include "SpriteComponent.h"

#include <utility>
#include <Pure2D/Util/Convert.h>
#include <Pure2D/Renderables/Texture.h>
#include <SDL2/SDL.h>


SpriteComponent::SpriteComponent(
    pure::Texture *texture,
    std::optional<SDL_Rect> textureRect,
    glm::vec2 size
):
    texture(texture),
    textureRect(std::move(textureRect)),
    size(size) { }


void SpriteComponent::draw(SDL_Renderer *renderer, const TransformComponent &transform, SDL_RendererFlip flip) const
{
    assert(textureRect != std::nullopt);
    assert(texture != nullptr);

    SDL_Rect drawRect = { (int)transform.position.x, (int)transform.position.y, (int)size.x, (int)size.y };
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
