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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>

using std::ostream;

class Keyboard {
    friend ostream& operator<<(ostream& out, const Keyboard& keyboard);
public:
    Keyboard();
    virtual ~Keyboard();
    
    bool isKeyPressed(int keyCode) const;
    
    void update();
    
private:
    bool* keys;
    
    Keyboard(const Keyboard& init);
    Keyboard& operator=(const Keyboard& right);
    
    void checkKeyPressed(const Keyboard& newState);
    void checkKeyReleased(const Keyboard& newState);
    void notifyKeyPressed(const Keyboard& keyboard, int keyCode);
    void notifyKeyReleased(const Keyboard& keyboard, int keyCode);
};

#endif

