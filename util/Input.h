#pragma once

enum class InputType {
	next,//次へ行くボタン
	right,//右
	left,//左
	up,//上
	down,//下
	shot
};

// テトリス専用パッド処理
namespace Input
{
	// パッドの入力状態取得
	void update();
	// 押し下げ判定
	bool isPress(InputType type);
	// トリガー判定
	bool isTrigger(InputType type);
	
}
