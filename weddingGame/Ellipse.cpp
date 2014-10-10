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

#include "Ellipse.h"

#include <cassert>

Ellipse::Ellipse(const Point& _center, int _radiusX, int _radiusY, const Color& _color, bool _filled)
: center(_center), radiusX(_radiusX), radiusY(_radiusY), color(_color), filled(_filled) {
    assert(radiusX >= 0);
    assert(radiusY >= 0);
}

Ellipse::Ellipse(int x, int y, int _radiusX, int _radiusY, const Color& _color, bool _filled)
: center(x, y), radiusX(_radiusX), radiusY(_radiusY), color(_color), filled(_filled) {
}

void Ellipse::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);
    
    if(filled)
        ellipsefill(bitmap, center.getX(), center.getY(), radiusX, radiusY, getColor().toInteger());
    else
        ellipse(bitmap, center.getX(), center.getY(), radiusX, radiusY, getColor().toInteger());
}

Ellipse& Ellipse::incrementCenterX(int value) {
    center.incrementX(value);
    return *this;
}

Ellipse& Ellipse::incrementCenterY(int value) {
    center.incrementY(value);
    return *this;
}

Ellipse& Ellipse::incrementRadiusX(int value) {
    setRadiusX(radiusX + value);
    return *this;
}

Ellipse& Ellipse::incrementRadiusY(int value) {
    setRadiusY(radiusY + value);
    return *this;
}

