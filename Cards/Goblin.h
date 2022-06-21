#ifndef EX4_GOBLIN_H
#define EX4_GOBLIN_H

#include "Battle.h"

class Goblin : public Battle
{
    public:

        Goblin ();
        
        void printInfo (std::ostream& os) const override;

        void applyEncounter(Player& player) const override;

    private:

        // nothing
};

#endif // EX4_GOBLIN_H