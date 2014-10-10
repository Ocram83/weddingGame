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

#include "Bitmap.h"

#include "Allegro.h"
#include <cassert>

Bitmap::Bitmap(const string& filename)
: background(255,0,255) {
    data = load_bitmap(filename.c_str(), NULL);
    assert(data != NULL);
}

Bitmap::Bitmap(unsigned width, unsigned height) 
: background(255,0,255) {
    data = create_bitmap_ex(Allegro::getColorDepth(), width, height);
    clearBackground();
}

Bitmap::Bitmap(unsigned width, unsigned height, const Color& background)
: background(background) {
    data = create_bitmap_ex(Allegro::getColorDepth(), width, height);
    clearBackground();
}

Bitmap::Bitmap(const Bitmap& init)
: data(NULL), background(init.background) {
    if(init.data != NULL) {
        data = create_bitmap(init.getWidth(), init.getHeight());
        clearBackground();
        masked_blit(init.data, data, 0, 0, 0, 0, getWidth(), getHeight());
    }
}

Bitmap::~Bitmap() {
    free();
}

void Bitmap::free() {
    if(data != NULL) {
        destroy_bitmap(data);
        data = NULL;
    }
}

Color Bitmap::getBackground() const {
    return background;
}

void Bitmap::setBackground(const Color& value) {
    background = value;
}

bool Bitmap::hasBackground() const {
    return background != Color(255,0,255);
}

void Bitmap::removeBackground() {
    background = Color(255,0,255);
}
    
void Bitmap::clearBackground() {
    assert(data != NULL);
    clear_to_color(data, getBackground().toInteger());
}

int Bitmap::getWidth() const {
    assert(data != NULL);
    return data->w;
}

int Bitmap::getHeight() const {
    assert(data != NULL);
    return data->h;
}

Color Bitmap::getPixel(int x, int y) const {
    assert(data != NULL);
    if(!(0 <= x && x <= getWidth()))
        return Color(255,0,255);
    if(!(0 <= y && y <= getHeight()))
        return Color(255,0,255);
    Color res;
    res.set(getpixel(data, x, y));
    return res;
}

