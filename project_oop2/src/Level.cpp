#include "Level.h"
//----------------------------------
Level::Level(int curentLevel, std::vector<int> infoLevelVec)
    :m_board(curentLevel, m_percentage), m_timeForLevel((rand() % HALF_MINUTE) + HALF_MINUTE+ FIVE_SECONDS), m_infoMenu(char(curentLevel + FOR_ASCII_CONVERSION),
         m_timeForLevel), m_infoOfLevel(infoLevelVec), m_explosionPic(Graphics::getGraphics().getTexture(EXPLOSION_ANIMATION), BEGGINIG_OF_MATRIX, EXPLOSION_SPRITE_SHEET_SIZE), m_explosionAnimation(m_explosionPic, EXPLOSION_SPRITE_SHEET_SIZE.x, EXPLOSION_SPRITE_SHEET_SIZE.y),
        m_levelUp(Graphics::getGraphics().getTexture(LEVEL_UP), sf::Vector2f(MIDDLE_BOARD_X, MIDDLE_BOARD_Y), LEVEL_UP_SIZE),m_currentLevel(curentLevel)
    , m_winGame(Graphics::getGraphics().getTexture(WIN_GAME), { MIDDLE_BOARD_X ,MIDDLE_BOARD_Y}, WIN_SIZE)
{
    m_board.createEnemiesInBoard(curentLevel, this, m_infoOfLevel);
    m_board.createTerritoryEnemiesInBoard(curentLevel, this, m_infoOfLevel);
    m_levelUp.setOrigin(LEVEL_UP_SIZE.x /2, LEVEL_UP_SIZE.y /2);
    m_winGame.setOrigin(WIN_SIZE.x/2, WIN_SIZE.y / 2);
}
//������� ������� �� ���� �� ���
//----------------------------------
enum EndOfLevelCondition Level::runLevel()
{
    while (Graphics::getGraphics().getWindow().isOpen())
    {
        if (handleEvents() == CLOSE)
            return CLOSE;

        movesObjects();
        handlePlayer();
        m_board.handleSpaceBlockage();
        m_board.handleCreateGifts(m_gift_num, m_rand_time, this);
        handleTime();

        if (m_infoOfLevel[LIFE_AMOUNT] < ZERO)
            return FAIL_LEVEL;
        drawWindow();
        if (handlePercentage() == FINISHLEVEL)
        {
            drawWindow();
            return FINISHLEVEL;
        }
    }
    return JUST_FOR_VISUAL; 
}
//������� ������� �� ����� ����� ��� �������
//------------------------------------------------
void Level::handlePlayer()
{
    if (m_board.checkIfPassedAlready())
        handleFailure();
    m_board.handleCollision();
}
//������� ������ ������ �������� 
//------------------------------------------------
enum EndOfLevelCondition Level::handleEvents()
{
    sf::Event event;
    while (Graphics::getGraphics().getWindow().pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed: {
            Graphics::getGraphics().getWindow().close();
            return CLOSE;}
        case sf::Event::KeyPressed: {
            m_board.setDirection(event.key.code);break;}
        }
    }
    return JUST_FOR_VISUAL;
}
//������� ������� �� �� �� ����� ���� �� ����
//------------------------------------------------
void Level::handleTime()
{
    if (int(m_timeForLevel - m_clock.getElapsedTime().asSeconds()) == 10)
        Graphics::getGraphics().getSoundVec()[CLOCK_SOUND]->play();
    if (float(m_timeForLevel - m_clock.getElapsedTime().asSeconds()) <= 0 ||  (int(m_timeForLevel - m_clock.getElapsedTime().asSeconds()) > 10) )
        Graphics::getGraphics().getSoundVec()[CLOCK_SOUND]->pause();
    if (float(m_timeForLevel - m_clock.getElapsedTime().asSeconds()) <= 0)
    {
        handleFailure();
        m_clock.restart();
    }
    m_infoMenu.setTimer(float(m_timeForLevel - m_clock.getElapsedTime().asSeconds()));

    if (m_clockForGift.getElapsedTime().asSeconds() >= FIVE_SECONDS)
    {
        m_board.unFreezeEnemies();
        m_board.setPlayer();
    }
}
//������� ������� �� ������� ������ ���
//------------------------------------------------
enum EndOfLevelCondition Level::handlePercentage()
{
    m_infoMenu.setPercentage(m_percentage, m_infoOfLevel[PERCENTAGE]);
    if (m_percentage >= m_infoOfLevel[PERCENTAGE])
        return FINISHLEVEL;
    return JUST_FOR_VISUAL;
}
//������� ������� �� ������ �� �����
//------------------------------------------------
void Level::handleFailure()
{
    --m_infoOfLevel[LIFE_AMOUNT]; 
    handleAnimationExplosion();
    m_board.setPlayerPositionToBegining();
    Graphics::getGraphics().getSoundVec()[FAILURE_SOUND]->play();
}
//������� ������� �� ����� ��������� �����
//------------------------------------------------
void Level::movesObjects()
{
    m_board.movePlayer();
    if (m_board.moveEnemies())  handleFailure();
}
//������� ������� �� ������ 
//------------------------------------------------
void Level::drawWindow()
{
    Graphics::getGraphics().getWindow().clear();
    m_board.draw(m_infoOfLevel);
    m_infoMenu.drawInfoMenu(m_infoOfLevel[LIFE_AMOUNT]);
    if (m_percentage >= m_infoOfLevel[PERCENTAGE] && m_currentLevel!= LAST_LEVEL)
        m_levelUp.draw();
    else if(m_percentage >= m_infoOfLevel[PERCENTAGE] && m_currentLevel == LAST_LEVEL)
        m_winGame.draw();
    Graphics::getGraphics().getWindow().display();
}
//������� ������� �� ������� ��������� 
//------------------------------------------------
void Level::handleAnimationExplosion()
{
    for (int i = 0; i < 5; i++)
    {
        Graphics::getGraphics().getWindow().clear();
        drawWindow();
        m_explosionAnimation.handleAnimation();
        m_explosionPic.draw();
        Graphics::getGraphics().getWindow().display();
    }
}
