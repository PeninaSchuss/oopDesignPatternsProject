#include "Animation.h"
//������� ������� �� ����� ��������
//------------------------------------------
void Animation::handleAnimation()
{
	m_display.update(m_pos.x, m_spriteSize);
	m_pos.x += m_spriteSize;
	if (m_pos.x == m_sizeOfSpriteSheet)
		m_pos.x =ZERO;
}