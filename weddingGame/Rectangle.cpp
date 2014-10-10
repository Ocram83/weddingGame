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

#include "Rectangle.h"

#include <cassert>

Rectangle::Rectangle(const Point& a, unsigned w, unsigned h, const Color& _color, bool _filled)
: leftTopCorner(a), width(w), height(h), color(_color), filled(_filled) {
}

Rectangle::Rectangle(int x, int y, unsigned w, unsigned h, const Color& _color, bool _filled)
: leftTopCorner(x,y), width(w), height(h), color(_color), filled(_filled) {
}

void Rectangle::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);
    
    if(filled)
        rectfill(bitmap, leftTopCorner.getX(), leftTopCorner.getY(), leftTopCorner.getX() + width, leftTopCorner.getY() + height, color.toInteger());
    else
        rect(bitmap, leftTopCorner.getX(), leftTopCorner.getY(), leftTopCorner.getX() + width, leftTopCorner.getY() + height, color.toInteger());
}
