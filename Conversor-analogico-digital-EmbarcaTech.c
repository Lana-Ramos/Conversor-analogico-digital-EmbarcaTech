#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/i2c.h"
#include "lib/ssd1306.h"
#include "lib/font.h"
#include "inicializar.h"
#include "LED-pwm.h"

// Definição do display SSD1306
#define WIDTH 128
#define HEIGHT 64
#define ENDERECO 0x3C

// Função que converte o valor em microsegundos para o nível de PWM
uint16_t convert_us_to_pwm_level(uint16_t us) {
    return (us * WRAP) / 20000;  // microsegundos para nível PWM
}

// Função para mapear valores de ADC para PWM
int map_value(int value, int in_min, int in_max, int out_min, int out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Função para desenhar um quadrado de 8x8 pixels com borda, com o uso de retângulos
void draw_square(ssd1306_t *ssd, uint8_t x_pos, uint8_t y_pos, bool color) {
    // Desenha um retângulo de 8x8 pixels no display
    ssd1306_rect(ssd, x_pos, y_pos, 8, 8, color, color); 
}

int main() {
    stdio_init_all(); // Inicializa o sistema padrão de I/O
    inicializar();
    pwm_setup_led(); // Configura o PWM para o LED
    i2c_init(I2C_PORT, 400 * 1000); // Inicialização do I2C usando 400Khz.

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
    gpio_pull_up(I2C_SDA); 
    gpio_pull_up(I2C_SCL);

    ssd1306_t ssd; // Inicializa a estrutura do display

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // DISPLAY INICIA APAGADO
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    bool cor = true;
    uint8_t square_x = 52, square_y = 30;  // Inicializa a posição do quadrado

    while (true) {
        uint16_t adc_value_x;
        uint16_t adc_value_y;  

        // Leitura dos valores do joystick (eixos X e Y)
        adc_select_input(0); // Seleciona o ADC para eixo X. O pino 26 como entrada analógica
        adc_value_x = adc_read();
        adc_select_input(1); // Seleciona o ADC para eixo Y. O pino 27 como entrada analógica
        adc_value_y = adc_read();    

        // Controla a intensidade dos LEDs RGB com base no joystick
        pwm_set_gpio_level(LEDr, map_value(adc_value_x, 0, 4095, 0, 255));  // LED vermelho
        pwm_set_gpio_level(LEDg, map_value(adc_value_y, 0, 4095, 0, 255));  // LED verde
        pwm_set_gpio_level(LEDb, map_value(adc_value_y, 0, 4095, 0, 255));  // LED azul

        // Limpa o display
        ssd1306_fill(&ssd, false); // Limpa o display

        // Desenha o quadrado na posição atual
        draw_square(&ssd, square_x, square_y, cor); // Desenha o quadrado

        // Atualiza o display
        ssd1306_send_data(&ssd);

        // Movimento do quadrado com base nos valores do joystick
        square_x = map_value(adc_value_x, 0, 4095, 0, WIDTH - 8); // Movimenta quadrado no eixo X
        square_y = map_value(adc_value_y, 0, 4095, 0, HEIGHT - 8); // Movimenta quadrado no eixo Y

        sleep_ms(100); // Espera um pouco antes de continuar o loop
    } 
}
