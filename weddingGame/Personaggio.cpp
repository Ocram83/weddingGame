#include "Personaggio.h"
#include "MyAllegro.h"

#include <sstream>



Personaggio::Personaggio(MyAllegro* e, unsigned width , unsigned height, const char* n, unsigned startX, Direzione d, unsigned energy)
        :CompositeSprite(imageName(n,REST), Point(startX,e->getb_height()-height)), 
        name(n),
        base(imageName(n,REST)),
        throwLeft(imageName(n,LEFT)),
        throwRigth(imageName(n,RIGHT)),
        down(imageName(n,DOWN)),
        orizontalMovement(NONE),
        verticalMovement(ONGROUND),
        action(IDLE),
        environment(e),
        realHeight(height),
        realWidth(width),
        positionX(startX),
        positionY(e->getb_height()-height),
        angle(0),
        maxAngle(3),
        increment(26),
        firePositionX(width/2-20),
        firePositionY(height/2),
        shootingPause(500),
        lastShoot(0),
        ticks(0),
        direzione(d),
        energy(energy)/*,
        throwSound(soundName(THROW)),
        hitSound(soundName(HIT))*/
        {
    
        setScaleHeight((float)realHeight/getHeight());
        setScaleWidth((float)realWidth/getWidth());
   /*
        throwSound.setLoop(false);
        throwSound.setVolume(40);
        hitSound.setLoop(false);
        hitSound.setVolume(40);
        */
        //environment->getBackgroundLayer().add(Rectangle(Point(positionX,positionY),getRealWidth(), getRealHeight(), Color(255,0,0), false));
}

Personaggio::~Personaggio(){};

string Personaggio::imageName(const char* n, SpritePosition sp)
{
    stringstream ss;
    /*
    switch(sp)
    {
        case REST:
            ss<<n  << ".bmp";
            break;
        case LEFT:
            ss << name << "ThrowLeft.bmp";
            break;
        case RIGHT:
            ss << name << "ThrowRight.bmp";
            break;
        case DOWN:
            ss << name << "Down.bmp";
            break;
        default:
             ss<<n  << ".bmp";
            break;      
    }
    */
    ss<<n  << ".bmp";
    return ss.str();
}

string Personaggio::soundName(SoundType st)
{
    stringstream ss;
    
    switch(st)
    {
        case THROW:
            ss<<name<<"Throw.wav";
            break;
        case HIT:
            ss<<"pain.wav";
            break;
        default:
            break;
                  
    }
    cout<<ss.str()<<endl;
    return ss.str();
}


bool Personaggio::canMoveRight() const {return(positionX+realWidth)<environment->getWinWidth();}

bool Personaggio::canMoveLeft() const {return positionX > 0;}

void Personaggio::salta()
{
    
    int feetPosition = getY()+getRealHeight();

    if(verticalMovement == JUMPING && increment==0)
    {    
        verticalMovement = FALLING;
    }
    if(verticalMovement == FALLING && feetPosition > environment->getb_height() -increment )
    {

        positionY=environment->getb_height()-getRealHeight();
        verticalMovement = ONGROUND;
    }
    
    if(verticalMovement == JUMPING )
    {
        increment-=2;
        
        if(increment<0)
            increment=0;
        else
            positionY-=increment;
    }

    if(verticalMovement == FALLING )
    {
        positionY+=increment;  
        increment+=2;

    }
   
    setLeftTopCorner(Point(positionX,positionY));
}

void Personaggio::abbassati()
{
    
}

void Personaggio::colpito()
{
   // hitSound.play();
    energy--;
}

void Personaggio::setIdle()
{
    action = IDLE;
    verticalMovement = ONGROUND;
    orizontalMovement = NONE;
   
}