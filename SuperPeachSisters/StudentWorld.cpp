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

void StudentWorld::bonkAllAtPoint(Actor* actor, int x, int y, int width, int height) {
    for(int i = 0; i < actors.size(); i++) {
        if(actors[i]->actorOverlap(x, y, width, height)) {
            if(&actor != &actors[i]) {
                actors[i]->bonk();
            }
        }
    }
}
//if there is anything there that blocks, return true.
bool StudentWorld::checkWithBlocking(Actor* actor, int x, int y, int width, int height) {
    for(int i = 0; i < actors.size(); i++) {
        if(actors[i]->actorOverlap(x,y, width, height) && actors[i]->blocksOthers()) {
            if(&actor != &actors[i]) {
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::checkEdge(Actor *actor, int x, int y, int width, int height) {
    for(int i = 0; i < actors.size(); i++) {
        if(actors[i]->edgeOverlap(x,y, width, height) && actors[i]->blocksOthers()) {
            if(&actor != &actors[i]) {
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::overlapWithPeach(Actor* actor) {
    return m_peach->actorOverlap(actor->getX(), actor->getY(), SPRITE_WIDTH, SPRITE_HEIGHT);
}

bool StudentWorld::isPeach(Actor* actor) {
    return actor == m_peach;
}

void StudentWorld::bonkPeach() {
    m_peach->bonk();
}

void StudentWorld::givePeachPower(int power) {
    //1 is mushroom, 2 is flower, 3 is star
    m_peach->setHitPoints(2);
    m_peach->setPower(power);
}

void StudentWorld::peachSetTicks(int power) {
    m_peach->setTicks(power);
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

    Actor* actor;
    for(int i = 0; i < actors.size(); i++) {
        if(!actors[i]->isAlive()) {
            actor = actors[i];
            actors.erase(actors.begin() + i);
            delete actor;
        }
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
