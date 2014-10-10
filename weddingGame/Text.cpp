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

#include "Text.h"

#include "Bitmap.h"
#include <cassert>

Text::Text(const string& _text, const Point& _position, const Color& _color, Alignment _alignment, const Color& _background, const Font& font_)
: text(_text), position(_position), alignment(_alignment), color(_color), font(font_) {
    background = new Color(_background);
}

Text::Text(const string& _text, const Point& _position, const Color& _color, Alignment _alignment, const Font& font_)
: text(_text), position(_position), alignment(_alignment), color(_color), background(NULL), font(font_) {
}

Text::Text(const Text& init)
: text(init.text), position(init.position), alignment(init.alignment), color(init.color), font(init.font) {
    background = init.background != NULL ? new Color(*init.background) : NULL;
}

Text::~Text() {
    removeBackground();
}

const Color& Text::getBackground() const {
    assert(background != NULL);
    return *background;
}

void Text::setBackground(const Color& value) {
    removeBackground();
    background = new Color(value);
}

bool Text::hasBackground() const {
    return background != NULL;
}

void Text::removeBackground() {
    if(background != NULL) {
        delete background;
        background = NULL;
    }
}
    
void Text::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);

    switch(alignment) {
    case ALIGN_LEFT:
        textout_ex(
            bitmap, 
            font.data,
            text.c_str(), 
            position.getX(), 
            position.getY(), 
            color.toInteger(), 
            hasBackground() ? getBackground().toInteger() : -1
        );
        break;
        
    case ALIGN_CENTER:
        textout_centre_ex(
            bitmap, 
            font.data, 
            text.c_str(), 
            position.getX(), 
            position.getY(), 
            color.toInteger(), 
            hasBackground() ? getBackground().toInteger() : -1
        );
        break;
    
    case ALIGN_RIGHT:
        textout_right_ex(
            bitmap, 
            font.data, 
            text.c_str(), 
            position.getX(), 
            position.getY(), 
            color.toInteger(), 
            hasBackground() ? getBackground().toInteger() : -1
        );
        break;
    
    default:
        break;
    }
}

