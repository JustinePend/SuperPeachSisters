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
    void addToActors(Actor* actor);
    void bonkAllAtPoint(Actor* actor, int x, int y, int width, int height);
    bool checkWithBlocking(Actor* actor, int x, int y, int width, int height);
    bool overlapWithPeach(Actor* actor);
    void givePeachPower(int power);
private:
    vector<Actor*> actors;
    Level m_level;
    Actor* m_peach;
};
#endif // STUDENTWORLD_H_
