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

#ifndef PIXEL_H
#define PIXEL_H

#include "Color.h"
#include "Drawable.h"
#include "Point.h"

#include <allegro.h>

class Pixel : public Point, public Drawable {
public:
    Pixel(const Point& point, Color color = Color());
    Pixel(int x = 0, int y = 0, Color color = Color());
    virtual ~Pixel();
    
    const Color& getColor() const { return color; }
    void setColor(const Color& value) { color = value; }
    
    virtual Drawable* clone() const { return new Pixel(*this); }
    virtual void draw(BITMAP* bitmap);
    
private:
    Color color;
};

#endif

