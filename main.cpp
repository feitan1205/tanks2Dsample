#include <DxLib.h>

#include "DxLib.h"
#include "game.h"
#include "Input.h"
#include <vector>
#include <memory>
#include "AllCollision.h"

#include "Player.h"
#include "Field.h"
#include "Shot.h"

namespace {
	constexpr int maxShotNum = 6;
}


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	Player player;
	Field field;
	Vec2 fieldSize = field.GetFieldSize();
	int mousePosX;
	int mousePosY;

	std::vector<std::shared_ptr<Shot>> shots;


	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		Input::update();

		if (Input::isTrigger(InputType::shot)) {
			GetMousePoint(&mousePosX, &mousePosY);
			shots.push_back(std::make_shared<Shot>());
			shots.back()->Start(player.GetPos(), Vec2(static_cast<float>(mousePosX), static_cast<float>(mousePosY)));
			shots.back()->SetFieldData(&field);
		}

		player.Update();
		field.Update();
		for (auto shot : shots) {
			shot->Update();
		}

		for (int i = 0; i < fieldSize.y; i++) {
			for (int j = 0; j < fieldSize.x; j++) {
				if (field.GetFieldData(i, j)) {
					if (AllCollision::CollCheck_Box_Circle(
								field.GetMinHitBox(i, j),
								field.GetMaxHitBox(i, j),
								player.GetPos(),
								player.GetCircleScale())) 
					{
						player.UpdateCancel();
					}
				}
			}
		}

		player.Draw();
		field.Draw();
		for (auto shot : shots) {
			shot->Draw();
		}

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}