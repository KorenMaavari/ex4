#include "Card.h"
#include "../utilities.h"
using std::string;

Card::Card (const string cardName)
:
    m_cardName (cardName)
{

    bool isFirst = true;
    bool isCardNameValid = false;
    if
    (
        cardName == BARFIGHT_STR ||
        cardName == DRAGON_STR ||
        cardName == FAIRY_STR ||
        cardName == GOBLIN_STR ||
        cardName == MERCHANT_STR ||
        cardName == PITFALL_STR ||
        cardName == TREASURE_STR ||
        cardName == VAMPIRE_STR
    )
    {
        isCardNameValid = true;
    }
    if (isCardNameValid == false)
    {
        throw DeckFileFormatError();
    }
}

void Card::printInfo(std::ostream& os) const
{
    printCardDetails(os, this->m_cardName);
    printEndOfCardDetails(os);
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    card.printInfo(os);
    return os;
}
