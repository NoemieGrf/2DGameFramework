#pragma once

#include <string>
#include "spine-sfml/spine-sfml.h"
#include "../Game/GlobalDefine.h"

class SpineFactory
{
public:
    SpineFactory() = delete;

public:
    static auto CreateSpineDrawable(const std::string& spineName) -> uptr<spine::SkeletonDrawable>;


private:
    struct SpineResData
    {
        // texture loader -> hold the real data of PNG file.
        uptr<spine::SFMLTextureLoader> pTextureLoader = nullptr;

        // atlas -> hold the reference of real PNG file, and all slices of PNG.
        uptr<spine::Atlas> pAtlasData = nullptr;

        // skeleton -> hold the real data of skeleton data & reference to atlas.
        uptr<spine::SkeletonData> pSkeletonData = nullptr;
    };

public:
    inline static umap<std::string, SpineResData> _spineResourcePool {};
};