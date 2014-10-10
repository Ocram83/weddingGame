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

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Color.h"
#include "Drawable.h"
#include "Point.h"

#include <allegro.h>

class Ellipse : public Drawable {
public:
    Ellipse(const Point& center = Point(), int radiusX = 0, int radiusY = 0, const Color& color = Color(), bool filled = false);
    Ellipse(int x, int y, int radiusX = 0, int radiusY = 0, const Color& color = Color(), bool filled = false);
    virtual ~Ellipse() {}

    const Point& getCenter() const { return center; }
    void setCenter(const Point& value) { center = value; }

    int getRadiusX() const { return radiusX; }
    virtual void setRadiusX(int value) { radiusX = value >= 0 ? value : 0; }

    int getRadiusY() const { return radiusY; }
    virtual void setRadiusY(int value) { radiusY = value >= 0 ? value : 0; }
    
    Ellipse& incrementCenterX(int value);
    Ellipse& incrementCenterY(int value);
    Ellipse& incrementRadiusX(int value);
    Ellipse& incrementRadiusY(int value);
    
    const Color& getColor() const { return color; }
    void setColor(const Color& value) { color = value; }
    
    bool isFilled() const { return filled; }
    void setFilled(bool value) { filled = value; }
    
    virtual Drawable* clone() const { return new Ellipse(*this); }
    virtual void draw(BITMAP* bitmap);
    
private:
    Point center;
    int radiusX;
    int radiusY;
    Color color;
    bool filled;
};

#endif

