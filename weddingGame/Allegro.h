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

#ifndef ALLEGRO_H_
#define ALLEGRO_H_

#include <allegro.h>
#include <iostream>

#include "Bitmap.h"
#include "Circle.h"
#include "Color.h"
#include "CompositeBitmap.h"
#include "CompositeSprite.h"
#include "Drawable.h"
#include "DrawablePointer.h"
#include "Ellipse.h"
#include "Font.h"
#include "Keyboard.h"
#include "Line.h"
#include "Mouse.h"
#include "Pixel.h"
#include "Point.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "SampleSound.h"
#include "Sprite.h"
#include "Text.h"
#include "Triangle.h"

using namespace std;

class Allegro {
    friend void timer();
public:
    typedef CompositeSprite::iterator iterator;
    typedef CompositeSprite::const_iterator const_iterator;

    virtual ~Allegro();

    static unsigned getColorDepth() { return colorDepth; }
    static Allegro* getInstance() { return instance; }

    static void showMessage(string s);
    static string getLastError();
    
    void draw();

    iterator add(const Drawable& element) { return buffer->add(element); }
    void remove(iterator it) { buffer->remove(it); }

    iterator begin() { return buffer->begin(); }
    iterator end() { return buffer->end(); }
    const_iterator begin() const { return buffer->begin(); }
    const_iterator end() const { return buffer->end(); }

    const Mouse& getMouse() const { return mouse; }
    const Keyboard& getKeyboard() const { return keyboard; }
    
    Color getPixel(int x, int y) const { return buffer->getPixel(x, y); }

    Allegro& setNotification(Notification type);
    Allegro& unsetNotification(Notification type);
    bool hasNotification(Notification type) const { return buffer->hasNotification(type); }

    virtual void run();
    
    virtual void onTick() { buffer->onTick(); }
    virtual void onKeyPressed(const Keyboard& keyboard, int keyCode) { buffer->onKeyPressed(keyboard, keyCode); }
    virtual void onKeyReleased(const Keyboard& keyboard, int keyCode) { buffer->onKeyReleased(keyboard, keyCode); }
    virtual void onMouseButtonPressed(const Mouse& mouse, Mouse::Button button) { buffer->onMouseButtonPressed(mouse, button); }
    virtual void onMouseButtonReleased(const Mouse& mouse, Mouse::Button button) { buffer->onMouseButtonReleased(mouse, button); }
    virtual void onMouseMove(const Mouse& mouse) { buffer->onMouseMove(mouse); }

protected:
    bool exit;

    Allegro(unsigned width = 640, unsigned height = 480, unsigned colorDepth = 32, bool fullScreen = false, bool showMouse = true);
    
private:
    CompositeSprite* buffer;
    Mouse mouse;
    Keyboard keyboard;

    static unsigned colorDepth;
    static Allegro* instance;
};

#endif

