// Bibliotecas necessárias para o funcionamento do programa
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "lib/ssd1306.h"
#include "lib/font.h"
#include "inicializar.h"
#include "LED-pwm.h"

// Função que converte o valor em microsegundos para o nível de PWM
uint16_t convert_us_to_pwm_level(uint16_t us) {
    return (us * WRAP) / 20000;  // microsegundos para nível PWM
}

// Função para mapear valores de ADC para PWM
int map_value(int value, int in_min, int in_max, int out_min, int out_max) {
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main()
{
    stdio_init_all(); // inicializa o sistema padrão de I/O
    inicializar();
    pwm_setup_led(); // configura o PWM para o LED
    i2c_init(I2C_PORT, 400 * 1000); // Inicialização do I2C usando 400Khz.

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
    gpio_pull_up(I2C_SDA); 
    gpio_pull_up(I2C_SCL);

    ssd1306_t ssd; // Inicializa a estrutura do display

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // DISPLAY INICIA APAGADO
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    bool cor = true;
    while (true)
    {
        uint16_t adc_value_x;
        uint16_t adc_value_y;  
        char str_x[5];  // Buffer para armazenar a string
        char str_y[5];  // Buffer para armazenar a string 

        adc_select_input(0); // Seleciona o ADC para eixo X. O pino 26 como entrada analógica
        adc_value_x = adc_read();
        adc_select_input(1); // Seleciona o ADC para eixo Y. O pino 27 como entrada analógica
        adc_value_y = adc_read();    
        sprintf(str_x, "%d", adc_value_x);  // Converte o inteiro em string
        sprintf(str_y, "%d", adc_value_y);  // Converte o inteiro em string
        
        cor = !cor;
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
    ssd1306_rect(&ssd, 52, 90, 8, 8, cor, !gpio_get(JOYSTICK_B)); // Desenha um retângulo  
    ssd1306_rect(&ssd, 52, 102, 8, 8, cor, !gpio_get(BotaoA)); // Desenha um retângulo    
    ssd1306_rect(&ssd, 52, 114, 8, 8, cor, !cor); // Desenha um retângulo       
    ssd1306_send_data(&ssd); // Atualiza o display

        sleep_ms(1000);
      } 
}