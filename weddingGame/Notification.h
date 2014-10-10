#ifndef NOTIFICATION_H
#define NOTIFICATION_H

enum Notification {
    ON_KEY_PRESSED = 1,
    ON_KEY_RELEASED = 2,
    ON_MOUSE_BUTTON_PRESSED = 4,
    ON_MOUSE_BUTTON_RELEASED = 8,
    ON_MOUSE_MOVE = 16,
    ON_TICK = 32,
    ALL = ~0
};

#endif

