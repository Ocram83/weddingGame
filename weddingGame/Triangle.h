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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Color.h"
#include "Drawable.h"
#include "Point.h"

#include <allegro.h>

class Triangle : public Drawable {
public:
    Triangle(const Point& a = Point(), const Point& b = Point(), const Point& c = Point(), const Color& color = Color(), bool filled = false);
    virtual ~Triangle() {}
    
    const Point& getVertex1() const { return vertex1; }
    const Point& getVertex2() const { return vertex2; }
    const Point& getVertex3() const { return vertex3; }
    
    void setVertex1(const Point& value) { vertex1 = value; }
    void setVertex2(const Point& value) { vertex2 = value; }
    void setVertex3(const Point& value) { vertex3 = value; }
    
    const Color& getColor() const { return color; }
    void setColor(const Color& value) { color = value; }
    
    bool isFilled() const { return filled; }
    void setFilled(bool value) { filled = value; }

    virtual Drawable* clone() const { return new Triangle(*this); }
    virtual void draw(BITMAP* bitmap);
    
private:
    Point vertex1;
    Point vertex2;
    Point vertex3;
    Color color;
    bool filled;
};

#endif

