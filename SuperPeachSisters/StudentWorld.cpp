#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_level(assetPath)
{
    levelActive = true;
    gameActive = true;
    level = 1;
}
    
StudentWorld::~StudentWorld() {
    cleanUp();
}

void StudentWorld::levelDone() {
    levelActive = false;
}

void StudentWorld::gameDone() {
    gameActive = false;
}
void StudentWorld::bonkAllAtPoint(Actor* actor, int x, int y, int width, int height) {
    for(int i = 0; i < actors.size(); i++) {
        if(actors[i]->actorOverlap(x, y, width, height)) {
            if(&actor != &actors[i]) {
                actors[i]->bonk(actor);
            }
        }
    }
}
//if there is anything there that blocks, return true.
bool StudentWorld::damageAllAtPoint(Actor* actor, int x, int y, int width, int height) {
    bool damaged = false;
    for(int i = 0; i < actors.size(); i++) {
        if(actors[i]->actorOverlap(x,y, width, height) && actors[i]->isDamageable()) {
            if(&actor != &actors[i] && actors[i]->isAlive()) {
                actors[i]->damage();
                damaged = true;
            }
        }
    }
    return damaged;
}

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

int StudentWorld::getPeachPower(int power) {
    return m_peach->getPower(power);
}

int StudentWorld::getPeachX() {
    return m_peach->getX();
}

int StudentWorld::getPeachY() {
    return m_peach->getY();
}


void StudentWorld::bonkPeach() {
    m_peach->bonk();
}

void StudentWorld::damagePeach() {
    m_peach->damage();
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
    levelActive = true;
    
    ostringstream oss;
    oss << setw(2) <<setfill('0') << getLevel();
    string lv = "level" + oss.str() + ".txt";
    m_level.loadLevel(lv);
    
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
                } case Level::flag: {
                    Flag *flag = new Flag(i * SPRITE_WIDTH, j*SPRITE_HEIGHT, getWorld());
                    actors.push_back(flag);
                    break;
                }
                default: {
                    break;
                }
                 
            }
        }
    }
    
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
    ostringstream oss;
    oss << "Lives: " << getLives() << "  Level: " << level << " Points: " << getScore();
    if(m_peach->getPower(3))
        oss << " StarPower!";
    if(m_peach->getPower(2))
        oss << " ShootPower!";
    if(m_peach->getPower(1))
        oss << " JumpPower!";
    
    string text = oss.str();
    setGameStatText(text);
    
    if(!m_peach->isAlive()) {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    if(!levelActive) {
        playSound(SOUND_FINISHED_LEVEL);
        level++;
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    if(!gameActive) {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    

    Actor* actor;
    for(int i = 0; i < actors.size(); i++) {
        if(!actors[i]->isAlive()) {
            actor = actors[i];
            actors.erase(actors.begin() + i);
            delete actor;
            i--;
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    Actor* actor;

    for(int i = 0; i < actors.size(); i++) {
        actor = actors[i];
        actors.erase(actors.begin() + i);
        delete actor;
        i--;
    }
}
