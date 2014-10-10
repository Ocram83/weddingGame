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

#ifndef COMPOSITE_BITMAP_H
#define COMPOSITE_BITMAP_H

#include "Bitmap.h"
#include "Drawable.h"
#include "Notification.h"

#include <list>

using std::list;

class Allegro;

class CompositeBitmap : public Bitmap {
    friend class Allegro;
public:
    typedef list<Drawable*>::iterator iterator;
    typedef list<Drawable*>::const_iterator const_iterator;

    CompositeBitmap(const string& filename);
    CompositeBitmap(unsigned width = 0, unsigned height = 0);
    CompositeBitmap(unsigned width, unsigned height, const Color& background);
    CompositeBitmap(const CompositeBitmap& init);
    virtual ~CompositeBitmap();
    
    iterator add(const Drawable& element);
    void remove(iterator it);
    
    iterator begin() { return elements.begin(); }
    iterator end() { return elements.end(); }
    const_iterator begin() const { return elements.begin(); }
    const_iterator end() const { return elements.end(); }
    
    void clear();
    
    virtual void drawElements();

private:
    list<Drawable*> elements;
};

#endif

