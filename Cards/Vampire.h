#ifndef EX4_VAMPIRE_H
#define EX4_VAMPIRE_H

#include "Battle.h"

class Vampire : public Battle
{
    public:

        Vampire ();

        void printInfo (std::ostream& os) const override;

        void applyEncounter(Player& player) const override;

    private:

        // nothing
};

#endif // EX4_VAMPIRE_H