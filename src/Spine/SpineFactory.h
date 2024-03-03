#pragma once

#include <string>
#include "spine-sfml/spine-sfml.h"
#include "SpineResData.h"

class SpineFactory
{
public:
    SpineFactory() = delete;

public:
    static auto GetSpine(const std::string& jsonPath, const std::string& atlasPath) -> SpineResData;


private:
    struct SpineResData
    {
        // texture loader -> hold the real data of PNG file.
        uptr<spine::SFMLTextureLoader> pTextureLoader = nullptr;

        // atlas -> hold the reference of real PNG file, and all slices of PNG.
        uptr<spine::Atlas> pAtlasData = nullptr;

        // skeleton -> hold the real data of skeleton data & animation data.
        uptr<spine::Skeleton> pSkeletonData = nullptr;
    };

public:
    
};