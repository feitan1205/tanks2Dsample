#include "AllCollision.h"

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

}

