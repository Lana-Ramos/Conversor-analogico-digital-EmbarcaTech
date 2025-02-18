#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"

// Definição dos leds
#define LEDr 13
#define LEDg 11
#define LEDb 12

// Definição do Joystick
#define JOYSTICK_X_PIN 26  // Eixo X
#define JOYSTICK_Y_PIN 27  // Eixo Y
#define JOYSTICK_B 22 // Botão do Joystick

// Definição do push button
#define BotaoA 5 

void inicializar(){
    gpio_init(BotaoA);
    gpio_set_dir(BotaoA, GPIO_IN);
    gpio_pull_up(BotaoA);
}