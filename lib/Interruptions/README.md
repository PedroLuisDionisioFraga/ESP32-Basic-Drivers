# Interruptions
This is a library that provides a interface to manage interruptions in a program.

## Externals
This library uses the ISR interruptions. The priority of interruptions are defined in the `esp_intr_alloc.h` library.

### Example
```c
void config_interruption(gpio_pinout_t pinout, gpio_int_type_t intr_type, void gpio_isr_handler(void *arg));

void exclude_interruption(gpio_pinout_t pinout);
```

### NOTES
* Is not recommended to use the **GPIO34** pin with interruptions. This pin is used by the ESP32 to wake up from deep sleep mode. If you use this pin, the ESP32 will wake up from deep sleep mode when the pin is activated, even if the interruption is not enabled.