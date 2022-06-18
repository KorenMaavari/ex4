#include "Mtmchkin.h"
#include "Exception.h"
#include <fstream>
using std::ifstream;
using std::string;
using std::cin;
using std::cout; // דיבוג ידני
using std::getline;
using std::unique_ptr;


int Mtmchkin::m_numberOfRounds = 0;
int Mtmchkin::m_amountOfLosers = 0;
int Mtmchkin::m_amountOfWinners = 0;
int Mtmchkin::m_numberOfPlayers = 0;

Mtmchkin::Mtmchkin(const string fileName){
    checkFile(fileName);
    m_numberOfPlayers = initializeTeamSize();
    insertPlayers(m_numberOfPlayers);
    for(int i=0;i<MAXIMUM_AMOUNT_OF_PLAYERS;++i){
        m_playersRank[i] = i;
    }
};

void Mtmchkin::checkFile(const string fileName){
    int amountOfCards =0;
    ifstream source(fileName.c_str());
    if(!source){
        throw DeckFileNotFound();
    }
    try{
        string line;
        while (getline(source,line)){
            createCard(line,amountOfCards);
            ++amountOfCards;
        }
    }catch(const DeckFileFormatError& e){
        //m_cardsDeque.release();
        throw DeckFileFormatError(amountOfCards);
    }
    if(amountOfCards <= MINIMUM_AMOUNT_OF_CARDS){
        //m_cardsDeque.release();
        throw DeckFileInvalidSize();
    }
}

int Mtmchkin::initializeTeamSize() const{
    printStartGameMessage();
    string teamSize;
    while (true)
    {
        printEnterTeamSizeMessage();
        cin >> teamSize;
        if(teamSize.length() == 1 && isdigit(teamSize[0]))
        {
            if(teamSize[0] >= MINIMUM_AMOUNT_OF_PLAYERS && teamSize[0] <= MAXIMUM_AMOUNT_OF_PLAYERS)
            {
                return teamSize[0];
            }
        }
        printInvalidTeamSize();
    }
}

void Mtmchkin::insertPlayers(int teamSize){
    int players = 0;
    string str;
    string playerName;
    string playerClass;
    while(players < teamSize){
        printInsertPlayerMessage();
        cin >> str;
        if(str.find(SPACE_CHAR) == str.npos)// no class input
        {
            playerName = str;
            if(checkName(playerName)){
                printInvalidClass();
            }
            else{
                printInvalidName();
            }
        }
        else{ // input of player name and also class
            playerName = str.substr(0,str.find(SPACE_CHAR));
            playerClass = str.substr(str.find(SPACE_CHAR+1));
            if(checkName(playerName)){
                try{
                    createPlayer(playerName,playerClass);
                    ++players;
                }
                catch(PlayerInvalidClass()){
                    printInvalidClass();
                }
            }
            else{
                printInvalidName();
            }
        }

    }

}

void Mtmchkin::createPlayer(const std::string playerName, const std::string playerClass)
{
    if(FIGHTER_STR == playerClass){

        m_playersInGame.push_back(new Fighter(playerName));
    }
    else if(ROGUE_STR == playerClass){
        m_playersInGame.push_back(new Rogue(playerName));;
    }
    else if(WIZARD_STR == playerClass){
        m_playersInGame.push_back(new Wizard(playerName));;
    }
    else{
        throw PlayerInvalidClass();
    }

}

bool Mtmchkin::checkName(string playerName) const{
    if(playerName.length() <= MAX_PLAYER_NAME_LENGTH){
        for(int i=0; i< playerName.length();++i){
            if(!(isalpha(playerName[0]))){
                return false;
            }
        }
        return true;
    }
    return false;
}

int Mtmchkin::getNumberOfRounds() const{
    return m_numberOfRounds;
}

void Mtmchkin::updateGame(){
    for(int i=m_amountOfWinners;i<m_numberOfPlayers-m_amountOfLosers;++i){
        if(m_isInGame.at(i)){
            if(m_playersInGame.at(i)->*isKnockedOut()){
                m_isInGame.at(i) = false;
                for(int j=i;j<m_numberOfPlayers-m_amountOfLosers-1;++j){
                    swap(m_playersRank[j],m_playersRank[j+1]);
                }
                ++m_amountOfLosers;
            }
            if(m_playersInGame.at(i)->getLevel() == MAX_LEVEL)
            {
                m_isInGame.at(i) = false;
                for(int j=i;j>m_amountOfWinners+1;--j){
                    swap(m_playersRank[j],m_playersRank[j-1]);
                }
                ++m_amountOfWinners;
            }
        }
    }
}

bool Mtmchkin::isGameOver() const{
    bool isOver = false;
    for(int i=0; i<m_numberOfPlayers;++i){
        if(m_isInGame.at(i)){
            return false;
        }
    }
    return true;
}

void Mtmchkin::playRound(){
    printRoundStartMessage(m_numberOfRounds);
    for(int i=0;i<m_numberOfPlayers;++i){
        if(m_isInGame.at(i)){
            printTurnStartMessage(m_playersInGame[i]->getName());
            m_cardsDeque[i]->applyEncounter(*m_playersInGame[i]);
            m_cardsDeque[m_cardsDeque.size()] = m_cardsDeque[0];
            m_cardsDeque.pop_front();
        }
    }
    ++m_numberOfRounds;
    if(isGameOver()){
        printGameEndMessage();
    }

}

void Mtmchkin::printLeaderBoard() const{
    printLeaderBoardStartMessage();
    for(int i=0;i<m_numberOfPlayers;++i){
        printPlayerLeaderBoard(i+1,*m_playersInGame[m_playersRank[i]]);
    }
}

void Mtmchkin::createCard(const string cardString,int row){

    if(cardString == GOBLIN_STR){
        m_cardsDeque.push_back(new Goblin());
    }
    else if(cardString == VAMPIRE_STR){
       m_cardsDeque.push_back(new Vampire());
    }
    else if(cardString == DRAGON_STR){
        m_cardsDeque.push_back(new Dragon());
    }
    else if(cardString == BARFIGHT_STR){
        m_cardsDeque.push_back(new Barfight());
    }
    else if(cardString == FAIRY_STR){
        m_cardsDeque.push_back(new Fairy());
    }
    else if(cardString == PITFALL_STR){
        m_cardsDeque.push_back(new Pitfall());
    }
    else if(cardString == TREASURE_STR){
        m_cardsDeque.push_back(new Treasure());
    }
    else if(cardString == MERCHANT_STR){
        m_cardsDeque.push_back(new Merchant());
    }
    else{
        throw DeckFileFormatError(row);
    }
    
}