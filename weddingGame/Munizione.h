/* 
 * File:   Munizione.h
 * Author: marco
 *
 * Created on 11 June 2013, 15:32
 */

#ifndef MUNIZIONE_H
#define	MUNIZIONE_H
#include "Sprite.h"

enum Peso {LIGHT, MEDIUM, HEAVY};
enum Direzione {DESTRA, SINISTRA};
enum VelocitaRotazione{STILL=0,SLOW=1,MODERATE=2,FAST=4};

class Personaggio;

class Munizione:public Sprite {
public:
    Munizione(Personaggio*, Personaggio**, const unsigned, unsigned, Peso, Direzione, VelocitaRotazione, const char*);
    Munizione(const Munizione& orig);
    virtual ~Munizione();
    
    virtual bool checkColpito();
    
    virtual void onTick();
    virtual bool alive() const;
    virtual Drawable* clone() const { return new Munizione(*this); }
private:
    
    bool checkColpito(Personaggio*);

    Personaggio* proprietario;
    Personaggio** bersagli;
    int bersagliSize;
    
    unsigned velocita;
    int posizioneX;
    int posizioneY;
    unsigned incrementoY;
    int angle;
    
    bool hit;
    
    Peso peso;
    Direzione direzione;
    VelocitaRotazione velocitaRotazione;
    
    const char* nome;
    
    unsigned tick;
};

#endif	/* MUNIZIONE_H */

