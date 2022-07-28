#include "TerritoryEater.h"
#include "Board.h"
//-------------------------------------------------------
//������� ������� �� ����� ����� �����
//-------------------------------------------------------
void TerritoryEater::move(Board& b)
{
	sf::Vector2f pos;
	if (m_move != nullptr)
	{
		pos = m_move->move(b);
		m_display.setPosition(pos);
		b.eatCellInMatrix((pos.y-BEGGINING_OF_BOARD_Y)/ BOARD_GAME_CELL_SIZE,(pos.x-BEGGINING_OF_BOARD_X)/BOARD_GAME_CELL_SIZE);
	}
}

