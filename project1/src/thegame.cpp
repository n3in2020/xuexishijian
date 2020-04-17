#include "thegame.h"
#include "helper.h"

TheGame::TheGame()
{
    init();
}
TheGame::~TheGame()
{
    delete (hero);
    monsters.clear();
}

void TheGame::init()
{
    processConfig("./config");
    if (hero != nullptr)
    {
        Weapon *weapon = new Weapon("Blade", 20);
        hero->equipWeapon(weapon);
    }
    isRunning = true;
}

void TheGame::run()
{
    update();
    if(hero->getDead())
    {
        printf("## Monsters wins!\n");
    }
    else
    {
         printf("## Hero wins!\n");
    }
}

void TheGame::update()
{
    while (isRunning)
    {
        if (monsters.empty())
        {
            isRunning = false;
            return;
        }
        if (hero->getHealth() <= 0)
        {
            isRunning = false;
            return;
        }
        auto it = monsters.begin();
        while (it != monsters.end())
        {
            hero->attack(*it);
            if ((*it)->getDead())
            {
                monsters.erase(it);
                it--;
            }
            it++;
        }
        it = monsters.begin();
        while (it != monsters.end())
        {
            (*it)->attack(hero);
            if (hero->getHealth() <= 0)
            {
                isRunning = false;
                return;
            }
            it++;
        }
    }
}

void TheGame::processConfig(const std::string &filename)
{
    printf("reading config ...\n");
    std::vector<std::string> config = readFile(filename);
    auto it = config.begin();
    enum Types
    {
        HERO,
        MONSTER,
        MINION,
    };
    int currType;
    std::string name;
    int h, ad, amr;
    while (it != config.end())
    {
        if ((*it) == "HERO")
        {
            currType = Types::HERO;
        }
        else if((*it) =="MONSTER")
        {
            currType = Types::MONSTER;   
        }
        else if((*it) =="MINION")
        {
            currType = Types::MINION;
        }
        else
        {
            errExit("Unknown type\n");
        }
        it++;
        name = *it;
        it++;
        if(isNum((*it)))
        {
            h = std::stoi((*it).c_str());
        }
        else 
            errExit("Health value should be a number!");
        it++;
        if(isNum(*it))
        {
            ad = std::stoi((*it).c_str());
        }
        else
        {
            errExit("AttackDamage value should be a number!");
        }
        it++;
        if(currType!=Types::MINION)
        {
            if (isNum(*it))
            {
                amr = std::stoi((*it).c_str());
            }
            else
            {
                errExit("Armor value should be a number!");
            }
            it++;
        }
        if(currType == Types::MINION)
        {
            monsters.push_back(new Actor(name, h, ad));
        }
        else
        {
            if (currType == Types::HERO)
            {
                hero = new Hero(name, h, ad, amr);
            }
            else
            {
                monsters.push_back(new Actor_plusArmor(name, h, ad, amr));
            }
        }
    }
    printf("config readed!\n");
}
