#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "app.h"

int main(void) {
    AppState app = {false, false, false, false, 0};
    
    app_update(&app, false, 0);
    assert(app.stable_pressed == false);
    assert(app.raw_pressed == false);
    
    app_update(&app, true, 2);
    assert(app.stable_pressed == false);
    assert(app.raw_pressed == true);
    
    app_update(&app, false, 4);
    assert(app.stable_pressed == false);
    assert(app.raw_pressed == false);
    
    app_update(&app, true, 5);
    assert(app.stable_pressed == false);
    assert(app.raw_pressed == true);
    
    app_update(&app, true, 54);
    assert(app.stable_pressed == false);
    assert(app.raw_pressed == true);
    
    app_update(&app, true, 55);
    assert(app.stable_pressed == true);
    assert(app.raw_pressed == true);
    
    assert(app.led_on == true);

    // Dlugie trzymanie przycisku
    app_update(&app, true, 60);
    assert(app.led_on == true);

    // Krotkie zaklocenie
    app_update(&app, false, 70);
    app_update(&app, true, 72);

    // Nadal trzymamy przycisk
    app_update(&app, true, 122);
    assert(app.led_on == true);
    
    printf("cacy \n");
    
    return 0;
}