#pragma once

#include "Vec2.h"

enum class CollNumber {
	bottom,
	top,
	right,
	left,
	none
};

namespace AllCollision
{

	bool CollCheck_Box_Circle(Vec2 minHitBox, Vec2 maxHitBox, Vec2 pos, int circleScale);

};

