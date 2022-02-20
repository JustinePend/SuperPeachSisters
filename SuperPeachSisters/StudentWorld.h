#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>

#include "Actor.h"
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp


class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    StudentWorld* getWorld();
    Actor* overlap(int x, int y, int width, int height);
private:
    vector<Actor*> actors;
    Level m_level;
};
#endif // STUDENTWORLD_H_
