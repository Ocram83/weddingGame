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

#include "Triangle.h"

#include "Line.h"
#include <cassert>

Triangle::Triangle(const Point& a, const Point& b, const Point& c, const Color& _color, bool _filled)
: vertex1(a), vertex2(b), vertex3(c), color(_color), filled(_filled) {
}

void Triangle::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);
    
    if(filled)
        triangle(bitmap, vertex1.getX(), vertex1.getY(), vertex2.getX(), vertex2.getY(), vertex3.getX(), vertex3.getY(), color.toInteger());
    else {
        Line line(vertex1, vertex2, color);
        line.draw(bitmap);
        line.setPoint2(vertex3);
        line.draw(bitmap);
        line.setPoint1(vertex2);
        line.draw(bitmap);
    }
}

