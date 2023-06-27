#include "Player.h"
#include "DxLib.h"
#include "Input.h"

Player::Player():
	_hitCircleScale(15)
{
	_pos = Vec2(32 * 2, 32 * 9);
	_vec = Vec2(0, 0);
}

Player::~Player()
{
}

void Player::Update()
{
	_tempPos = _pos;

	if (Input::isPress(InputType::left))	_vec.x += -1;
	if (Input::isPress(InputType::right))	_vec.x +=  1;
	if (Input::isPress(InputType::up))		_vec.y += -1;
	if (Input::isPress(InputType::down))	_vec.y +=  1;

	_vec = _vec.normalize();

	_pos += _vec;

	_vec = Vec2(0, 0);

}

void Player::UpdateCancel()
{
	_pos = _tempPos;
}

void Player::Draw()
{

	DrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 16, _pos.y + 16, 0x00ff00, true);
	DrawCircle(_pos.x, _pos.y, _hitCircleScale, 0x0000ff, true);
}
