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

#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point();
    Point(int x, int y);
    virtual ~Point();
    
    int getX() const { return x; }
    int getY() const { return y; }
    
    void setX(int value) { x = value; }
    void setY(int value) { y = value; }
    void set(int x, int y) { setX(x); setY(y); }
    
    Point& incrementX(int value);
    Point& incrementY(int value);
    
private:
    int x;
    int y;
};

#endif

