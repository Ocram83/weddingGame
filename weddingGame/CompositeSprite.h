#ifndef COMPOSITE_SPRITE_H
#define COMPOSITE_SPRITE_H

#include "CompositeBitmap.h"
#include "Sprite.h"

class CompositeSprite : public TSprite<CompositeBitmap> {
public:
    CompositeSprite(const string& filename, const Point& leftTopCorner = Point());
    CompositeSprite(unsigned width, unsigned height, const Point& leftTopCorner = Point());
    CompositeSprite(unsigned width, unsigned height, const Color& background, const Point& leftTopCorner = Point());
    CompositeSprite(const CompositeSprite& init);

    CompositeSprite& setNotification(Notification type);
    CompositeSprite& unsetNotification(Notification type);
    bool hasNotification(Notification type) const;
    
    virtual void onKeyPressed(const Keyboard& keyboard, int keyCode);
    virtual void onKeyReleased(const Keyboard& keyboard, int keyCode);
    virtual void onMouseButtonPressed(const Mouse& mouse, Mouse::Button button);
    virtual void onMouseButtonReleased(const Mouse& mouse, Mouse::Button button);
    virtual void onMouseMove(const Mouse& mouse);
    virtual void onTick();
    
    virtual void draw(BITMAP* bitmap);
    
private:
    int notifications;
    
    void notifyKeyPressed(const Keyboard& keyboard, int keyCode);
    void notifyKeyReleased(const Keyboard& keyboard, int keyCode);
    void notifyMouseButtonPressed(const Mouse& mouse, Mouse::Button button);
    void notifyMouseButtonReleased(const Mouse& mouse, Mouse::Button button);
    void notifyMouseMove(const Mouse& mouse);
    void notifyTick();
};

#endif

