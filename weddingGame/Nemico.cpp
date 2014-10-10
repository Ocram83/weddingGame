/* 
 * File:   Character.cpp
 * Author: marco
 * 
 * Created on 08 June 2013, 17:31
 */

#include "Nemico.h"
#include "MyAllegro.h"

#include <sstream>
#include <iostream>

using namespace std;

int Nemico::characterNum = 0;

Nemico::Nemico(MyAllegro* e, int width , int height, const char* name, int startX, Direzione d, unsigned energy, const char* mun)
        :Personaggio(e, width, height, name, startX, d, energy),
        jumpingProbability(4),
        movingProbability(3),
        shootingProbability(20),
        maxHorizontalSpeed(10),
        munizione(mun)

{
    c = ++characterNum;
    shootingPause=100;

}
Nemico::Nemico(MyAllegro* e, int width , int height, const char* name, int startX, Direzione d, unsigned energy, unsigned jprob, unsigned movProb, unsigned shootProb,unsigned maxHSpeed, const char* mun)
        :Personaggio(e, width, height, name, startX, d, energy),
        jumpingProbability(jprob),
        movingProbability(movProb),
        shootingProbability(shootProb),
        maxHorizontalSpeed(maxHSpeed),
        munizione(mun)

{
    c = ++characterNum;
    shootingPause=100;
}


Nemico::Nemico(const Nemico& orig)
        :Personaggio(orig.getEnvironment(), orig.getWidth(), orig.getHeight(), orig.getName(), orig.getX(), orig.direzione, orig.energy),
        jumpingProbability(orig.jumpingProbability),
        movingProbability(orig.movingProbability),
        shootingProbability(orig.shootingProbability),
        maxHorizontalSpeed(orig.maxHorizontalSpeed),
        munizione(orig.munizione)
{
        shootingPause=100;
}

Nemico::~Nemico() {
}

void Nemico::vaiADestra()
{
    if(!canMoveRight())
    {

        orizontalMovement = NONE;
        return;
    }
    int random = rand() % maxHorizontalSpeed;
    
    if(random == 0)
    {
       orizontalMovement = NONE;
    }
    else
    {
        positionX+=random;
        setLeftTopCorner(Point(positionX,positionY));
                 
        angle = 0;

        if(verticalMovement == ONGROUND)
        {

            if(random%2==0)
                angle+= random%maxAngle;
            else
                angle-= random%maxAngle;

            setAngle(angle);
        }
    }
}

void Nemico::vaiASinistra()
{
    if(!canMoveLeft())
    {
        orizontalMovement = NONE;
        return;
    }
    
    int random = rand() % maxHorizontalSpeed;
    
    if(random == 0)
    {
        orizontalMovement = NONE;
    }
    else
    {
        positionX-=random;
        setLeftTopCorner(Point(positionX,positionY));
        
        angle = 0;

        if(verticalMovement == ONGROUND)
        {
            if(random%2==0)
                angle+= random%maxAngle;
            else
                angle-= random%maxAngle;

            setAngle(angle);
        }
    }
}

void Nemico::spara()
{

   // throwSound.play();

     if(environment->getEroe()->getX()>positionX)
        direzione=DESTRA;
    else
        direzione = SINISTRA;
        
    Personaggio** enemies= new Personaggio*[1];
    
    enemies[0]= environment->getEroe();
    
    lastShoot = ticks;
    environment->getBulletLayer().add(Munizione(this,enemies,1,4,LIGHT,direzione,FAST,munizione));
    action = IDLE;
   
    clear();
    if(direzione == DESTRA)
        add(throwRigth);
    else if(direzione == SINISTRA)
        add(throwLeft);
}

void Nemico::onTick()
{
    
    if( ++ticks % environment->getSpeed() == 0)
    {   
        int random=0;
        
        if(ticks == lastShoot +environment->getSpeed())
        {
            clear();
            add(base);
        }
        
       // cout << "ciao"<<endl;
        if(verticalMovement == ONGROUND)
        {
            random = rand() % jumpingProbability; 
            
            if(random==0)
                verticalMovement = JUMPING;
            
        }
        
        if(orizontalMovement == NONE)
        {
            random = rand() % movingProbability;
            
            switch(random)
            {
                case 0:
                    orizontalMovement = NONE;
                    break;
                case 1:
                    orizontalMovement = MOVING_RIGHT;
                    break;
                case 2:
                    orizontalMovement = MOVING_LEFT;
                    break;
                default:
                    break;
            }
        }
        if(action == IDLE && ticks > lastShoot +shootingPause)
        {
            random = rand() % shootingProbability; 
            
            if(random==0)
                action = SHOOTING;
        }
        
       if(verticalMovement == JUMPING || verticalMovement == FALLING)
                salta();
       
        if(orizontalMovement == MOVING_RIGHT)
            vaiADestra();
        else if(orizontalMovement == MOVING_LEFT)
            vaiASinistra();
        
        if(action == SHOOTING)
            spara();
              
        }
    
    //Animazioni
     /*   if(direzione == DESTRA && ticks == lastShoot +environment->getSpeed()/2)
        {
            clear();
            stringstream ss;
            ss << name << "ThrowRight2.bmp";
            add(Sprite(ss.str()));
        }
       */
    }
    


