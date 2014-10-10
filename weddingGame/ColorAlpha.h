/* 
 * File:   ColorAlpha.h
 * Author: marco
 *
 * Created on 16 July 2013, 15:33
 */

#ifndef COLORALPHA_H
#define	COLORALPHA_H

#include "Color.h"

class ColorAlpha :public Color{
public:
    ColorAlpha(int=0,int=0,int=0,int=128);
    ColorAlpha(const ColorAlpha& orig);
    virtual ~ColorAlpha();
    
    virtual int toInteger() const;
    
    inline virtual void setAlpha(int a){alpha = a;}
    inline virtual int getAlpha() const {return alpha;}
    
    bool operator!=(const ColorAlpha& right) const;
    bool operator==(const ColorAlpha& right) const { return !operator!=(right); }
    void operator=(const ColorAlpha& right);

private:

    int alpha;
    
};

#endif	/* COLORALPHA_H */

