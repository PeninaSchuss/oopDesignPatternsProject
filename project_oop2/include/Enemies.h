#pragma once
#include "DynamicObj.h"
#include "Move.h"
class Level;
//--------------------------------------------
class Enemies:public DynamicObj {
public:
	Enemies() = default;
	Enemies(sf::Texture& t, std::shared_ptr<Move> m, Level* l);
	 ~Enemies() {}
	virtual void move(Board& b)override;
	sf::Vector2i getIndex()const {return m_prevMove->getIndex();}
	void reduceLife();
	void freeze() { m_move = NULL; }
	void unFreeze() { m_move = m_prevMove; }
	void playAnimation(); 
	void deleted() { m_isDeleted = true; }
	bool isDead()const { return m_isDeleted; }
	void updateFailure(bool b); 
protected:	
	std::shared_ptr<Move> m_move;
	std::shared_ptr<Move> m_prevMove;
	Level* m_level;
	bool m_isDeleted=false;
};

