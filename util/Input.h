#pragma once

enum class InputType {
	next,//���֍s���{�^��
	right,//�E
	left,//��
	up,//��
	down,//��
	shot
};

// �e�g���X��p�p�b�h����
namespace Input
{
	// �p�b�h�̓��͏�Ԏ擾
	void update();
	// ������������
	bool isPress(InputType type);
	// �g���K�[����
	bool isTrigger(InputType type);
	
}
