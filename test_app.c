#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "app.h"

int main(void) {
    AppState app = {false, false};
    
    app_update(&app, false, 0);
    assert(app.led_on == false);
    
    app_update(&app, true, 0);
    assert(app.led_on == true);
    
    app_update(&app, true, 0);
    assert(app.led_on == true);
    
    app_update(&app, false, 0);
    assert(app.led_on == true);
    
    app_update(&app, true, 0);
    assert(app.led_on == false);
    
    printf("cacy \n");
    
    return 0;
}