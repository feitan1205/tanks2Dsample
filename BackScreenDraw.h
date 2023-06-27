#pragma once

class Vec2;
class Player;

class BackScreenDraw
{
public:

	BackScreenDraw();
	~BackScreenDraw();

	void Updata();
	void Draw();

	void SetMousePos(int posX, int posY);
	void SetPlayerData(Player* player) { _player = player; }

private:

	Vec2 _mousePos;
	Vec2 _reticleStart;
	Vec2 _reticleEnd;

	Player* _player;

};

