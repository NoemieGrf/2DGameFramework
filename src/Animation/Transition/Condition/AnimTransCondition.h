#pragma once

class Entity;

class AnimTransCondition
{
public:
    virtual ~AnimTransCondition() = default;

public:
    virtual bool Check(Entity* pEntity) = 0;

};