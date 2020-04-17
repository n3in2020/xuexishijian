#ifndef ACTOR_PLUSARMOR_H
#define ACTOR_PLUSARMOR_H
#include "actor.h"
class Actor_plusArmor : public Actor
{
public:
    Actor_plusArmor(const std::string &n, int h, int ad, int amr);
    ~Actor_plusArmor(){};
    
    int calcDamage(int damage) override;
private:
    int armor;
};
#endif