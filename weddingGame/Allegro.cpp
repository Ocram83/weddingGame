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

#include "Allegro.h"

unsigned Allegro::colorDepth = 24;
Allegro* Allegro::instance = NULL;

void timer() {
    assert(Allegro::getInstance() != NULL);
    Allegro::getInstance()->onTick();
    Allegro::getInstance()->keyboard.update();
    Allegro::getInstance()->mouse.update();
}
END_OF_FUNCTION(timer)

Allegro::Allegro(unsigned width, unsigned height, unsigned _colorDepth, bool fullScreen, bool showMouse) 
: exit(false) {
    assert(instance == NULL && "Cannot create more than one instance of Allegro.");
    
    instance = this;

    allegro_init();
    
    colorDepth = _colorDepth;
    set_color_depth(colorDepth);
    
    install_keyboard();
    install_mouse();
    install_timer();

    set_alpha_blender();
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);    

    if(set_gfx_mode(fullScreen ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED, width, height, 0, 0) != 0) {
        showMessage(getLastError());
        assert(0);
    }
    
    if(install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
        showMessage(getLastError());
        //assert(0);
    }
        
    buffer = new CompositeSprite(width, height, Color(0,0,0));
    buffer->setNotification(ALL);
    
    if(showMouse)
        show_mouse(screen);
}

Allegro::~Allegro() {
    assert(instance != NULL);
    
    instance = NULL;
    
    assert(buffer != NULL);
    delete buffer;
    
    remove_int(timer);

    remove_sound();
    remove_timer();
    remove_mouse();
    remove_keyboard();
    allegro_exit();
}

Allegro& Allegro::setNotification(Notification type) {
    buffer->setNotification(type);
    return *this;
}

Allegro& Allegro::unsetNotification(Notification type) {
    buffer->unsetNotification(type);
    return *this;
}

void Allegro::run() {
    install_int(timer, 10);
    do {
        rest(500);
    }while(!exit);
    remove_int(timer);
}

void Allegro::showMessage(string s) {
    allegro_message("%s", s.c_str());
}

string Allegro::getLastError() {
    return allegro_error;
}

void Allegro::draw() {
    assert(buffer != NULL);
    assert(buffer->getData() != NULL);
    
    buffer->drawElements();
    scare_mouse();
    masked_blit(buffer->getData(), screen, 0, 0, 0, 0, buffer->getWidth(), buffer->getHeight());
    unscare_mouse();
}

