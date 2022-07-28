#include "Board.h"
#include "CollisionHandling.h"
#include "Level.h"
//-----------------------------------------------
Board::Board(int curentLevel, int& percent)
	: m_player(std::make_unique<Player>(Graphics::getGraphics().getTexture(PLAYER), PLAYER_SPRITE_SIZE)),
	m_backgroundGame(Graphics::getGraphics().getTexture(SKY), {}, { WIDTH_WINDOW, HIGTH_WINDOW }), m_percentage(percent),
	m_crumbPic(Graphics::getGraphics().getTexture(CRUMB_ANIMATION), {}, CRUMS_SPRITE_SHEET_SIZE), m_crumbAnimation(m_crumbPic, CRUMS_SPRITE_SHEET_SIZE.x, CRUMS_SPRITE_SHEET_SIZE.y)
{
	clockForGifts.restart();
	createBoard();
}
//������� ������ �� ���� �� �����
//-----------------------------------------------
void Board::createBoard()
{
	m_matrix.resize(MATRIX_SIZE);
	for (int i = 0; i < MATRIX_SIZE; i++)
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			m_matrix[i].emplace_back(EMPTY);
			if (i == ZERO || j == ZERO || i == MATRIX_SIZE - 1 || j == MATRIX_SIZE - 1)
				m_matrix[i][j] = BLOCKED;
		}
}
//������� ������� ������ ����
//-----------------------------------------------
void Board::draw(std::vector<int> infoVec)
{
	m_backgroundGame.draw();
	drawTiles(infoVec);
	m_player->draw();
	drawObjects();

}
//����� ������
//------------------------------------------------
void Board::drawTiles(std::vector<int> infoVec)const
{
	for (int i = 0; i < MATRIX_SIZE; i++)
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			sf::RectangleShape rect(BOARD_GAME_CELL);
			rect.setPosition(j * BOARD_GAME_CELL_SIZE + BEGGINING_OF_BOARD_X, i * BOARD_GAME_CELL_SIZE + BEGGINING_OF_BOARD_Y);
			if (m_matrix[i][j] == EMPTY)
				rect.setTexture(&(Graphics::getGraphics().getTexture(infoVec[INDEX_OF_EMPTY])));
			if (m_matrix[i][j] == BLOCKED)
				rect.setTexture(&(Graphics::getGraphics().getTexture(infoVec[INDEX_OF_BLOCKED])));
			if (m_matrix[i][j] == MIDDLE)
				rect.setTexture(&(Graphics::getGraphics().getTexture(infoVec[INDEX_OF_MIDDLE])));
			Graphics::getGraphics().getWindow().draw(rect);
		}
}
//����� ������
//------------------------------------------------
void Board::drawObjects()
{
	drawVec(m_ballsVec);
	drawVec(m_spidersVec);
	drawVec(m_territoryEaterVec);
	drawVec(m_giftsVec);
}
//������� ������� �� ����� ������ ���������
//-------------------------------------------------------------
template <typename enemyVec>
void Board::drawVec(std::vector<typename enemyVec>& vec)
{
	for (int i = 0; i < vec.size(); i++)
		vec[i]->draw();
}
//������� ������ ��� ����� ��� ����� ���� ��� ��
//------------------------------------------------
bool Board::checkIfPassedAlready()
{
	if (m_matrix[m_player->getPlayerYpos()][m_player->getPlayerXpos()] == MIDDLE)
	{
		updateFailure(true);
		return true;
	}
	if (m_matrix[m_player->getPlayerYpos()][m_player->getPlayerXpos()] == EMPTY)
		m_matrix[m_player->getPlayerYpos()][m_player->getPlayerXpos()] = MIDDLE;
	return false;
}
//������� ������� �� ����� �������
//-------------------------------------------------
bool Board::moveEnemies()
{
	bool isColideWithMiddleTile = false;
	moveEnemiesVec(m_ballsVec,isColideWithMiddleTile);
	moveEnemiesVec(m_spidersVec, isColideWithMiddleTile);
	moveEnemiesVec(m_territoryEaterVec, isColideWithMiddleTile);
	return isColideWithMiddleTile;
}
//������� ������� �� ����� �� ����� ������
//-------------------------------------------------------------
template <typename enemyVec>
void Board::moveEnemiesVec(std::vector<typename enemyVec>& enemiesVec,bool& isColideWithMiddleTile)
{
	for (auto& enemy : enemiesVec)
	{
		enemy->move(*this);
		if ((typeid(Player) == typeid(*m_player)) && (m_matrix[enemy->getIndex().x][enemy->getIndex().y] == MIDDLE))
		{
			updateFailure(true);
			isColideWithMiddleTile = true;
		}
	}
}
//������� ������� �� ����� �������
//-------------------------------------------------
void Board::handleSpaceBlockage()
{
	if (m_matrix[m_player->getPlayerYpos()][m_player->getPlayerXpos()] == BLOCKED)
	{
		m_player->setPlayerDx(ZERO);
		m_player->setPlayerDy(ZERO);
		floodFill();
		handleConditionTile();
		updateFailure(false);
	}
}
//������� ������� �� ��� �������
//----------------------------------------------------------
void Board::handleConditionTile()
{
	for (int i = 0; i < MATRIX_SIZE; i++)
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			if ((m_matrix[i][j] == MIDDLE && m_inFailure) || m_matrix[i][j] == AROUND_ENEMY)
				m_matrix[i][j] = EMPTY;
			else if ((m_matrix[i][j] == EMPTY || m_matrix[i][j] == MIDDLE) && !m_inFailure)
			{
				if (++m_blockCounter >= AMOUNT_FOR_ONE_PERCENT)
				{
					m_percentage++;
					m_blockCounter = ZERO;
				}
				m_matrix[i][j] = BLOCKED;
			}
		}
}
//�������� ������� ��������� ���� �� ����� ����
//----------------------------------------------------------
void Board::floodFill(sf::Vector2i v)
{
	if (v.x >= ZERO && v.x <= MATRIX_SIZE - 1 && v.y >= ZERO && v.y <= MATRIX_SIZE - 1 && m_matrix[v.x][v.y] == EMPTY) m_matrix[v.x][v.y] = AROUND_ENEMY;
	if (((v.x + TO_LEFT) >= ZERO) && v.y >= 0 && v.y <= MATRIX_SIZE - 1 && m_matrix[v.x + TO_LEFT][v.y] == EMPTY) floodFill(sf::Vector2i(v.x+TO_LEFT, v.y));
	if (((v.x + TO_RIGHT) <= MATRIX_SIZE-1) && v.y >= ZERO && v.y <= MATRIX_SIZE - 1 && m_matrix[v.x + TO_RIGHT][v.y] == EMPTY) floodFill(sf::Vector2i(v.x + TO_RIGHT, v.y));
	if (((v.y + TO_UP) >= ZERO) && v.x >= 0 && v.x <= MATRIX_SIZE - 1 && m_matrix[v.x][v.y + TO_UP] == EMPTY) floodFill(sf::Vector2i(v.x, v.y +TO_UP));
	if (((v.y + TO_DOWN) <= MATRIX_SIZE - 1) && v.x >= ZERO && v.x <= MATRIX_SIZE - 1 && m_matrix[v.x][v.y +TO_DOWN] == EMPTY) floodFill(sf::Vector2i(v.x, v.y + TO_DOWN));
}
//���� �����
//------------------------------------------------------------
void Board::movePlayer()
{
	m_player->move();
}
//������� ������� �� ����� ������ 
//------------------------------------------------------------
void Board::setDirection(sf::Keyboard::Key key)
{
	switch (key){
	case sf::Keyboard::Key::Right:{
		m_player->setPlayerDx(TO_RIGHT); m_player->setPlayerDy(ZERO);break;}
	case sf::Keyboard::Key::Left:{
		m_player->setPlayerDx(TO_LEFT); m_player->setPlayerDy(ZERO);break;}
	case sf::Keyboard::Key::Down:{
		m_player->setPlayerDx(ZERO); m_player->setPlayerDy(TO_DOWN);break;}
	case sf::Keyboard::Key::Up:{
		m_player->setPlayerDx(ZERO); m_player->setPlayerDy(TO_UP);break;}
	default:
		return;
	}
}
//������� ������� �� ����� ������ ����
//--------------------------------------------
void Board::handleCreateGifts(int& gift_num, int rand_time, Level* l)
{
	if (clockForGifts.getElapsedTime().asSeconds() >= rand_time && gift_num != 0)
	{
		m_giftsVec.emplace_back(GiftFactory::createGift(l));
		gift_num--;
		clockForGifts.restart();
	}
	rotateGifts();
}
//������� ������ �� ������ ����� ������� ������ ���� ��� ����� �����
//--------------------------------------------
sf::Vector2f Board::findDirectionToMove(int x, int y)
{
	sf::Vector2f pos = { ZERO,ZERO };
	if (m_player->isRight(x))
		pos.x = TO_RIGHT;
	else if (m_player->isLeft(x))
		pos.x = TO_LEFT;
	else if (m_player->isUp(y))
		pos.y = TO_UP;
	else if (m_player->isDown(y))
		pos.y = TO_DOWN;
	if (m_player->isUp(y) && m_player->isRight(x)){
		pos.x = TO_RIGHT;
		pos.y = ZERO;
	}
	return pos;
}
//�������� �� ����� ������ �� �����-���� �����
//--------------------------------------------------------
void Board::eatCellInMatrix(int i, int j)
{
	if ((!(i <= ZERO || i >= MATRIX_SIZE - 1 || j <= ZERO || j >= MATRIX_SIZE - 1))
		&& (m_matrix[i][j] == BLOCKED || m_matrix[i][j] == MIDDLE)) {
		if (--m_blockCounter <= ZERO)
		{
			m_percentage--;
			m_blockCounter = AMOUNT_FOR_ONE_PERCENT;
		}
		m_matrix[i][j] = EMPTY;
		handleAnimationCrumb(i, j);
	}
}
//������� ������� �� ���������� �� ���������
//---------------------------------------------------------
void Board::handleCollision()
{
	handleEnemiesCollision(m_ballsVec, *m_player);
	handleEnemiesCollision(m_spidersVec, *m_player);
	for (int i = 0; i < m_giftsVec.size(); i++)
		if (colide(*m_giftsVec[i], *m_player))
		{
			processCollision(*m_giftsVec[i], *m_player);
			Graphics::getGraphics().getSoundVec()[GIFT_SOUND]->play();
		}
	eraseDeletedObjects();
}
//������� ������� �� ���������� �� �������
//---------------------------------------------------------
void Board::handleEnemiesCollision(std::vector<std::unique_ptr<Enemies>>& vec, Player& player)
{
	for (int i = 0; i < vec.size(); i++)
		if (colide(*vec[i], player))    //�����?
			processCollision(*vec[i], player);
}
//������� ������ ��� ���� �������
//-------------------------------------------------------------
bool Board::colide(Object& obj1, Object& obj2)const
{
	sf::FloatRect res;
	auto player = sf::FloatRect(obj2.getDisplay().getSprite().getGlobalBounds());
	return (player.intersects(obj1.getDisplay().getSprite().getGlobalBounds(), res));
}
//������� ������� ������ ������� ����
//-------------------------------------------------------------
void Board::createEnemiesInBoard(int curentLevel, Level* l, std::vector<int> vec)
{
	m_ballsVec = EnemyFactory::createBalls(curentLevel, l);
	m_spidersVec = EnemyFactory::createSpiders(curentLevel, l, vec);
}
//������� ������� ������ ���� ������ ����
//-------------------------------------------------------------
void Board::createTerritoryEnemiesInBoard(int curentLevel, Level* l, std::vector<int> vec)
{
	m_territoryEaterVec = EnemyFactory::createTerritoryEaters(curentLevel, l, vec);
}
//������� ������� �� ������� �����
//-------------------------------------------------------------
void Board::freezeEnemies()
{
	freezeEnemies(m_ballsVec);
	freezeEnemies(m_spidersVec);
	freezeEnemies(m_territoryEaterVec);
}
//������� ������� ����� �� ������
//-------------------------------------------------------------
template <typename enemyVec>
void Board::freezeEnemies(std::vector<typename enemyVec>& vec)
{
	for (auto& enemy : vec)
		enemy->freeze();
}
//������� ������ �� ����� �������
//-------------------------------------------------------------
void Board::unFreezeEnemies()
{
	unFreezeEnemies(m_ballsVec);
	unFreezeEnemies(m_spidersVec);
	unFreezeEnemies(m_territoryEaterVec);
}
//������� ������ ����� ����� �� ������
//-------------------------------------------------------------
template <typename enemyVec>
void Board::unFreezeEnemies(std::vector<typename enemyVec>& vec)
{
	for (auto& enemy : vec)
		enemy->unFreeze();
}
//������� ������� ������ ������ �� ����
//-------------------------------------------------------------
void Board::rotateGifts()
{
	for (int i = 0; i < m_giftsVec.size(); i++)
		m_giftsVec[i]->handleAnimation();
}
//������� ������� �� ������� ��������� �� ����� ����
//-------------------------------------------------------------
void Board::handleAnimationCrumb(int i, int j)
{
	sf::Vector2f pos;
	pos.x = BOARD_GAME_CELL_SIZE * j + BEGGINING_OF_BOARD_X - HALF_ENEMY_PIC_SIZE;
	pos.y = BOARD_GAME_CELL_SIZE * i + BEGGINING_OF_BOARD_Y - HALF_ENEMY_PIC_SIZE;
	m_crumbPic.setPosition(pos);
	m_crumbAnimation.handleAnimation();
	m_crumbPic.draw();
	Graphics::getGraphics().getWindow().display();
}
//������� ������� ���� ���� ���� 
//-------------------------------------------------------------
void Board::setPlayer()
{
	if (typeid(*m_player) != typeid(Player))
		setBackPlayer();
}
//������� ������ ��� ����� ����
//-------------------------------------------------------------
bool Board::checkIfBlocked(sf::Vector2i pos)const
{
	return (m_matrix[pos.x][pos.y] == BLOCKED);
}
//������� ������ ��� ����� �� ����
//-------------------------------------------------------------
bool Board::checkIUnfBlocked(sf::Vector2i pos)const
{
	return (m_matrix[pos.x][pos.y] == EMPTY || m_matrix[pos.x][pos.y] == MIDDLE);
}
//������� ������� �� ������ �� ����� ������
//-------------------------------------------------------------
void Board::setPlayerPositionToBegining()
{
	m_player->setPlayerPosition(sf::Vector2f(22, 0));
}
//����� ����� ����
//-------------------------------------------------------------
void Board::immuneThePlayer()
{
	m_player = std::make_unique < ImmunePlayer>(m_player->getPlayerXpos(), m_player->getPlayerYpos(), m_player->getPlayerDx(), m_player->getPlayerDy());
}
//����� ����� ����
//-------------------------------------------------------------
void Board::changePlayerToKilling()
{
	m_player = std::make_unique < KillingPlayer>(m_player->getPlayerXpos(), m_player->getPlayerYpos(), m_player->getPlayerDx(), m_player->getPlayerDy());
}
//����� ����� �����
//-------------------------------------------------------------
void Board::setBackPlayer()
{
	m_player = std::make_unique<Player>(m_player->getPlayerXpos(), m_player->getPlayerYpos(), m_player->getPlayerDx(), m_player->getPlayerDy());
}
//������� ������ �� ��������� ������ ���� ��� ������� ������
//-------------------------------------------------------------
void Board::eraseDeletedObjects()
{
	std::erase_if(m_ballsVec, [](const auto& ball) { return ball->isDead(); });
	std::erase_if(m_spidersVec, [](const auto& spider) { return spider->isDead(); });
	std::erase_if(m_giftsVec, [](const auto& gift) { return gift->isDead(); });
}
//������� ������� �� ����� ���� ����� �"� �����
//-------------------------------------------------------------
void Board::floodFill()
{
	floodFillOnEnemy(m_ballsVec);
	floodFillOnEnemy(m_territoryEaterVec);
}
//������� ������� �� ����� �������� �����_��� �� �������
//-------------------------------------------------------------
template <typename enemyVec>
void Board::floodFillOnEnemy(std::vector<typename enemyVec>& vec)
{
	for (int i = 0; i < vec.size(); i++)
		floodFill(vec[i]->getIndex());
}