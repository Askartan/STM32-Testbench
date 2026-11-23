#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "app.h"

int main(void) {
    AppState app = {false, false};
    
    app_update(&app, false);
    assert(app.led_on == false);
    
    app_update(&app, true);
    assert(app.led_on == true);
    
    app_update(&app, true);
    assert(app.led_on == true);
    
    app_update(&app, false);
    assert(app.led_on == true);
    
    app_update(&app, true);
    assert(app.led_on == false);
    
    printf("cacy \n");
    
    return 0;
}