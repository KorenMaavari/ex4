#include "Cards/Card.h"
#include "Players/Player.h"
#include "Cards/Barfight.h"
#include "Cards/Dragon.h"
#include "Cards/Fairy.h"
#include "Cards/Goblin.h"
#include "Cards/Merchant.h"
#include "Cards/Pitfall.h"
#include "Cards/Treasure.h"
#include "Cards/Vampire.h"
#include "Players/Fighter.h"
#include "Players/Rogue.h"
#include "Players/Wizard.h"
#include "utilities.h"
#include "Exception.h"
#include "Mtmchkin.h"
using std::cout;
using std::cerr;
using std::endl;
using std::string;

#define SOURCE_FILE_ARGV_INDEX 2

int main ()
{
    // Wizard shlomo = Wizard("Shlomo");
    // cout << shlomo;
    // Treasure treasure = Treasure();
    // cout << treasure;
    // treasure.applyEncounter(shlomo);
    // cout << shlomo;
    
    try{
        const string theCards= "C:\\Users\\koren\\Desktop\\Technion\\hw\\Systems Programming\\hw4\\deck.txt";
        Mtmchkin game(theCards);
        while (!game.isGameOver())
        {
            game.playRound();
        }
        game.printLeaderBoard();
    }
    catch(const DeckFileNotFound& e){
        cerr << e.what() << endl;
    }
    catch(const DeckFileFormatError& e){
        cerr << e.what() << endl;
    }
    catch(const DeckFileInvalidSize& e){
        cerr << e.what() << endl;
    }
    
    return 0;
}
