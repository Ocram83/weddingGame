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

#include "Mouse.h"

#include "Allegro.h"

Mouse::Mouse() 
: buttons(mouse_b), x(mouse_x), y(mouse_y), z(mouse_z) {

}

int Mouse::getX() const {
    return x;
}

int Mouse::getY() const {
    return y;
}

int Mouse::getZ() const {
    return z;
}

bool Mouse::isButtonPressed(Button button) const {
    return buttons & button;
}

bool Mouse::isLeftButtonPressed() const {
    return buttons & LEFT;
}

bool Mouse::isRightButtonPressed() const {
    return buttons & RIGHT;
}

bool Mouse::isCenterButtonPressed() const {
    return buttons & CENTER;
}

void Mouse::update() {
    Mouse newState;
    
    checkButtonPressed(newState, LEFT);
    checkButtonPressed(newState, RIGHT);
    checkButtonPressed(newState, CENTER);
    
    checkButtonReleased(newState, LEFT);
    checkButtonReleased(newState, RIGHT);
    checkButtonReleased(newState, CENTER);
    
    checkMouseMove(newState);
        
    *this = newState;
}

void Mouse::checkButtonPressed(const Mouse& newState, Button button) {
    if(!isButtonPressed(button) && newState.isButtonPressed(button))
        notifyMouseButtonPressed(newState, button);
}

void Mouse::checkButtonReleased(const Mouse& newState, Button button) {
    if(isButtonPressed(button) && !newState.isButtonPressed(button))
        notifyMouseButtonReleased(newState, button);
}

void Mouse::checkMouseMove(const Mouse& newState) {
    if(getX() != newState.getX() || getY() != newState.getY() || getZ() != newState.getZ())
        notifyMouseMove(newState);
}

void Mouse::notifyMouseButtonPressed(const Mouse& mouse, Button button) {
    assert(Allegro::getInstance() != NULL);
    Allegro::getInstance()->onMouseButtonPressed(mouse, button);
}

void Mouse::notifyMouseButtonReleased(const Mouse& mouse, Button button) {
    assert(Allegro::getInstance() != NULL);
    Allegro::getInstance()->onMouseButtonReleased(mouse, button);
}

void Mouse::notifyMouseMove(const Mouse& mouse) {
    assert(Allegro::getInstance() != NULL);
    Allegro::getInstance()->onMouseMove(mouse);
}
