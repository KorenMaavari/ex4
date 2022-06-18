#include "../utilities.h"
#include "Merchant.h"
using std::string;
using std::cin;
using std::cout;

Merchant::Merchant ()
:
    Card(MERCHANT_STR)
{

}

void Merchant::applyEncounter (Player& player) const
{
    printMerchantInitialMessageForInteractiveEncounter(cout,
    player.getName(), player.getCoins());
    int input;
    cin >> input;
    while (cin.fail() || input < 0 || input > 2)
    {
        printInvalidInput();
        cin >> input;
    }
    int price;
    if (input == HEALTH_POTION)
    {
        price = HEALTH_POTION_PRICE;
    }
    else if (input == FORCE_BOOST)
    {
        price = FORCE_BOOST_PRICE;
    }
    if (input == HEALTH_POTION && player.getCoins() >= HEALTH_POTION_PRICE)
    {
        player.pay(HEALTH_POTION_PRICE);
        player.heal(1);
        printMerchantSummary(cout, player.getName(), input, price);
    }
    else if (input == FORCE_BOOST && player.getCoins() >= FORCE_BOOST_PRICE)
    {
        player.pay(FORCE_BOOST_PRICE);
        player.buff(1);
        printMerchantSummary(cout, player.getName(), input, price);
    }
    else if (player.getCoins() < price)
    {
        printMerchantInsufficientCoins(cout);
    }
}
