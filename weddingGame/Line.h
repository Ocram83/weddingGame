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

#ifndef LINE_H
#define LINE_H

#include "Color.h"
#include "Drawable.h"
#include "Point.h"

class Line : public Drawable {
public:
    Line(const Point& point1 = Point(), const Point& point2 = Point(), const Color& color = Color());
    Line(int x1, int y1, int x2, int y2, const Color& color = Color());
    virtual ~Line() {}

    const Point& getPoint1() const { return point1; }
    const Point& getPoint2() const { return point2; }
    
    void setPoint1(const Point& value) { point1 = value; }
    void setPoint2(const Point& value) { point2 = value; }

    const Color& getColor() const { return color; }
    void setColor(const Color& value) { color = value; }
        
    virtual Drawable* clone() const { return new Line(*this); }
    virtual void draw(BITMAP* bitmap);
    
private:
    Point point1;
    Point point2;
    Color color;
};

#endif

