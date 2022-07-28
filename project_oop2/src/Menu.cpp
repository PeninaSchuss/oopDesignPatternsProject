#include "StartMenu.h"
#include "NewGameCommand.h"
//-------------------------------------------------------------
//������� ������ �� ���� ����� �� ������
//-------------------------------------------------------------
void  Menu::handleMouseMove(sf::Vector2f move_position)
{
	for (int i = 0; i < m_menu.size(); i++)
	{
		if (m_menu[i].second.getSprite().getGlobalBounds().contains(move_position))
			m_menu[i].second.scale(1.3,1.3);
		else
			m_menu[i].second.scale(1, 1);
	}
}
//=====================================================================
//������� ������ ������� ���� ��� �������
//---------------------------------------
void Menu::handleBoard()
{
	m_View.draw();
	for (int i = 0; i < m_menu.size(); i++)
		m_menu[i].second.draw();
}
//������� ������ �� �� ����� ������� �� ������ ������
//---------------------------------------------------------------------
void Menu::handlePress(sf::Vector2f press_position)
{
	for (int i = 0; i < m_menu.size(); i++)
		if (m_menu[i].second.getSprite().getGlobalBounds().contains(press_position))
		{
			Graphics::getGraphics().getSoundVec()[CLICK_SOUND]->play();
			m_menu[i].first->execute(m_menu[i].second);
		}
}
