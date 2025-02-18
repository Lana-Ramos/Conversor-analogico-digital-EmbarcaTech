// Bibliotecas necessárias para o funcionamento do programa
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "lib/ssd1306.h"
#include "lib/font.h"

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

int main()
{
    stdio_init_all();

    return 0;
}
