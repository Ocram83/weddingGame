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

#include "CompositeBitmap.h"

#include "Sprite.h"

#include <iostream>
#include <cassert>

using namespace std;

CompositeBitmap::CompositeBitmap(const string& filename)
: Bitmap(filename) {
    add(Sprite(filename));
}

CompositeBitmap::CompositeBitmap(unsigned width, unsigned height)
: Bitmap(width, height) {
}

CompositeBitmap::CompositeBitmap(unsigned width, unsigned height, const Color& background)
: Bitmap(width, height, background) {
}

CompositeBitmap::CompositeBitmap(const CompositeBitmap& init)
: Bitmap(init) {
    for(list<Drawable*>::const_iterator it = init.elements.begin(); it != init.elements.end(); ++it)
        add(**it);
}

CompositeBitmap::~CompositeBitmap() {
    clear();
}

void CompositeBitmap::clear() {
    while(!elements.empty()) {
        assert(elements.front() != NULL);
        delete elements.front();
        elements.pop_front();
    }
}

CompositeBitmap::iterator CompositeBitmap::add(const Drawable& element) {
    elements.push_back(element.clone());
    return --elements.end();
}

void CompositeBitmap::remove(iterator it) {
    elements.erase(it);
}

void CompositeBitmap::drawElements() {
    assert(getData() != NULL);

    clearBackground();
    for(list<Drawable*>::const_iterator it = elements.begin(); it != elements.end(); ++it)
        (**it).draw(getData());
}

