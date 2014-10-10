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

#include "Keyboard.h"

#include "Allegro.h"

ostream& operator<<(ostream& out, const Keyboard& keyboard) {
    out << "Keyboard:";
    for(unsigned i = 0; i < 128; ++i)
        if(keyboard.isKeyPressed(i))
            out << " " << i;
    return out << ";";
}

Keyboard::Keyboard() {
    keys = new bool[128];
    for(int i = 0; i < 128; ++i)
        this->keys[i] = key[i];
}

Keyboard::Keyboard(const Keyboard& init) {
    assert(0);
}

Keyboard::~Keyboard() {
    delete[] keys;
}

Keyboard& Keyboard::operator=(const Keyboard& right) {
    assert(0);
}

bool Keyboard::isKeyPressed(int keyCode) const {
    assert(0 <= keyCode && keyCode <= 127);
    return this->keys[keyCode];
}

void Keyboard::update() {
    Keyboard newState;
    
    checkKeyPressed(newState);
    checkKeyReleased(newState);
    
    bool* tmp = this->keys;
    this->keys = newState.keys;
    newState.keys = tmp;
}

void Keyboard::checkKeyPressed(const Keyboard& newState) {
    for(int i = 0; i < 128; ++i)
        if(!isKeyPressed(i) && newState.isKeyPressed(i))
            notifyKeyPressed(newState, i);
}

void Keyboard::checkKeyReleased(const Keyboard& newState) {
    for(int i = 0; i < 128; ++i)
        if(isKeyPressed(i) && !newState.isKeyPressed(i))
            notifyKeyReleased(newState, i);
}

void Keyboard::notifyKeyPressed(const Keyboard& keyboard, int keyCode) {
    assert(Allegro::getInstance() != NULL);
    Allegro::getInstance()->onKeyPressed(keyboard, keyCode);
}

void Keyboard::notifyKeyReleased(const Keyboard& keyboard, int keyCode) {
    assert(Allegro::getInstance() != NULL);
    Allegro::getInstance()->onKeyReleased(keyboard, keyCode);
}

