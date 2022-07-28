#pragma once
#include "CanMoveToPlace.h"
//-----------------------------------------------
class Move{
public:
	Move(sf::Vector2i pos,std::unique_ptr<CanMoveToPlace> placeToMove); 
	virtual ~Move()=0{}
	virtual sf::Vector2f move(Board& b) = 0{}
	sf::Vector2i getIndex()const; 
protected:
	int m_x = MIDDLE_BOARD_X, m_y = MIDDLE_BOARD_Y;
	int m_dx =  SIX - rand() % TWELVE;
	int m_dy =  SIX - rand() % TWELVE;
	std::unique_ptr<CanMoveToPlace> m_placeToMove;
};