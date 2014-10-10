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

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Color.h"
#include "Drawable.h"
#include "Point.h"

#include <allegro.h>

class Rectangle : public Drawable {
public:
    Rectangle(const Point& leftTopCorner = Point(), unsigned width = 0, unsigned height = 0, const Color& color = Color(), bool filled = false);
    Rectangle(int x, int y, unsigned width, unsigned height, const Color& color = Color(), bool filled = false);
    virtual ~Rectangle() {}
    
    const Point& getLeftTopCorner() const { return leftTopCorner; }
    void setLeftTopCorner(const Point& value) { leftTopCorner = value; }
    
    unsigned getWidth() const { return width; }
    void setWidth(unsigned value) { width = value; }
    
    unsigned getHeight() const { return height; }
    void setHeight(unsigned value) { height = value; }
    
    const Color& getColor() const { return color; }
    void setColor(const Color& value) { color = value; }
    
    bool isFilled() const { return filled; }
    void setFilled(bool value) { filled = value; }

    virtual Drawable* clone() const { return new Rectangle(*this); }
    virtual void draw(BITMAP* bitmap);
    
private:
    Point leftTopCorner;
    unsigned width;
    unsigned height;
    Color color;
    bool filled;
};

#endif

