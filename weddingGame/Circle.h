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

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Ellipse.h"

class Circle : public Ellipse {
public:
    Circle(const Point& center = Point(), int radius = 0, const Color& color = Color(), bool filled = false);
    Circle(int x, int y, int radius = 0, const Color& color = Color(), bool filled = false);
    virtual ~Circle() {}

    int getRadius() const { return getRadiusX(); }
    void setRadius(int value) { Ellipse::setRadiusX(value); Ellipse::setRadiusY(value); }
    
    Circle& incrementRadius(int value) { return static_cast<Circle&>(incrementRadiusX(value).incrementRadiusY(value)); }
    
    virtual void setRadiusX(int value) { setRadius(value); }
    virtual void setRadiusY(int value) { setRadius(value); }
};

#endif

