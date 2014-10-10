#include "CompositeSprite.h"

#include <iostream>

using namespace std;

CompositeSprite::CompositeSprite(const string& filename, const Point& leftTopCorner)
: TSprite<CompositeBitmap>(filename, leftTopCorner), notifications(0) {
    add(Sprite(filename));
}

CompositeSprite::CompositeSprite(unsigned width, unsigned height, const Point& leftTopCorner)
: TSprite<CompositeBitmap>(width, height, leftTopCorner), notifications(0) {
}

CompositeSprite::CompositeSprite(unsigned width, unsigned height, const Color& background, const Point& leftTopCorner)
: TSprite<CompositeBitmap>(width, height, background, leftTopCorner), notifications(0) {
}

CompositeSprite::CompositeSprite(const CompositeSprite& init)
: TSprite<CompositeBitmap>(init), notifications(init.notifications) {
}

CompositeSprite& CompositeSprite::setNotification(Notification type) {
    notifications |= type;
    return *this;
}

CompositeSprite& CompositeSprite::unsetNotification(Notification type) { 
    notifications &= ~type;
    return *this;
}

bool CompositeSprite::hasNotification(Notification type) const { 
    return notifications & type;
}

void CompositeSprite::onKeyPressed(const Keyboard& keyboard, int keyCode) {
    if(hasNotification(ON_KEY_PRESSED))
        notifyKeyPressed(keyboard, keyCode);
}

void CompositeSprite::onKeyReleased(const Keyboard& keyboard, int keyCode) {
    if(hasNotification(ON_KEY_RELEASED))
        notifyKeyReleased(keyboard, keyCode);
}

void CompositeSprite::onMouseButtonPressed(const Mouse& mouse, Mouse::Button button) {
    if(hasNotification(ON_MOUSE_BUTTON_PRESSED))
        notifyMouseButtonPressed(mouse, button);
}

void CompositeSprite::onMouseButtonReleased(const Mouse& mouse, Mouse::Button button) {
    if(hasNotification(ON_MOUSE_BUTTON_RELEASED))
        notifyMouseButtonReleased(mouse, button);
}

void CompositeSprite::onMouseMove(const Mouse& mouse) {
    if(hasNotification(ON_MOUSE_MOVE))
        notifyMouseMove(mouse);
}

void CompositeSprite::onTick() {
    if(hasNotification(ON_TICK))
        notifyTick();
}

void CompositeSprite::notifyKeyPressed(const Keyboard& keyboard, int keyCode) {
    for(iterator it = begin(); it != end(); ++it) {
        Drawable& element = **it;
        element.onKeyPressed(keyboard, keyCode);
    }
}

void CompositeSprite::notifyKeyReleased(const Keyboard& keyboard, int keyCode) {
    for(iterator it = begin(); it != end(); ++it) {
        Drawable& element = **it;
        element.onKeyReleased(keyboard, keyCode);
    }
}

void CompositeSprite::notifyMouseButtonPressed(const Mouse& mouse, Mouse::Button button) {
    for(iterator it = begin(); it != end(); ++it) {
        Drawable& element = **it;
        element.onMouseButtonPressed(mouse, button);
    }
}

void CompositeSprite::notifyMouseButtonReleased(const Mouse& mouse, Mouse::Button button) {
    for(iterator it = begin(); it != end(); ++it) {
        Drawable& element = **it;
        element.onMouseButtonReleased(mouse, button);
    }
}

void CompositeSprite::notifyMouseMove(const Mouse& mouse) {
    for(iterator it = begin(); it != end(); ++it) {
        Drawable& element = **it;
        element.onMouseMove(mouse);
    }
}

void CompositeSprite::notifyTick() {
    for(iterator it = begin(); it != end(); ) {
        iterator currIt = it++;
        Drawable& element = **currIt;
        element.onTick();
        if(!element.alive())
            remove(currIt);
    }
}

void CompositeSprite::draw(BITMAP* bitmap) {
    assert(bitmap != NULL);

    drawElements();
    TSprite<CompositeBitmap>::draw(bitmap);
}

