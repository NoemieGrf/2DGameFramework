#pragma once

#include "Component.h"

class CompCamera : public Component
{
public:
	CompCamera() = default;

public: // override
	CompType GetType() const override;


};