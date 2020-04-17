#include "hero.h"

Hero::Hero(const std::string &n, int h, int ad, int amr, Weapon *w)
    : Actor_plusArmor{n, h, ad, amr}, weapon{w}
{
}

void Hero::equipWeapon(Weapon *w)
{
    weapon = w;
    setAttackDamage(getAttackDamage()+w->getDamage());
    printf("++ %s equipped with a weapon: %s, added %d AD\n", getName().c_str(), w->getName().c_str(),w->getDamage());
}

void Hero::destroyWeapon()
{
    if (isEquipped())
        delete (weapon);
}

Hero::~Hero()
{
    destroyWeapon();
}
