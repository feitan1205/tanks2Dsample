#pragma once

#include "Vec2.h"

class Player
{
public:

	Player();
	~Player();

	void Update();
	void UpdateCancel();
	void Draw();

	const Vec2 GetPos()const { return _pos; }
	const int GetCircleScale()const { return _hitCircleScale; }

private:

	Vec2 _pos;
	Vec2 _tempPos;
	Vec2 _vec;
	int _hitCircleScale;

};

