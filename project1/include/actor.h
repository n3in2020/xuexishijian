#ifndef ACTOR_H
#define ACTOR_H
#include <string>
class Actor
{
public:
    Actor(const std::string &n, int h, int ad);
    virtual ~Actor() = default;
    virtual int calcDamage(int damage);

    void attack(Actor *other);
    void setName(const std::string &n) { name = n; }
    void setHealth(int h) { health = h; }
    void setAttackDamage(int damage) { attackDamage = damage; }
    void setDead(bool b) { dead = b; } 

    const std::string &getName() const { return name; }
    const int getHealth() const { return health; }
    const int getAttackDamage() const { return attackDamage; }
    const bool getDead() const { return dead;}
private:
    std::string name{"Actor"};
    int health = 300;
    int attackDamage = 40;
    bool dead{false};
};
#endif