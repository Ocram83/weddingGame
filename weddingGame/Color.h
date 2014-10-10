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

#ifndef COLOR_H
#define COLOR_H

#include <allegro.h>

#include <ostream>

using std::ostream;

class Color {
    friend ostream& operator<<(ostream& out, const Color& color);
public:
    Color(int red = 0, int green = 0, int blue = 0);
    virtual ~Color();
    
    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    void setRed(int value);
    void setGreen(int value);
    void setBlue(int value);
    void set(int red, int green, int blue);
    void set(int color_24bit);
    
    int toInteger() const;
    
    bool operator!=(const Color& right) const;
    bool operator==(const Color& right) const { return !operator!=(right); }

protected:
    int red;
    int green;
    int blue;
};

#endif

