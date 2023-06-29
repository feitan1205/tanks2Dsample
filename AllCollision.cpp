#include "AllCollision.h"
#include <cmath>

namespace AllCollision{

	/// <summary>
	/// ボックスとサークルの当たり判定
	/// </summary>
	/// <param name="minHitBox">ボックスの最小座標</param>
	/// <param name="maxHitBox">ボックスの最大座標</param>
	/// <param name="pos">サークルの中心座標</param>
	/// <param name="circleScale">サークルの半径</param>
	/// <returns>当たっているか</returns>
    bool CollCheck_Box_Circle(Vec2 minHitBox, Vec2 maxHitBox, Vec2 pos, int circleScale)
    {
		     
		if (minHitBox.y > pos.y + circleScale)	return false;
		if (minHitBox.x > pos.x + circleScale)	return false;
		if (maxHitBox.y < pos.y - circleScale)	return false;
		if (maxHitBox.x < pos.x - circleScale)	return false;
		return true;
    }

	bool CollCheck_Circle_Circle(Vec2 pos1, int circleScale1, Vec2 pos2, int circleScale2)
	{
		int hitDistance = circleScale1 + circleScale2;

		int distance;

		distance = std::abs(sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));

		if (hitDistance > distance) {
			return true;
		}

		return false;

	}

}

