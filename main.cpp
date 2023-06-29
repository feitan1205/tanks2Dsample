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


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
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
		// 画面のクリア
		ClearDrawScreen();

		//入力情報のアップデート
		Input::update();

		//ショット発射
		if (shots.size() < maxShotNum) {
			if (Input::isTrigger(InputType::shot)) {
				GetMousePoint(&mousePosX, &mousePosY);
				shots.push_back(std::make_shared<Shot>());
				shots.back()->Start(player.GetPos(), Vec2(static_cast<float>(mousePosX), static_cast<float>(mousePosY)));
				shots.back()->SetFieldData(&field);
			}
		}

		//プレイヤーアップデート
		player.Update();
		//フィールドアップデート
		field.Update();
		//ショットアップデート
		for (auto shot : shots) {
			shot->Update();
		}

		//プレイヤーと壁の当たり判定
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

		//ショット同士の当たり判定
		for(int i = 0;i < shots.size(); i++) {
			for (int j = 0; j < shots.size(); j++) {
				if (i == j)continue;
				if (AllCollision::CollCheck_Circle_Circle(
					shots[i]->GetPos(),
					shots[i]->GetCircleScale(),
					shots[j]->GetPos(),
					shots[j]->GetCircleScale())) {
					shots[i]->ShotKill();
					shots[j]->ShotKill();
				}
			}
		}

		for (int i = 0; i < shots.size(); i++) {

			if (AllCollision::CollCheck_Circle_Circle(
				shots[i]->GetPos(),
				shots[i]->GetCircleScale(),
				player.GetPos(),
				player.GetCircleScale())) {
				//printfDx("dasdfasadf");
			}

		}

		//ショット削除
		auto rmIt = std::remove_if        // 条件に合致したものを消す
		(shots.begin(),			// 対象はenemies_の最初から
			shots.end(),			// 最後まで
		   // 消えてもらう条件を表すラムダ式
		   // trueだと消える。falseだと消えない
			[](const std::shared_ptr<Shot>& shot)
			{
				return !shot->IsEnabled();
			});
		shots.erase(rmIt, shots.end());

		//プレイヤー描画
		player.Draw();
		//フィールド描画
		field.Draw();
		//ショット描画
		for (auto shot : shots) {
			shot->Draw();
		}

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}