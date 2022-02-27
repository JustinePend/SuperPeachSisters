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
                case Level::peach: {
                    Peach *peach = new Peach(i*SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld());
                    m_peach = peach;
                    break;
                } case Level::block: {
                    Block *block = new Block(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld(), 0);
                    actors.push_back(block);
                    break;
                } case Level::pipe: {
                    Pipe *pipe = new Pipe(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld());
                    actors.push_back(pipe);
                    break;
                } case Level::goomba: {
                    Goomba *goomba = new Goomba(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld());
                    actors.push_back(goomba);
                    break;
                } case Level::koopa: {
                    Koopa *koopa = new Koopa(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld());
                    actors.push_back(koopa);
                    break;
                } case Level::piranha: {
                    Piranha *piranha = new Piranha(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld());
                    actors.push_back(piranha);
                    break;
                } case Level::mushroom_goodie_block: {
                    Block *block = new Block(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld(), 1);
                    actors.push_back(block);
                    break;
                } case Level::flower_goodie_block: {
                    Block *block = new Block(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld(), 2);
                    actors.push_back(block);
                    break;
                } case Level::star_goodie_block: {
                    Block *block = new Block(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld(), 3);
                    actors.push_back(block);
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
    cleanUp();
}

Actor* StudentWorld::overlap(Actor* actor, int x, int y, int width, int height) {
    for(int i = 0; i < actors.size(); i++) {
        if(actors[i]->actorOverlap(x, y, width, height)) {
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

void StudentWorld::addToActors(Actor *actor) {
    actors.push_back(actor);
}

int StudentWorld::init()
{
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    
//    decLives();
//    return GWSTATUS_PLAYER_DIED;
    m_peach->doSomething();

    for(int i = 0; i < actors.size(); i++) {
        actors[i]->doSomething();
    }

    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    for(int i = 0; i < actors.size(); i++) {
        delete actors[i];
    }
}
