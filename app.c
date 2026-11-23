#include "app.h"

void app_update(AppState *app, bool pressed) {
    if (pressed && !app->was_pressed) {
        app->led_on = !app->led_on;
    } 
    
    app->was_pressed = pressed;
}