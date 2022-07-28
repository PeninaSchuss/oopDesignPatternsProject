#include "GiftFactory.h"
//---------------------------------------------------
std::vector<giftFunc>& GiftFactory::getGiftVec()
{
	static std::vector<giftFunc> m_giftV;
	return m_giftV;
}
//--------------------------------------------------
bool GiftFactory::registerGift(giftFunc mf)
{
	getGiftVec().emplace_back(std::move(mf));
	return true;
}
//--------------------------------------------------
std::unique_ptr<Gift> GiftFactory::createGift(Level* l)
{
	int rand_gift = rand() % AMOUNT_OF_GIFTS;
	return getGiftVec()[rand_gift](l);
}


