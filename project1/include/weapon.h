#ifndef WEAPON_H
#define WEAPON_H
#include <string>
class Weapon
{
public:
    Weapon(const std::string &n, int dmg);

    void setName(const std::string &n) { name = n; }
    void setDamage(int dmg) { damage = dmg; }

    const std::string &getName() const { return name; }
    const int getDamage() const { return damage; }  
private:
    std::string name{"Weapon"};
    int damage{30};
};
#endif
