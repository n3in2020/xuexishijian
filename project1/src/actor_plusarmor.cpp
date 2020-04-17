#include "actor_plusarmor.h"

Actor_plusArmor::Actor_plusArmor(const std::string &n, int h, int ad, int amr) : Actor{n, h, ad}, armor{amr} {}

int Actor_plusArmor::calcDamage(int damage)
{
    int dmg = damage - armor;
    if (dmg < 0)
        dmg = 1;
    return dmg;
}