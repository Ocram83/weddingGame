/*
    AllegroWrapper - A wrapper for the Allegro library (version 4)
    Copyright (C) 2013, Mario Alviano

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SPRITE_H
#define SPRITE_H

#include "Bitmap.h"
#include "Color.h"
#include "Drawable.h"
#include "Point.h"

#include <cassert>
#include <string>
#include <iostream>

using std::string;

template<class B>
class TSprite : public B, public Drawable {
public:
    TSprite(const string& filename, const Point& leftTopCorner = Point());
    TSprite(unsigned width, unsigned height, const Point& leftTopCorner = Point());
    TSprite(unsigned width, unsigned height, const Color& background, const Point& leftTopCorner = Point());
    explicit TSprite(const TSprite& init);
    virtual ~TSprite() {}

    const Point& getLeftTopCorner() const { return leftTopCorner; }
    void setLeftTopCorner(const Point& value) { leftTopCorner = value; }
    
    float getScaleWidth() const { return scaleWidth; }
    void setScaleWidth(float value);

    float getScaleHeight() const { return scaleHeight; }
    void setScaleHeight(float value);
    
    int getAngle() const { return angle; }
    void setAngle(int value);
    
    inline int getPivot() const { return pivot; }
    void setPivot(Point);
    
    virtual Drawable* clone() const { return new TSprite<B>(*this); }
    virtual void draw(BITMAP* bitmap);
    
protected:
    Point leftTopCorner;
    float scaleWidth;
    float scaleHeight;
    int angle;
    Point pivot;
};

typedef TSprite<Bitmap> Sprite;

template<class B>
TSprite<B>::TSprite(const string& filename, const Point& _leftTopCorner)
: B(filename), leftTopCorner(_leftTopCorner), scaleWidth(1.0), scaleHeight(1.0), angle(0), pivot(this->getWidth()/2, this->getHeight()/2) {
}

template<class B>
TSprite<B>::TSprite(unsigned width, unsigned height, const Point& _leftTopCorner)
: B(width, height), leftTopCorner(_leftTopCorner), scaleWidth(1.0), scaleHeight(1.0), angle(0), pivot(this->getWidth()/2, this->getHeight()/2) {
}

template<class B>
TSprite<B>::TSprite(unsigned width, unsigned height, const Color& background, const Point& _leftTopCorner)
: B(width, height, background), leftTopCorner(_leftTopCorner), scaleWidth(1.0), scaleHeight(1.0), angle(0), pivot(this->getWidth()/2, this->getHeight()/2) {
}

template<class B>
TSprite<B>::TSprite(const TSprite<B>& init)
: B(init), leftTopCorner(init.leftTopCorner), scaleWidth(init.scaleWidth), scaleHeight(init.scaleHeight), angle(init.angle), pivot(init.pivot) {
}

template<class B>
void TSprite<B>::setScaleWidth(float value) {
    assert(value > 0.0);
    scaleWidth = value;
}

template<class B>
void TSprite<B>::setScaleHeight(float value) {
    assert(value > 0.0);
    scaleHeight = value;
}

template<class B>
void TSprite<B>::setAngle(int value) {
    angle = value;
}

template<class B>
void TSprite<B>::setPivot(Point p) {
    pivot = p;
}

template<class B>
void TSprite<B>::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);
    
    if(this->getData() != NULL) { 
        BITMAP* buffer = create_bitmap(this->getWidth() * scaleWidth, this->getHeight() * scaleHeight);
        clear_to_color(buffer, Color(255,0,255).toInteger());
        stretch_sprite(buffer, this->getData(), 0, 0, this->getWidth() * scaleWidth, this->getHeight() * scaleHeight);
        pivot_sprite(bitmap, buffer, leftTopCorner.getX() + pivot.getX(), leftTopCorner.getY() + pivot.getY(), pivot.getX(), pivot.getY(), itofix(angle));
        destroy_bitmap(buffer);
    }
}

#endif

