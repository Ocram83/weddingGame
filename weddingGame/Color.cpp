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

#include "Color.h"

ostream& operator<<(ostream& out, const Color& color) {
    return out << "(" << color.getRed() << "," << color.getGreen() << "," << color.getBlue() << ")";
}

Color::Color(int _red, int _green, int _blue)
: red(_red), green(_green), blue(_blue) {
}

Color::~Color() {
}

int Color::getRed() const {
    return red;
}

int Color::getGreen() const {
    return green;
}

int Color::getBlue() const {
    return blue;
}

void Color::setRed(int value) {
    red = value % 256;
}

void Color::setGreen(int value) {
    green = value % 256;
}

void Color::setBlue(int value) {
    blue = value % 256;
}

void Color::set(int red, int green, int blue) {
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

void Color::set(int color_24bit) {
    red = color_24bit / 256 / 256;
    green = color_24bit / 256 % 256;
    blue = color_24bit % 256;
}

int Color::toInteger() const {
    return makecol(red, green, blue);
}

bool Color::operator!=(const Color& right) const {
    return red != right.red || green != right.green || blue != right.blue;
}

