#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    Peach *peach = new Peach(100,100,getWorld());
    actors.push_back(*peach);
}

//StudentWorld::~StudentWorld() {
//    for(int i = 0; i < actors.size(); i++) {
//        delete actors[i];
//    }
//}

Actor* StudentWorld::overlap(int x, int y, int width, int height) {
    for(int i = 0; i < actors.size(); i++) {
        if(actors[i].actorOverlap(x, y, width, height))
            return &actors[i];
    }
    return nullptr;
}

StudentWorld* StudentWorld::getWorld() {

    return this;
}

int StudentWorld::init()
{
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}
