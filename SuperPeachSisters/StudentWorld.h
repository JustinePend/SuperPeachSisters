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
    void levelDone();
    void gameDone();
    
    void bonkAllAtPoint(Actor* actor, int x, int y, int width, int height);
    bool damageAllAtPoint(Actor* actor, int x, int y, int width, int height);
    bool checkWithBlocking(Actor* actor, int x, int y, int width, int height);
    bool checkEdge(Actor* actor, int x, int y, int width, int height);
    bool overlapWithPeach(Actor* actor);
    
    bool isPeach(Actor* actor);
    int getPeachPower(int power);
    int getPeachX();
    int getPeachY();
    void bonkPeach();
    void damagePeach();
    void givePeachPower(int power);
    void peachSetTicks(int power);
private:
    vector<Actor*> actors;
    Level m_level;
    Peach* m_peach;
    bool levelActive;
    bool gameActive;
    int level;
};
#endif // STUDENTWORLD_H_
