#ifndef HERO_H
#define HERO_H
#include "actor_plusarmor.h"
#include <vector>
#include "weapon.h"
class Hero : public Actor_plusArmor
{
public:
    using Actor_plusArmor::Actor_plusArmor;
    Hero(const std::string &n, int h, int amr, int ad, Weapon *weapon);
    ~Hero();
    void equipWeapon(Weapon *weapon);
    void destroyWeapon();
    const bool isEquipped() const { return weapon != nullptr; }
private:
    Weapon *weapon{nullptr};
};
#endif