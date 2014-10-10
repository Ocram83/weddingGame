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

#ifndef POLYGON_H
#define POLYGON_H

#include "Color.h"
#include "Drawable.h"
#include "Point.h"
#include <vector>

using std::vector;

class Polygon : public Drawable {
public:
    Polygon(const Color& color = Color(), bool filled = false);
    virtual ~Polygon() {}
    
    Point getVertex(unsigned idx) const;
    Polygon& setVertex(unsigned idx, const Point& value);
    
    Polygon& addVertex(const Point& value);
    Polygon& addVertex(int x, int y) { return addVertex(Point(x,y)); }
    Polygon& removeVertex(unsigned idx);

    const Color& getColor() const { return color; }
    void setColor(const Color& value) { color = value; }
    
    bool isFilled() const { return filled; }
    void setFilled(bool value) { filled = value; }

    virtual Drawable* clone() const { return new Polygon(*this); }
    virtual void draw(BITMAP* bitmap);
    
private:
    vector<Point> vertices;
    Color color;
    bool filled;
};

#endif

