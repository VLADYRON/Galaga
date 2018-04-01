//
// Created by matt on 3/31/18.
//

#include "TextureManager.h"

TextureManager &TextureManager::instance()
{
    static TextureManager manager;
    return manager;
}

bool TextureManager::addTexture(std::string pathName, pure::Texture *texture)
{
    auto itr = m_textures.emplace(pathName, texture);

    return itr.second;
}

pure::Texture *TextureManager::getTexture(std::string pathName)
{
    auto itr = m_textures.find(pathName);
    if (itr == m_textures.end()) return nullptr;
    return itr->second;
}
