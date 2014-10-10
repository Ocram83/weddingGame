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

#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
public:
    enum Button { LEFT = 1, RIGHT = 2, CENTER = 4 };

    Mouse();
    virtual ~Mouse() {}
    
    int getX() const;
    int getY() const;
    int getZ() const;
    
    bool isButtonPressed(Button button) const;
    bool isLeftButtonPressed() const;
    bool isRightButtonPressed() const;
    bool isCenterButtonPressed() const;
    
    void update();
    
private:
    int buttons;
    int x;
    int y;
    int z;
    
    void checkButtonPressed(const Mouse& newState, Button button);
    void checkButtonReleased(const Mouse& newState, Button button);
    void checkMouseMove(const Mouse& newState);
    
    void notifyMouseButtonPressed(const Mouse& mouse, Button button);
    void notifyMouseButtonReleased(const Mouse& mouse, Button button);
    void notifyMouseMove(const Mouse& mouse);
};

#endif

