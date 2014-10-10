/* 
 * File:   ColorAlpha.cpp
 * Author: marco
 * 
 * Created on 16 July 2013, 15:33
 */

#include "ColorAlpha.h"
#include <iostream>

using namespace std;

ColorAlpha::ColorAlpha(int r, int g, int b, int a )
        : Color(r,g,b),
        alpha(a)
        {
}

ColorAlpha::ColorAlpha(const ColorAlpha& orig) {
    Color(orig.red,orig.green,orig.blue);
    
    alpha = orig.alpha;
}

ColorAlpha::~ColorAlpha() {
}

int ColorAlpha::toInteger() const
{
    return makeacol(getRed(), getGreen(), getBlue(), alpha);
}

bool ColorAlpha::operator!=(const ColorAlpha& right) const {
    return red != right.red || green != right.green || blue != right.blue || alpha != right.alpha;
}

void ColorAlpha::operator=(const ColorAlpha& right)  {
    setRed(right.red);
    setGreen(right.green);
    setBlue(right.blue);
    alpha = right.alpha;
}