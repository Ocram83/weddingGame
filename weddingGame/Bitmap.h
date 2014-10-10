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

#ifndef BITMAP_H
#define BITMAP_H

#include "Color.h"

#include <allegro.h>
#include <string>

using std::string;

class Bitmap {
public:
    Bitmap(const string& filename);
    Bitmap(unsigned width, unsigned height);
    Bitmap(unsigned width, unsigned height, const Color& background);
    Bitmap(const Bitmap& init);
    virtual ~Bitmap();
    
    void free();
    
    int getWidth() const;
    int getHeight() const;
    
    Color getPixel(int x, int y) const;
    
    Color getBackground() const;
    void setBackground(const Color& value);
    bool hasBackground() const;
    void removeBackground();
    void clearBackground();

protected:    
    BITMAP* getData() { return data; }

private:
    BITMAP* data;
    Color background;
};

#endif

