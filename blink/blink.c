#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define SW_PIN 7 // Digital button output (GP10)
#define VR_Y_PIN 26 // Analog Y-axis output of the joystick (ADC0)
#define VR_X_PIN 27 // Analog X-axis output of the joystick (ADC1)

#define AXIS_TRANSLATION 8

int main() {
    // Initialize standard I/O and ADC
    stdio_init_all();
    
    // Set up the switch button as input (high or low)
    gpio_init(SW_PIN);
    gpio_set_dir(SW_PIN, GPIO_IN);
    gpio_pull_up(SW_PIN);

    // Enable the ADC channels for VR_Y_PIN and VR_X_PIN (12 bits)
    adc_init();
    adc_gpio_init(VR_Y_PIN);
    adc_gpio_init(VR_X_PIN);

    while (true) {
        if (gpio_get(SW_PIN) == 0) {
            printf("Button pressed\n\r");
        } else {
            printf("Button not pressed\n\r");
        }

        adc_select_input(0);
        uint16_t y_value = adc_read();
        printf("Y-axis: %d\n\r", y_value - AXIS_TRANSLATION);

        adc_select_input(1);
        uint16_t x_value = adc_read();
        printf("X-axis: %d\n\r", x_value - AXIS_TRANSLATION);

        sleep_ms(16);
    }
}
