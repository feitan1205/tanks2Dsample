#include "AllCollision.h"

namespace AllCollision{

	/// <summary>
	/// �{�b�N�X�ƃT�[�N���̓����蔻��
	/// </summary>
	/// <param name="minHitBox">�{�b�N�X�̍ŏ����W</param>
	/// <param name="maxHitBox">�{�b�N�X�̍ő���W</param>
	/// <param name="pos">�T�[�N���̒��S���W</param>
	/// <param name="circleScale">�T�[�N���̔��a</param>
	/// <returns>�������Ă��邩</returns>
    bool CollCheck_Box_Circle(Vec2 minHitBox, Vec2 maxHitBox, Vec2 pos, int circleScale)
    {
		     
		if (minHitBox.y > pos.y + circleScale)	return false;
		if (minHitBox.x > pos.x + circleScale)	return false;
		if (maxHitBox.y < pos.y - circleScale)	return false;
		if (maxHitBox.x < pos.x - circleScale)	return false;
		return true;
    }

}

