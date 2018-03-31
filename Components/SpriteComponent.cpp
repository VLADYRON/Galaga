//
// Created by matt on 3/30/18.
//
#include "SpriteComponent.h"

#include <utility>


SpriteComponent::SpriteComponent(
    pure::Texture *texture,
    std::optional<SDL_Rect> textureRect,
    glm::vec2 size
):
    texture(texture),
    textureRect(std::move(textureRect)),
    size(size) { }
