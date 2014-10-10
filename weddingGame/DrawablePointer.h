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

#ifndef DRAWABLE_POINTER_H
#define DRAWABLE_POINTER_H

#include "Drawable.h"

class DrawablePointer : public Drawable {
public:
    DrawablePointer(Drawable& instance);
    virtual ~DrawablePointer();
    
    virtual Drawable* clone() const { return new DrawablePointer(*this); }
    virtual void draw(BITMAP* bitmap) { instance->draw(bitmap); }
    
    virtual void onTick() { instance->onTick(); }
    virtual bool alive() const { return instance->alive(); }
    
    virtual void onKeyPressed(const Keyboard& keyboard, int keyCode) { instance->onKeyPressed(keyboard, keyCode); }
    virtual void onKeyReleased(const Keyboard& keyboard, int keyCode) { instance->onKeyReleased(keyboard, keyCode); }
    virtual void onMouseButtonPressed(const Mouse& mouse, Mouse::Button button) { instance->onMouseButtonPressed(mouse, button); }
    virtual void onMouseButtonReleased(const Mouse& mouse, Mouse::Button button) { instance->onMouseButtonReleased(mouse, button); }
    virtual void onMouseMove(const Mouse& mouse) { instance->onMouseMove(mouse); }

    
private:
    Drawable* instance;
};

#endif

