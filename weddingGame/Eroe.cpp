/* 
 * File:   Eroe.cpp
 * Author: marco
 * 
 * Created on 10 June 2013, 16:41
 */

#include "Eroe.h"
#include "MyAllegro.h"
#include "Keyboard.h"
#include <iostream>
#include <sstream>

using namespace std;

Eroe::Eroe(MyAllegro* e, int width , int height, const char* name, int startX, Direzione d, unsigned energy)
        :Personaggio(e, width, height, name, startX, d, energy),
        horizontal_speed(7)
{   
  
    shootingPause =100;
    
}

Eroe::Eroe(const Eroe& orig)
        :Personaggio(orig.getEnvironment(), orig.getWidth(), orig.getHeight(), orig.getName(), orig.getX(), orig.direzione, orig.energy),
        horizontal_speed(10){
}

Eroe::~Eroe() {
}


void Eroe::vaiADestra()
{
    if(!canMoveRight())
    {
        orizontalMovement = NONE;
        return;
    }
    
    positionX+=horizontal_speed;
        
    setLeftTopCorner(Point(positionX,positionY));
        
    angle = 0;
    
    if(verticalMovement == ONGROUND)
    {
        unsigned random = rand() % 10;
        
        if(random%2==0)
            angle+= random%maxAngle;
        else
            angle-= random%maxAngle;

        setAngle(angle);
    } 
    orizontalMovement = NONE;   
}

void Eroe::vaiASinistra()
{
    
    if(!canMoveLeft())
    {
        orizontalMovement = NONE;
        return;
    }
    
    positionX-=horizontal_speed;
    
    setLeftTopCorner(Point(positionX,positionY));

    angle = 0;

    if(verticalMovement == ONGROUND)
    {
        unsigned random = rand() % 10;

        if(random%2==0)
            angle+= random%maxAngle;
        else
            angle-= random%maxAngle;

        setAngle(angle);
    }
   orizontalMovement = NONE;

   
}

void Eroe::abbassati()
{
    clear();
    stringstream ss;
    ss << name << "Down.bmp";
    add(Sprite(ss.str()));   
}

void Eroe::spara()
{
    if(environment->getFirstAliveEnemy()->getX()>positionX)
        direzione=DESTRA;
    else
        direzione = SINISTRA;
               
    environment->getBulletLayer().add(Munizione(this,  environment->getAliveAndActiveEnemies(), environment->getNumOfAliveEnemies(), 5, LIGHT, direzione, FAST, "cuore.bmp"));

    action = IDLE;
    lastShoot = ticks;
    
    clear();
     if(direzione == DESTRA)
        add(throwRigth);
    else
        add(throwLeft);

}

void Eroe::onTick()
{
    if( ++ticks % environment->getSpeed() == 0)
    {
        if(ticks > lastShoot +30)
        {
            clear();
            add(base);
        }
        
        const Keyboard* k = &(environment->getKeyboard());

        if(verticalMovement == ONGROUND && k->isKeyPressed(KEY_UP))
        {
            verticalMovement = JUMPING;
        }
        if(verticalMovement == ONGROUND && k->isKeyPressed(KEY_DOWN))
        {
            abbassati();
        }
        if (orizontalMovement == NONE && k->isKeyPressed(KEY_RIGHT))
        {
            orizontalMovement = MOVING_RIGHT;
        }
        if (orizontalMovement == NONE && k->isKeyPressed(KEY_LEFT))
        {
            orizontalMovement = MOVING_LEFT;
        }

        if(action == IDLE && k->isKeyPressed(KEY_SPACE) && (ticks > lastShoot +shootingPause || (ticks <= shootingPause && lastShoot==0 )))
        {
            action = SHOOTING;
            spara();       
        }
        
        if(verticalMovement == JUMPING || verticalMovement == FALLING)
            salta();
        
        if(orizontalMovement == MOVING_RIGHT)
            vaiADestra();
        else if(orizontalMovement == MOVING_LEFT)
            vaiASinistra();
        
    }

}