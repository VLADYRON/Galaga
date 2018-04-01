//
// Created by matt on 3/31/18.
//

#ifndef GALAGA_TEXTUREMANAGER_H
#define GALAGA_TEXTUREMANAGER_H

#include <Pure2D/Util/NonCopyable.h>
#include <unordered_map>
#include <string>

namespace pure
{
    class Texture;
}

// TODO: Maybe refactor this into a generic asset manager class
class TextureManager final : private pure::NonCopyable
{
public:
    ~TextureManager() final = default;

    bool addTexture(std::string pathName, pure::Texture* texture);
    pure::Texture* getTexture(std::string pathName);

    static TextureManager& instance();

private:
    TextureManager() = default;
    std::unordered_map<std::string, pure::Texture*> m_textures;
};


#endif //GALAGA_TEXTUREMANAGER_H
