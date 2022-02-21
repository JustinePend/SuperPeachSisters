#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_level(assetPath)
{
    m_level.loadLevel("level01.txt");
    
    for(int i = 0; i< GRID_WIDTH; i++) {
        for(int j = 0; j < GRID_HEIGHT; j++) {
            switch(m_level.getContentsOf(i,j)) {
                case Level::block: {
                    Block *block = new Block(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld());
                    actors.push_back(block);
                    break;
                }
                case Level::peach: {
                    Peach *peach = new Peach(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld());
                    actors.push_back(peach);
                    
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }
    
    
}
    
StudentWorld::~StudentWorld() {
    for(int i = 0; i < actors.size(); i++) {
        delete actors[i];
    }
}

Actor* StudentWorld::overlap(Actor* actor, int x, int y, int width, int height) {
    for(int i = 0; i < actors.size(); i++) {
        if(actors[i]->actorOverlap(actor->getX(), actor->getY(), SPRITE_WIDTH, SPRITE_HEIGHT)) {
            cerr << i << " actor " << &actor << " actor[i] " << &actor[i] << endl;
            
            cout << "overlaps " << actor->getX() << " " << actor->getY() <<  " " << actors[i]->getX() <<  " " << actors[i]->getY() << endl;
            if(&actor != &actors[i]) {
                return actors[i];
            }
        }
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
//    decLives();
//    return GWSTATUS_PLAYER_DIED;
    for(int i = 0; i < actors.size(); i++) {
        actors[i]->doSomething();
    }
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
}
