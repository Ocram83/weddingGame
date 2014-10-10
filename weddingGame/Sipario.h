/* 
 * File:   Sipario.h
 * Author: marco
 *
 * Created on 16 July 2013, 17:56
 */

#ifndef SIPARIO_H
#define	SIPARIO_H

#include "ColorAlpha.h"
#include "Drawable.h"
#include "Point.h"

#include <allegro.h>

#include <iostream>
using namespace std;

class Sipario:public Drawable {
public:
    Sipario(const Point& leftTopCorner = Point(), unsigned width = 0, unsigned height = 0, const ColorAlpha& color = ColorAlpha());
    Sipario(int x, int y, unsigned width, unsigned height, const ColorAlpha& color = ColorAlpha());
    virtual ~Sipario();
            
    const Point& getLeftTopCorner() const { return leftTopCorner; }
    void setLeftTopCorner(const Point& value) { leftTopCorner = value; }
    
    unsigned getWidth() const { return width; }
    void setWidth(unsigned value) { width = value; }
    
    unsigned getHeight() const { return height; }
    void setHeight(unsigned value) { height = value; }
    
    ColorAlpha& getColor() { return color; }
    void setColor(ColorAlpha value) { color = value; }
    
    
    virtual Drawable* clone() const {return new Sipario(*this); }
    virtual void draw(BITMAP* bitmap);
    
private:
    Point leftTopCorner;
    unsigned width;
    unsigned height;
    ColorAlpha color;
};

#endif	/* SIPARIO_H */

