# Interrupt Example

Learning the working of hardware interrupts on the ESP32 GPIO pins

# Pins used

`Interrupt Pin: GPIO4`

`GPIO Output Pin: GPIO2`

### Functions used

`gpio_install_isr_service() API`

`gpio_isr_handle_add() API`

# Explanation

`GPIO_PIN_INTR_POSEDGE` causes the pin on positive edge to trigger an Interrupt

`GPIO2` pin is getting toggled and each low-to-high toggle causes a interrupt which increments a static variable
