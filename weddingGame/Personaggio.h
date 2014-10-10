/* 
 * File:   Nemico.h
 * Author: marco
 *
 * Created on 10 June 2013, 12:29
 */

#ifndef PERSONAGGIO_H
#define	PERSONAGGIO_H

#include "Munizione.h"
#include "CompositeSprite.h"
#include "SampleSound.h"


class MyAllegro;

enum OrizontalMovement{NONE,MOVING_RIGHT, MOVING_LEFT};
enum VerticalMovement{ONGROUND,JUMPING, FALLING, LOWER};
enum Action { IDLE, SHOOTING };
enum SpritePosition{REST,LEFT,RIGHT,DOWN};
enum SoundType{THROW,JUMP,HIT};

class Personaggio: public CompositeSprite {
public:
    Personaggio(MyAllegro*, unsigned, unsigned, const char*, unsigned, Direzione, unsigned);
    Personaggio(const Personaggio& orig);
    virtual ~Personaggio();
    virtual void salta();
    virtual void vaiADestra() = 0;
    virtual void vaiASinistra() = 0;
    virtual void abbassati();
    virtual void spara() = 0;
    virtual void colpito();
    
    inline const char* getName() const {return name;}
    inline void setX(int x){positionX=x;}
    inline int getX() const {return positionX;}
    
    inline void setY(int y){positionY=y;}
    inline int getY() const {return positionY;}
    
    inline void setRealWidth(int x) {realWidth=x;}
    inline int getRealWidth()const{return realWidth;}
    
    inline void setRealHeight(int y) {realHeight=y;}
    inline int getRealHeight()const{return realHeight;}
    
    inline bool isFalling()const {return verticalMovement == FALLING;}
    
    inline bool isJumping()const {return verticalMovement == JUMPING;}
    
    inline bool isIdle()const {return action == IDLE && verticalMovement == ONGROUND && orizontalMovement == NONE;}
    
    inline bool isOnGround()const {return true;}
    
    void setIdle();
    
    inline void setAction(Action a){action = a;}

    inline int getIncrement(){return increment;}
    
    inline MyAllegro* getEnvironment()const {return environment;}
    
    inline  const int getFirePositionX()const {return firePositionX;}

    inline  const int getFirePositionY()const {return firePositionY;}
    
    inline const unsigned getEnergy(){return energy;}
    
    inline void setEnergy(unsigned e){energy=e;}

    
    bool canMoveRight() const;

    bool canMoveLeft() const;
    
    virtual bool alive() const {return energy>0;};

    
protected:
    
    const char* name;
    
    Sprite base;
    Sprite throwLeft;
    Sprite throwRigth;
    Sprite down;
    
    OrizontalMovement orizontalMovement;
    VerticalMovement verticalMovement;
    Action action;
    
    MyAllegro *environment;
    
    int realHeight;
    int realWidth;
    
    int positionX;
    int positionY;
    
    int angle;
    int maxAngle;
       
    int increment;
    
    int firePositionX;
    int firePositionY;
    
    unsigned shootingPause;
    unsigned lastShoot;
    
    unsigned ticks;
    
    Direzione direzione;
    
    unsigned energy;
    
 //   SampleSound throwSound;
   // SampleSound hitSound;
    

    string imageName(const char*,SpritePosition);
    string soundName(SoundType);

};

#endif	/* PERSONAGGIO_H */

