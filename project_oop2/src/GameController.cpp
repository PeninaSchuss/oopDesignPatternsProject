#include "GameController.h"
#include "InfoOfLevel.h"
//----------------------------------------------------------------
GameController::GameController()
	:m_gameOver(Graphics::getGraphics().getTexture(GAME_OVER), MIDDLE_MATRIX, GAME_OVER_SIZE)
{
	m_gameOver.setOrigin(GAME_OVER_SIZE.x / 2, GAME_OVER_SIZE.y / 2);
}
//������� ������� �� ����� �����
//----------------------------------------------------------------
void GameController::runTheGame()
{
	int curentLevel = FIRST_LEVEL;
	runGameLevels(curentLevel);
	if (curentLevel < LEVELS_AMOUNT + 1)
	{
		m_gameOver.draw();
		Graphics::getGraphics().getWindow().display();
		sf::sleep(sf::Time(sf::seconds(THREE_SECONDS)));
	}
	Graphics::getGraphics().getWindow().display();
}
//----------------------------------------------------------------
//������� ������ �� ���� �����
void GameController::runGameLevels(int& curentLevel)
{
	enum EndOfLevelCondition endLevelCondition;
	while (curentLevel <= LEVELS_AMOUNT)
	{
		Level level(curentLevel, m_infoOfLevel.m_amountEnemiesInLevelMatrix[curentLevel]);
		endLevelCondition = level.runLevel();
		Graphics::getGraphics().getSoundVec()[CLOCK_SOUND]->pause();

		if (endLevelCondition == FAIL_LEVEL)
			return;
		else if (endLevelCondition == CLOSE)
			return;
		else if (endLevelCondition == FINISHLEVEL)
		{
			Graphics::getGraphics().getSoundVec()[WIN_SOUND]->play();
			sf::sleep(sf::Time(sf::seconds(THREE_SECONDS)));
			curentLevel++;
		}
	}
}

