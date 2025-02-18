// Bibliotecas necessárias para o funcionamento do programa
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "lib/ssd1306.h"
#include "lib/font.h"

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

// Definição do Joystick
#define JOYSTICK_X_PIN 26  // Eixo X
#define JOYSTICK_Y_PIN 27  // Eixo Y
#define JOYSTICK_B 22 // Botão do Joystick

// Definição do push button
#define BotaoA 5 

// Definição da comunicação i2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

int main()
{
  i2c_init(I2C_PORT, 400 * 1000); // Inicialização do I2C usando 400Khz.

  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); 
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); 
  gpio_pull_up(I2C_SDA); 
  gpio_pull_up(I2C_SCL);

  ssd1306_t ssd; // Inicializa a estrutura do display

  ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
  ssd1306_config(&ssd); // Configura o display
  ssd1306_send_data(&ssd); // Envia os dados para o display

  // Limpa o display. O display inicia com todos os pixels apagados.
  ssd1306_fill(&ssd, false);
  ssd1306_send_data(&ssd);

  bool cor = true;
  while (true)
  {
    cor = !cor;
    // Atualiza o conteúdo do display com animações
    ssd1306_fill(&ssd, !cor); // Limpa o display
    ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor); // Desenha um retângulo
    ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
    ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 30); // Desenha uma string
    ssd1306_draw_string(&ssd, "PROF WILTON", 15, 48); // Desenha uma string      
    ssd1306_send_data(&ssd); // Atualiza o display

    sleep_ms(1000);
  }
}