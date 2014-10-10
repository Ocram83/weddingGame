/* 
 * File:   Munizione.cpp
 * Author: marco
 * 
 * Created on 11 June 2013, 15:32
 */

#include "Munizione.h"
#include "Allegro.h"
#include "MyAllegro.h"
#include "Personaggio.h"
#include "Nemico.h"

#include <math.h>


Munizione::Munizione(Personaggio* p, Personaggio** en, const unsigned enSize, unsigned v, Peso pe, Direzione d,VelocitaRotazione vr,const char* n)
        :Sprite(n,Point(p->getX()+ p->getFirePositionX(), p->getY() + p->getFirePositionY())), 
        proprietario(p),
        bersagli(en),
        bersagliSize(enSize),
        velocita(v),
        posizioneX(p->getX()+ p->getFirePositionX()),
        posizioneY(p->getY() + p->getFirePositionY()),
        angle(0),
        hit(true),
        peso(pe),
        direzione(d),
        velocitaRotazione(vr),
        nome(n),
        tick(0)
    {
    
        switch(peso)
            {
                case HEAVY:
                    incrementoY = 1;
                    break;
                case MEDIUM:
                    incrementoY = 2;
                break;
                case LIGHT:
                    incrementoY = 3;
                break;
                default:
                    break;
            }
        
        //Uno strano baco mi impedisce di inizializzare la posizione utilizzando
        //la width e la height della immagine nella lista di inizializzazione
        posizioneX+= getWidth()/2;
        posizioneY+=getHeight()/2;
        
        setLeftTopCorner(Point(posizioneX,posizioneY));
    }

Munizione::Munizione(const Munizione& orig)
        :Sprite(orig.nome,Point(orig.posizioneX, orig.posizioneY)), 
        proprietario(orig.proprietario),
        bersagli(orig.bersagli),
        bersagliSize(orig.bersagliSize),
        velocita(orig.velocita),
        posizioneX(orig.posizioneX),
        posizioneY(orig.posizioneY),
        angle(orig.angle),
        hit(true),
        peso(orig.peso),
        direzione(orig.direzione),
        velocitaRotazione(orig.velocitaRotazione),
        nome(orig.nome),
        tick(orig.tick){
}

Munizione::~Munizione() {
}


//La gestione delle collisioni considera l'oggetto assimilabile ad un cerchio
//Quando la munizione entra all'interno della sprite bersaglio controllo che il colore di uno dei quattro punti
// agli estremi del diametro (perpendicolari agli assi X e Y) dell'ipotetico cerchio rappresentato dalla munizione
//siano trasparenti. Se così non è il bersaglio è stato colpito
bool Munizione::checkColpito()
{                  
    for(int i = 0; i< bersagliSize;i++)
    {   
        //cout <<" -->" <<bersagli[i]->getName()<< "size: "<<bersagliSize <<endl;

        if(checkColpito(bersagli[i]))
            return true;    
    }
    
    //Non ci sono state collisioni
    return false;
}

bool Munizione::checkColpito(Personaggio* bersaglio)
{
    //cout << bersagli[0]->getName() << " - "<< bersagliSize<<endl;
    //cout << bersaglio->getName() <<endl;
    MyAllegro* m =dynamic_cast<MyAllegro*>(MyAllegro::getInstance());
     
    if(direzione == SINISTRA)
    {
        if(posizioneX -getWidth()/2 <= bersaglio->getX()+bersaglio->getRealWidth() && posizioneX + getWidth()/2 > bersaglio->getX())
        {
            if(posizioneY+getHeight()/2 < bersaglio->getY())
                    return false;
            else if(posizioneY -getHeight()/2 > bersaglio->getY() + bersaglio->getRealHeight())
            {
                return false;
            }
            else 
            {     

                if(m->getPlayerLayer().getPixel( posizioneX - getWidth()/2, posizioneY) != Color(255,0,255) ||
                        m->getPlayerLayer().getPixel(posizioneX + getWidth()/2, posizioneY) != Color(255,0,255) ||
                                m->getPlayerLayer().getPixel(posizioneX,posizioneY-getHeight()/2) != Color(255,0,255) ||
                                        m->getPlayerLayer().getPixel(posizioneX,posizioneY+getHeight()/2) != Color(255,0,255))
                {

                  //  m->getPlayerLayer().add(Rectangle(Point(posizioneX - getWidth()/2,posizioneY),20, 20, Color(255,0,0), false));
                    bersaglio->colpito();
                    return true;
                }
            }   
        }
    }

    if(direzione == DESTRA)
    {        
        if(posizioneX >= bersaglio->getX() && posizioneX < bersaglio->getX()+bersaglio->getRealWidth())
        {
            if(posizioneY+getHeight() < bersaglio->getY())
                    return false;
            else if(posizioneY > bersaglio->getY() + bersaglio->getRealHeight())
            {
                return false;
            }
            else 
            {
                 if(m->getPlayerLayer().getPixel( posizioneX - getWidth()/2, posizioneY) != Color(255,0,255) ||
                        m->getPlayerLayer().getPixel(posizioneX + getWidth()/2, posizioneY) != Color(255,0,255) ||
                                m->getPlayerLayer().getPixel(posizioneX,posizioneY-getHeight()/2) != Color(255,0,255) ||
                                        m->getPlayerLayer().getPixel(posizioneX,posizioneY+getHeight()/2) != Color(255,0,255))
                 {
                     bersaglio->colpito();
                     return true;
                 }
            }   
        }
    }
    
    return false;
}


bool Munizione::alive() const
{
    if(!hit)
        return false;
    
    MyAllegro* m =dynamic_cast<MyAllegro*>(MyAllegro::getInstance());
    if(direzione == DESTRA && (posizioneX>=m->getWinWidth()))
        return false;
    
    return true;
}


void Munizione::onTick()
{
    MyAllegro* m =dynamic_cast<MyAllegro*>(MyAllegro::getInstance());
    if(tick%m->getSpeed()==0)
    {
         if(checkColpito())
        {
            hit=false;
        }
         else
         {
            if(direzione == DESTRA)
                posizioneX+=velocita;
            else
                posizioneX-=velocita;

            angle += velocitaRotazione;
            

            setLeftTopCorner(Point(posizioneX-getWidth()/2,posizioneY-getHeight()/2));

            setAngle(angle);
         }
    }
}