#include "Player.h"
//------------------------------------------------------------
Player::Player(sf::Texture& t, sf::Vector2f f, int x, int y, int dx, int dy)
	: Object(t, f), m_x(x), m_y(y), m_dx(dx), m_dy(dy)
{
	m_display.setOrigin(PLAYER_SPRITE_SIZE.x/2, PLAYER_SPRITE_SIZE.y);  //to be changed
}
//������� ������� �� ����� �����
//--------------------------------------------------------------
void Player::move()
{
	m_x += m_dx;
	m_y += m_dy;
	if (m_x < 0) m_x = 0; if (m_x > 44) m_x = 44;
	if (m_y < 0) m_y = 0; if (m_y > 44) m_y = 44;
	setPosition(sf::Vector2f(350 + (m_x * 20), 50 + (m_y * 20)));
}
//������� ������� ��� ����� ���� ����� ������ �����
//--------------------------------------------------------------
bool Player::isRight(int x_pos)const
{
	return (m_x > ((x_pos - 350) / 20));
}
//������� ������� ��� ����� ���� ����� ������ �����
//--------------------------------------------------------------
bool Player::isLeft(int x_pos)const
{
	return (m_x < ((x_pos - 350) / 20));
}
//������� ������� ��� ����� ���� ��� ������ �����
//--------------------------------------------------------------
bool Player::isUp(int y_pos)const
{
	return (m_y < ((y_pos - 50) / 20));
}
//������� ������� ��� ����� ���� ���� ������ �����
//--------------------------------------------------------------
bool Player::isDown(int y_pos)const
{
	return (m_y > ((y_pos - 50) / 20));
}
