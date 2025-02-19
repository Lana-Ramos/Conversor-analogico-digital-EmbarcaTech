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

// Função para desenhar um pixel no display SSD1306
void ssd1306_draw_pixel(ssd1306_t *ssd, uint8_t x, uint8_t y, bool color) {
    if (x >= WIDTH || y >= HEIGHT) {
        return; // Ignora se o pixel estiver fora dos limites do display
    }

    // Desenha um pixel no display
    ssd1306_draw_pixel(ssd, x, y, color);
}

// Função para desenhar um quadrado de 8x8 pixels preenchido
void fill_square(ssd1306_t *ssd, uint8_t x_pos, uint8_t y_pos, bool cor) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ssd1306_draw_pixel(ssd, x_pos + i, y_pos + j, cor); // Desenha pixel por pixel
        }
    }
    ssd1306_send_data(ssd);  // Atualiza o display
}

int main() {
    stdio_init_all(); // inicializa o sistema padrão de I/O
    inicializar();
    pwm_setup_led(); // configura o PWM para o LED
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
        char str_x[5];  // Buffer para armazenar a string
        char str_y[5];  // Buffer para armazenar a string 

        // Leitura dos valores do joystick (eixos X e Y)
        adc_select_input(0); // Seleciona o ADC para eixo X. O pino 26 como entrada analógica
        adc_value_x = adc_read();
        adc_select_input(1); // Seleciona o ADC para eixo Y. O pino 27 como entrada analógica
        adc_value_y = adc_read();    
        sprintf(str_x, "%d", adc_value_x);  // Converte o inteiro em string
        sprintf(str_y, "%d", adc_value_y);  // Converte o inteiro em string

        // Controla a intensidade dos LEDs RGB com base no joystick
        pwm_set_gpio_level(LEDr, map_value(adc_value_x, 0, 4095, 0, 255));  // LED vermelho
        pwm_set_gpio_level(LEDg, map_value(adc_value_y, 0, 4095, 0, 255));  // LED verde
        pwm_set_gpio_level(LEDb, map_value(adc_value_y, 0, 4095, 0, 255));  // LED azul

        // Atualiza o conteúdo do display com animações
        ssd1306_fill(&ssd, !cor); // Limpa o display
        ssd1306_rect(&ssd, 3, 3, 122, 60, cor, !cor); // Desenha um retângulo
        ssd1306_line(&ssd, 3, 25, 123, 25, cor); // Desenha uma linha
        ssd1306_line(&ssd, 3, 37, 123, 37, cor); // Desenha uma linha   
        ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 6); // Desenha uma string
        ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 16); // Desenha uma string
        ssd1306_draw_string(&ssd, "ADC   JOYSTICK", 10, 28); // Desenha uma string 
        ssd1306_draw_string(&ssd, "X    Y    PB", 20, 41); // Desenha uma string    
        ssd1306_line(&ssd, 44, 37, 44, 60, cor); // Desenha uma linha vertical         
        ssd1306_draw_string(&ssd, str_x, 8, 52); // Desenha uma string     
        ssd1306_line(&ssd, 84, 37, 84, 60, cor); // Desenha uma linha vertical      
        ssd1306_draw_string(&ssd, str_y, 49, 52); // Desenha uma string   

        // Desenha o quadrado que se move com base no joystick
        fill_square(&ssd, square_x, square_y, cor); // Desenha o quadrado
        ssd1306_send_data(&ssd); // Atualiza o display

        // Movimento do quadrado com base nos valores do joystick
        square_x = map_value(adc_value_x, 0, 4095, 0, WIDTH - 8); // Movimenta quadrado no eixo X
        square_y = map_value(adc_value_y, 0, 4095, 0, HEIGHT - 8); // Movimenta quadrado no eixo Y

        sleep_ms(100); // Espera um pouco antes de continuar o loop
    } 
}
