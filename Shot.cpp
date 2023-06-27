#include "Shot.h"

#include "DxLib.h"

#include "Field.h"
#include "AllCollision.h"

Shot::Shot():
	_shotScale(shotScale)
{
}

Shot::~Shot()
{
}

void Shot::Update()
{
	_tempPos = _pos;

	_pos.x += _vec.x;

	for (int i = 0; i < _fieldSize.y; i++) {
		for (int j = 0; j < _fieldSize.x; j++) {
			if (_field->GetFieldData(i, j)) {
				if (AllCollision::CollCheck_Box_Circle(
					_field->GetMinHitBox(i, j),
					_field->GetMaxHitBox(i, j),
					this->GetPos(),
					this->GetCircleScale())) {
					_vec.x *= -1;
					_pos = _tempPos;
				}
			}
		}
	}

	_pos.y += _vec.y;

	for (int i = 0; i < _fieldSize.y; i++) {
		for (int j = 0; j < _fieldSize.x; j++) {
			if (_field->GetFieldData(i, j)) {
				if (AllCollision::CollCheck_Box_Circle(
					_field->GetMinHitBox(i, j),
					_field->GetMaxHitBox(i, j),
					this->GetPos(),
					this->GetCircleScale())) {
					_vec.y *= -1;
					_pos = _tempPos;
				}
			}
		}
	}

}

void Shot::Draw()
{
	DrawCircle(_pos.x, _pos.y, _shotScale, 0xffffff, true);
}

void Shot::Start(Vec2 playerPos, Vec2 targetPos)
{
	_pos = playerPos;
	_vec = targetPos - playerPos;
	_vec = _vec.normalize();
	_vec *= speed;
}

void Shot::HitWall()
{

}

void Shot::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}
