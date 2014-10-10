/* 
 * File:   Eroe.h
 * Author: marco
 *
 * Created on 10 June 2013, 16:41
 */

#ifndef EROE_H
#define	EROE_H
#include "Personaggio.h"

class Eroe:public Personaggio {
public:
    Eroe(MyAllegro*, int , int, const char*, int, Direzione, unsigned);
    Eroe(const Eroe& orig);
    virtual ~Eroe();
    
    //virtual void salta();
    virtual void vaiADestra();
    virtual void vaiASinistra();
    virtual void spara();
    virtual void abbassati();
    
    virtual void onTick();
private:

    const unsigned horizontal_speed;
};

#endif	/* EROE_H */

