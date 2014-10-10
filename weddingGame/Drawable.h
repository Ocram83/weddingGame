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

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <allegro.h>

#include "Keyboard.h"
#include "Mouse.h"

class Drawable {
public:
    virtual ~Drawable() {}

    // This method must be implemented by all classes extending Drawable!
    virtual Drawable* clone() const = 0;

    virtual void draw(BITMAP* bitmap) = 0;
    
    virtual void onTick() {}
    virtual bool alive() const { return true; }
    
    virtual void onKeyPressed(const Keyboard& keyboard, int keyCode) {}
    virtual void onKeyReleased(const Keyboard& keyboard, int keyCode) {}
    virtual void onMouseButtonPressed(const Mouse& mouse, Mouse::Button button) {}
    virtual void onMouseButtonReleased(const Mouse& mouse, Mouse::Button button) {}
    virtual void onMouseMove(const Mouse& mouse) {}
    
    const Mouse& getMouse() const;
    const Keyboard& getKeyboard() const;
};

#endif

