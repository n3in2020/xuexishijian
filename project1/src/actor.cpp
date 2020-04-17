#include "actor.h"
#include <iostream>
Actor::Actor(const std::string& n, int h, int ad) :name(n), health{h}, attackDamage{ad} {}

void Actor::attack(Actor *other) {
    int dmg = other->calcDamage(attackDamage);
    other->setHealth(other->getHealth() - dmg);
    if(other->getHealth()<0)
    {
        other->setHealth(0);
        other->setDead(true);
    }
    printf("++ %s attacked %s and dealed with %d damage, now %s's health is %d\n", 
    name.c_str(), other->name.c_str(), dmg, other->name.c_str(), other->getHealth());
    if(other->getDead()){
        printf("-- %s is dead.\n", other->name.c_str());
    }
}

int Actor::calcDamage(int damage)
{
    return damage;
}
