#include "Shot.h"

#include "DxLib.h"

#include "Field.h"
#include "AllCollision.h"

Shot::Shot():
	_shotScale(shotScale),
	_enableFlg(false),
	_brittleFlg(false)
{
}

Shot::~Shot()
{
}

void Shot::Update()
{
	_tempPos = _pos;

	_pos.x += _vec.x;

	if (HitCheck()) {
		_vec.x *= -1;
		_pos = _tempPos;
		if (_brittleFlg) {
			_enableFlg = false;
		}
		_brittleFlg = true;
	}

	_pos.y += _vec.y;

	if (HitCheck()) {
		_vec.y *= -1;
		_pos = _tempPos;
		if (_brittleFlg) {
			_enableFlg = false;
		}
		_brittleFlg = true;
	}

}

void Shot::Draw()
{
	DrawCircle(_pos.x, _pos.y, _shotScale, 0xffffff, true);
}

void Shot::Start(Vec2 playerPos, Vec2 targetPos)
{
	_enableFlg = true;
	_pos = playerPos;
	_vec = targetPos - playerPos;
	_vec = _vec.normalize();
	_vec *= speed;
}

void Shot::ShotKill()
{
	_enableFlg = false;
}

void Shot::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}

bool Shot::HitCheck()
{
	for (int i = 0; i < _fieldSize.y; i++) {
		for (int j = 0; j < _fieldSize.x; j++) {
			if (_field->GetFieldData(i, j)) {
				if (AllCollision::CollCheck_Box_Circle(
					_field->GetMinHitBox(i, j),
					_field->GetMaxHitBox(i, j),
					this->GetPos(),
					this->GetCircleScale())) {
					return true;
				}
			}
		}
	}
	return false;
}
