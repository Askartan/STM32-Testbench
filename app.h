#ifndef APP_H
#define APP_H

#include <stdbool.h>

typedef struct {
    bool was_pressed;
    bool led_on;
} AppState;

void app_update(AppState *app, bool pressed);

#endif