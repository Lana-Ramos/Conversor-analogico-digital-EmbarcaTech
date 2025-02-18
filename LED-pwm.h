#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#define FREQUENCIA  50 // frequência do PWM
#define DIVISER  125 // divisor do clock para o PWM
#define DC  5 // ciclo ativo de ±5µs
#define DELAY 10    // atraso de ajuste
const uint16_t WRAP = 20000; // periodo/wrap
uint slice;

// Definição dos leds
#define LEDr 13
#define LEDg 11
#define LEDb 12

// Função que converte o valor em microsegundos para o nível de PWM
uint16_t convert_us_to_pwm_level(uint16_t us) {
    return (us * WRAP) / 20000;  // microsegundos para nível PWM
}

// Função que configura o módulo PWM para o LEDs
void pwm_setup_led() {
    // LED vermelho
    gpio_set_function(LEDr, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM
    uint slice_led = pwm_gpio_to_slice_num(LEDr); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice_led, DIVISER); //define o divisor de clock do PWM
    pwm_set_wrap(slice_led, WRAP); //definir o valor de wrap
    pwm_set_enabled(slice_led, true); //habilita o pwm no slice correspondente

    // LED verde
    gpio_set_function(LEDg, GPIO_FUNC_PWM); 
    uint slice_led = pwm_gpio_to_slice_num(LEDg); 

    pwm_set_clkdiv(slice_led, DIVISER); 
    pwm_set_wrap(slice_led, WRAP); 
    pwm_set_enabled(slice_led, true); 

    // LED azul
    gpio_set_function(LEDb, GPIO_FUNC_PWM); 
    uint slice_led = pwm_gpio_to_slice_num(LEDb); 

    pwm_set_clkdiv(slice_led, DIVISER); 
    pwm_set_wrap(slice_led, WRAP); 
    pwm_set_enabled(slice_led, true); 
}