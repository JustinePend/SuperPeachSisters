#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

/*
 It must have a constructor that initializes the object appropriately.
 It must be derived from our GraphObject class.
 It must have a member function named doSomething() that can be called to cause the actor to do something.
 You may add other public/private member functions and private data members to this base class, as you see fit.
 */

StudentWorld* Actor::getWorld() {
    return m_world;
}

bool Actor::actorOverlap(int otherX, int otherY, int otherWidth, int otherHeight) {
    int xPos = getX();
    int yPos = getY();
    int xMaxThis = xPos + SPRITE_WIDTH - 1;
    int yMaxThis = yPos + SPRITE_HEIGHT - 1;
    int xMaxOther = otherX + otherWidth - 1;
    int yMaxOther = otherY + otherHeight - 1;
    
    //if any x edge overlaps with the x edges of the other actor, and any y edge overlaps with the other y edge, there is overlap.

       if(((otherX <= xMaxThis && otherX >= xPos) && ((otherY <= yMaxThis && otherY >= yPos) || (yMaxOther <= yMaxThis && yMaxOther >= yPos))) ||
          ((xMaxOther <= xMaxThis && xMaxOther >= xPos) && ((otherY <= yMaxThis && otherY >= yPos) || (yMaxOther <= yMaxThis && yMaxOther >= yPos)))) {
        return true;
    } else {
        return false;
    }
}

bool Actor::edgeOverlap(int otherX, int otherY, int otherWidth, int otherHeight) {
    int xPos = getX();
    int xMaxThis = xPos + SPRITE_WIDTH - 1;
    int xMaxOther = otherX + otherWidth - 1;
    
    if((xMaxOther > xMaxThis && !checkBlocking(otherX + 7, otherY - 7)) || (otherX < xPos && !checkBlocking(otherX - 7, otherY - 7)))
        return true;
    else
       return false;
}

void Actor::bonkPoint(int x, int y) {
    getWorld()->bonkAllAtPoint(this, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);
}

bool Actor::damagePoint(int x, int y) {
    return getWorld()->damageAllAtPoint(this, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);
}

bool Actor::checkBlocking(int x, int y) {
    return getWorld()->checkWithBlocking(this, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);
}

bool Actor::checkPeachOverlap() {
    return getWorld()->overlapWithPeach(this);
}
bool Actor::checkEdgeOverlap(int x, int y) {
    return getWorld()->checkEdge(this, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);
}

bool Actor::isAlive() {
    
    return alive;
}
void Actor::setAlive(bool status) {
    alive = status;
}

void Actor::damage() {}


//==========================================//
//                  PEACH                   //
//==========================================//

void Peach::doSomething() {
    if(!isAlive())
        return;
    
    if(starPower) {
        starTicks --;
        if(starTicks <= 0)
            starPower = false;
    }
    
    if(tempInvincibility) {
        tempTicks --;
        if(tempTicks <= 0)
            tempInvincibility = false;
    }
    
    if(fireTicks > 0)
        fireTicks --;
    
    bonkPoint(getX(), getY());
    
    int targetY = getY() + 4;
    if(!checkBlocking(getX(), targetY) && remaining_jump_distance > 0 && hasJumped == true) {
        moveTo(getX(), targetY);
        remaining_jump_distance --;
    } else {
        bonkPoint(getX(), targetY);
        remaining_jump_distance = 0;
        hasJumped = false;
    }
    
    if(!hasJumped) {
        bool below = false;
        for(int i = 0; i <= 3; i++) {
            if(checkBlocking(getX(), getY() - i)) {
                below = true;
                break;
            }
        }
        if(!below)
            moveTo(getX(), getY() - 4);
    }

    int key;
    if(getWorld()->getKey(key)) {
        if(key == KEY_PRESS_LEFT) {
            setDirection(180);
            int nextX = getX() - 4;
            if(!checkBlocking(nextX, getY()))
                moveTo(nextX, getY());
        } else if(key == KEY_PRESS_RIGHT) {
            setDirection(0);
            int nextX = getX() + 4;
            if(!checkBlocking(nextX, getY()))
                moveTo(nextX, getY());
        } else if(key == KEY_PRESS_UP) {
            hasJumped = true;
            if(checkBlocking(getX(), getY() - 1)) {
                if(!jumpPower)
                    remaining_jump_distance = 8;
                else
                    remaining_jump_distance = 12;
                getWorld()->playSound(SOUND_PLAYER_JUMP);
            }
        } else if(key == KEY_PRESS_SPACE) {
            if(shootPower && fireTicks <= 0) {
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                fireTicks = 8;
                
                int nextX;
                if(getDirection() == 0) {
                    nextX = getX() + 8;
                } else {
                    nextX = getX() - 8;
                    }
                PeachFireball* fireball = new PeachFireball(nextX, getY(), getWorld(), getDirection());
                getWorld()->addToActors(fireball);
            }
        }
    }
    return;
}

void Peach::bonk(Actor* actor) {
    if(starPower || tempInvincibility)
        return;
    setHitPoints(getHitPoints()-1);
    tempInvincibility = true;
    tempTicks = 10;
    shootPower = false;
    jumpPower = false;
    if(getHitPoints() >= 1)
        getWorld()->playSound(SOUND_PLAYER_HURT);
    else {
        setAlive(false);
    }
}

void Peach::damage() {
    bonk();
}


bool Peach::blocksOthers() {
    return false;
}

bool Peach::isDamageable() {
    return true;
}

int Peach::getHitPoints() {
    return hitPoints;
}
void Peach::setHitPoints(int val) {

    hitPoints = val;
    if(hitPoints <= 0)
        setAlive(false);
}

void Peach::setPower(int power) {
    //1 is mushroom, 2 is flower, 3 is star
    if(power == 1)
        jumpPower = true;
    if(power == 2)
        shootPower = true;
    if(power == 3)
        starPower = true;
}

int Peach::getPower(int power) {
    if(power == 1)
        return jumpPower;
    if(power == 2)
        return shootPower;
    if(power == 3)
        return starPower;
    return 0;
}

void Peach::setTicks(int power) {
    if(power == 2 )
        starTicks = 150;
}

//==========================================//
//                  OBJECTS                 //
//==========================================//

bool Object::blocksOthers() {
    return true;
}
bool Object::isDamageable() {
    return false;
}

//=================BLOCK====================//

void Block::doSomething() {
    return;
}

void Block::bonk(Actor* actor) {
    if(m_goodie == 0) {
        getWorld()->playSound(SOUND_PLAYER_BONK);
    } else {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        switch(m_goodie) {
                //1 is mushroom, 2 is flower, 3 is star
            case 1: {
                Mushroom* mushroom = new Mushroom(getX(), getY() + 8, getWorld());
                getWorld()->addToActors(mushroom);
                break;
            } case 2: {
                Flower* flower = new Flower(getX(), getY() + 8, getWorld());
                getWorld()->addToActors(flower);
                break;
            } case 3: {
                Star* star = new Star(getX(), getY() + 8, getWorld());
                getWorld()->addToActors(star);
                break;
            }
        }
        m_goodie = 0;
    }
}

//=================PIPE====================//

void Pipe::doSomething() {
    return;
}

void Pipe::bonk(Actor* actor) {
}

//==========================================//
//                CREATURES                 //
//==========================================//

bool Creature::blocksOthers() {
    return false;
}

bool Creature::isDamageable() {
    return true;
}

void Creature::damage() {}
void Creature::increaseAnimation(){}

void Creature::bonk(Actor* actor) {
    if(getWorld()->isPeach(actor)) {
        if(getWorld()->getPeachPower(3)) {
            getWorld()->playSound(SOUND_PLAYER_KICK);
            damage();
        }
    }
}

void Creature::creatureAction() {
    int nextX;
    if(getDirection() == 0) {
        nextX = getX() + 1;
        if(checkBlocking(nextX, getY()) || checkEdgeOverlap(nextX, getY())) {
            setDirection(180);
            return;
        }
    } else {
        nextX = getX() - 1;
        if(checkBlocking(nextX, getY()) || checkEdgeOverlap(nextX, getY())) {
            setDirection(0);
            return;
        }
    }
    moveTo(nextX, getY());
}

void Creature::doSomething() {
    if(!isAlive())
        return;
    if(checkPeachOverlap()) {
        getWorld()->bonkPeach();
        return;
    }
    
    creatureAction();
}

//=================GOOMBA====================//

void Goomba::damage() {
    getWorld()->increaseScore(100);
    setAlive(false);
}


//=================KOOPA====================//

void Koopa::damage() {
    getWorld()->increaseScore(100);
    setAlive(false);
    Shell* shell = new Shell(getX(), getY(), getWorld(), getDirection());
    getWorld()->addToActors(shell);
}


//=================PIRANHA====================//
void Piranha::creatureAction() {
    bool level = false;
    if(getWorld()->getPeachY() <  getY() * 1.5 && getWorld()->getPeachY() > getY() * 0.5) {
        level = true;
    }
    if(getWorld()->getPeachX() < getX())
        setDirection(180);
    else
        setDirection(0);
    
    if(fireDelay > 0) {
        fireDelay --;
        return;
    } else {
        int diff = getWorld()->getPeachX() - getX();
        int sign = (diff < 0)? -1 : 1;
        if(sign * diff < 8 * SPRITE_WIDTH && level) {
            Fireball* pFireball =  new Fireball(getX(), getY(), getWorld(), getDirection());
            getWorld()->addToActors(pFireball);
            getWorld()->playSound(SOUND_PIRANHA_FIRE);
            fireDelay = 40;
        }
    }
}
void Piranha::increaseAnimation(){
    increaseAnimationNumber();
}

void Piranha::damage() {
    getWorld()->increaseScore(100);
    setAlive(false);
}
//==========================================//
//                  ITEMS                   //
//==========================================//
void Item::doSomething() {
    if(target()) {
        return;
    }
    
    if(!checkBlocking(getX(), getY() - 1) || !checkBlocking(getX(), getY() - 2)) {
        moveTo(getX(), getY() - 2);
    }
    int nextX;
    if(getDirection() == 0) {
        nextX = getX() + 2;
        if(checkBlocking(nextX, getY())) {
            hitWall(180);
            return;
        }
    } else {
        nextX = getX() - 2;
        if(checkBlocking(nextX, getY())) {
            hitWall(0);
            return;
        }
    }
    moveTo(nextX, getY());
}

bool Item::target() {
    if(checkPeachOverlap()) {
        overlapped();
        setAlive(false);
        return true;
    }
    else
        return false;
}

//==========================================//
//                 GOODIES                  //
//==========================================//

bool Goodie::blocksOthers() {
    return false;
}
bool Goodie::isDamageable() {
    return false;
}

void Goodie::hitWall(int dir) {
    if(dir == 0)
        setDirection(0);
    else
        setDirection(180);
}

//================FLOWER===================//

void Flower::overlapped() {
    getWorld()->increaseScore(50);
    getWorld()->givePeachPower(2);
    getWorld()->peachSetTicks(2);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);

}

void Flower::bonk(Actor* actor) {
}

//===============MUSHROOM==================//

void Mushroom::overlapped() {
    getWorld()->increaseScore(75);
    getWorld()->givePeachPower(1);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);


}
void Mushroom::bonk(Actor* actor) {
    
}

//===============STAR==================//
void Star::overlapped() {
    getWorld()->increaseScore(100);
    getWorld()->givePeachPower(3);
    getWorld()->peachSetTicks(2);
    getWorld()->playSound(SOUND_PLAYER_POWERUP);

    
}
void Star::bonk(Actor* actor) {
    
}

//==========================================//
//               PROJECTILES                //
//==========================================//


bool Projectile::blocksOthers(){
    return false;
}
bool Projectile::isDamageable(){
    return false;
}
void Projectile::hitWall(int dir){
    setAlive(false);
}

//===============FIREBALL==================//
void Fireball::overlapped(){
    getWorld()->damagePeach();
}

void Fireball::bonk(Actor* actor) {
    
}

//=============PEACH FIREBALL================//

bool PeachFireball::target() {
    return damagePoint(getX(), getY());
}
void PeachFireball::overlapped() {
    
}
void PeachFireball::bonk(Actor* actor) {
    
}

//===============SHELL==================//
bool Shell::target() {
    return damagePoint(getX(), getY());
}

void Shell::overlapped(){
    
}

void Shell::bonk(Actor* actor) {
    
}

//==========================================//
//               LEVEL ENDER                //
//==========================================//


bool LevelEnder::blocksOthers() {
    return false;
}

bool LevelEnder::isDamageable() {
    return false;
}

void LevelEnder::doSomething() {
    if(!isAlive())
        return;
    if(checkPeachOverlap()) {
        getWorld()->increaseScore(1000);
        setAlive(false);
        getWorld()->levelDone();
    }
}

void LevelEnder::bonk(Actor* actor) {}

void Flag::levelOrWin() {
    getWorld()->levelDone();
}

void Mario::levelOrWin() {
    getWorld()->levelDone();
}
