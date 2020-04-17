#ifndef THEGAME_H
#define THEGAME_H
#include <vector>
#include "hero.h"

class TheGame
{
public:
    TheGame();
    ~TheGame();
    void init();
    void run();
    void update();

    void processConfig(const std::string &filename);

private:
    Hero *hero{nullptr};
    std::vector<Actor *> monsters{};
    bool isRunning{false};
};
#endif