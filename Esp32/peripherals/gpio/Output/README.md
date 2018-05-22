# Output Example

Check the `gpio_output` function

Configured pin GPIO2 as an `OUTPUT` pin

### Functions used

`gpio_config() API`

`gpio_set_level() API`

### Data types used

`struct gpio_config_t`


# Explanation

`struct gpio_config_t` is set with appropriate parameters and passed to `gpio_config()`

`gpio_set_level()` is used to toggle the LED On and OFF
