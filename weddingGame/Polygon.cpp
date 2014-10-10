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

#include "Polygon.h"

#include "Bitmap.h"
#include "Line.h"
#include <cassert>

Polygon::Polygon(const Color& _color, bool _filled)
: color(_color), filled(_filled) {

}

Point Polygon::getVertex(unsigned idx) const {
    assert(idx < vertices.size());
    return vertices[idx];
}

Polygon& Polygon::setVertex(unsigned idx, const Point& value) {
    assert(idx < vertices.size());
    vertices[idx] = value;
    return *this;
}

Polygon& Polygon::addVertex(const Point& value) {
    vertices.push_back(value);
    return *this;
}

Polygon& Polygon::removeVertex(unsigned idx) {
    assert(idx < vertices.size());
    vertices.erase(vertices.begin()+idx);
    return *this;
}

void Polygon::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);

    if(filled) {
        int verticesArray[vertices.size() * 2];
        for(unsigned i = 0; i < vertices.size(); ++i) {
            verticesArray[i*2] = vertices[i].getX();
            verticesArray[i*2+1] = vertices[i].getY();
        }
        polygon(bitmap, vertices.size(), verticesArray, getColor().toInteger());
    }
    else {
        assert(vertices.size() > 2);
        for(unsigned i = 0; i < vertices.size(); ++i) {
            Line line(vertices[i], vertices[(i+1) % vertices.size()], color);
            line.draw(bitmap);
        }
    }
}

