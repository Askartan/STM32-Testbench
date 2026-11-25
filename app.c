#include "app.h"
#include <stdint.h>

uint32_t led_timer;
void app_update(AppState *app, bool pressed, uint32_t now_ms) {
    
    // swiezy press
    if (pressed && !app->was_pressed) {
        app->raw_pressed = true;
        led_timer = now_ms; // startuje odliczanie od nacisku
    }
    
    // jesli dalej trzyma, i powyzej 50ms
    if (pressed && ((now_ms - led_timer) >= 50)) {
        if (!app->stable_pressed) app->led_on = !app->led_on; // tylko raz
        
        app->stable_pressed = true;
    } 
    
    // puszcza
    if (!pressed) {
        app->stable_pressed = false;
        app->raw_pressed = false;
    }
    
    app->was_pressed = pressed;
}