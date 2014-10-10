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

#ifndef TEXT_H
#define TEXT_H

#include "Color.h"
#include "Drawable.h"
#include "Font.h"
#include "Point.h"

#include <allegro.h>
#include <string>

using std::string;

class Text : public Drawable {
public:
    enum Alignment { ALIGN_LEFT = 0, ALIGN_CENTER, ALIGN_RIGHT };

    Text(const string& text = "", const Point& position = Point(), const Color& color = Color(), Alignment alignment = ALIGN_LEFT, const Font& font = Font());
    Text(const string& text, const Point& position, const Color& color, Alignment alignment, const Color& background, const Font& font = Font());
    Text(const Text& init);
    virtual ~Text();
    
    const string& getText() const { return text; }
    void setText(const string& value) { text = value; }
    
    const Point& getPosition() const { return position; }
    void setPosition(const Point& value) { position = value; }
    
    Alignment getAlignment() const { return alignment; }
    void setAlignment(Alignment value) { alignment = value; }
    
    const Color& getColor() const { return color; }
    void setColor(const Color& value) { color = value; }
    
    const Color& getBackground() const;
    void setBackground(const Color& value);
    bool hasBackground() const;
    void removeBackground();

    virtual Drawable* clone() const { return new Text(*this); }
    virtual void draw(BITMAP* bitmap);
    
private:
    string text;
    Point position;
    Alignment alignment;
    Color color;
    Color* background;
    Font font;
};

#endif

