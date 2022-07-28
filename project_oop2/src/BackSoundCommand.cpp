#include "BackSoundCommand.h"
//-------------------------------------------------------------
//������� ������� �� ����� ������ �� ����� �� ����� ������ ���� �� �����
//-------------------------------------------------------------
void BackSoundCommand::execute(Display& d)
{
	if (Graphics::getGraphics().getSoundVec()[FIRST_MUSIC]->getVolume() == VOLUME)
	{
		d.setTexture(Graphics::getGraphics().getTexture(UN_SOUND));
		Graphics::getGraphics().getSoundVec()[FIRST_MUSIC]->setVolume(ZERO);
	}
	else
	{
		d.setTexture(Graphics::getGraphics().getTexture(SOUND));
		Graphics::getGraphics().getSoundVec()[FIRST_MUSIC]->setVolume(VOLUME);
	}
}