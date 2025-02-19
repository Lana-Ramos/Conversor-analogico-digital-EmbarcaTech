#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Definição da comunicação i2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

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
    
    // INICIALIZAÇÃO DO JOYSTICK
    gpio_init(JOYSTICK_B);
    gpio_set_dir(JOYSTICK_B, GPIO_IN);
    gpio_pull_up(JOYSTICK_B);

    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);  
    
    // Inicializando o display SSD1306 (I2C)
    i2c_init(i2c0, 400000);  // Inicializando I2C com uma velocidade de 400kHz
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);

    // Inicializando as variáveis de controle do joystick
    uint16_t x_value, y_value;
}