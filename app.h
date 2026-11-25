#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool      stable_pressed;
    bool      raw_pressed;
    bool      was_pressed;
    bool      led_on;
    uint32_t  timer;
} AppState;

void app_update(AppState *app, bool pressed, uint32_t now_ms);

#endif