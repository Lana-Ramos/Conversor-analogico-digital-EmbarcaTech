#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

// Definição dos leds
#define LEDr 13
#define LEDg 11
#define LEDb 12

#define WRAP 255  // Valor máximo do PWM (para 8 bits)
#define DIVISER 16  // Divisor de clock do PWM

void pwm_setup_led() {
    // LED vermelho
    gpio_set_function(LEDr, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM
    uint slice_ledr = pwm_gpio_to_slice_num(LEDr); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice_ledr, DIVISER); //define o divisor de clock do PWM
    pwm_set_wrap(slice_ledr, WRAP); //definir o valor de wrap
    pwm_set_enabled(slice_ledr, true); //habilita o pwm no slice correspondente

    // LED verde
    gpio_set_function(LEDg, GPIO_FUNC_PWM); 
    uint slice_ledg = pwm_gpio_to_slice_num(LEDg); 

    pwm_set_clkdiv(slice_ledg, DIVISER); 
    pwm_set_wrap(slice_ledg, WRAP); 
    pwm_set_enabled(slice_ledg, true); 

    // LED azul
    gpio_set_function(LEDb, GPIO_FUNC_PWM); 
    uint slice_ledb = pwm_gpio_to_slice_num(LEDb); 

    pwm_set_clkdiv(slice_ledb, DIVISER); 
    pwm_set_wrap(slice_ledb, WRAP); 
    pwm_set_enabled(slice_ledb, true); 
}