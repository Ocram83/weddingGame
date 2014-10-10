/* 
 * File:   Character.h
 * Author: marco
 *
 * Created on 08 June 2013, 17:31
 */

#ifndef NEMICO_H
#define	NEMICO_H

#include "Personaggio.h"

class Nemico: public Personaggio {
public:
    Nemico(const Nemico& orig);
    Nemico(MyAllegro*, int , int, const char*, int, Direzione, unsigned,const char*);
    Nemico(MyAllegro*, int , int, const char*, int, Direzione, unsigned, unsigned, unsigned, unsigned, unsigned, const char*);
    virtual ~Nemico();
    
    //virtual void salta();
    virtual void vaiADestra();
    virtual void vaiASinistra();
    virtual void spara();

    virtual void onTick();
    
    inline const char* getMunizioneName(){return munizione;}

private:
   
    const unsigned jumpingProbability;
    const unsigned movingProbability;
    const unsigned shootingProbability;
    const unsigned maxHorizontalSpeed;

    static int characterNum;
    int c;
    
    const char* munizione;
    

};

#endif	/* NEMICO_H */

