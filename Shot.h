#pragma once

#include "Vec2.h"

namespace {
	constexpr int speed = 1;
	constexpr int shotScale = 3;
}

class Field;

class Shot
{
public:

	Shot();
	~Shot();

	void Update();
	void Draw();

	void Start(Vec2 playerPos,Vec2 targetPos);

	void HitWall();

	void SetFieldData(Field* field);
	const Vec2 GetPos()const { return _pos; }
	const int GetCircleScale() const { return _shotScale; }
private:

	Vec2 _pos;
	Vec2 _vec;
	Vec2 _tempPos;

	Field* _field;
	Vec2 _fieldSize;

	int _shotScale;

	bool _enableFlg;
};

