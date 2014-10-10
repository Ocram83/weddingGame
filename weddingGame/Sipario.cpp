/* 
 * File:   Sipario.cpp
 * Author: marco
 * 
 * Created on 16 July 2013, 17:56
 */

#include <cassert>

#include "Sipario.h"

Sipario::Sipario(const Point& a, unsigned w, unsigned h, const ColorAlpha& _color)
: leftTopCorner(a), width(w), height(h), color(_color){
}

Sipario::Sipario(int x, int y, unsigned width, unsigned height, const ColorAlpha& _color) 
:leftTopCorner(x,y), width(width), height(height), color(_color)
{
}

Sipario::~Sipario() {
}

void Sipario::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);

    rectfill(bitmap, leftTopCorner.getX(), leftTopCorner.getY(), leftTopCorner.getX() + width, leftTopCorner.getY() + height, color.toInteger());
}
