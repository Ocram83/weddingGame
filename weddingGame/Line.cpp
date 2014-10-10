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

#include "Line.h"

#include <cassert>

Line::Line(const Point& a, const Point& b, const Color& _color)
: point1(a), point2(b), color(_color) {
}

Line::Line(int x1, int y1, int x2, int y2, const Color& _color)
: point1(x1,y1), point2(x2,y2), color(_color) {
}

void Line::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);
    
    line(bitmap, point1.getX(), point1.getY(), point2.getX(), point2.getY(), getColor().toInteger());
}
