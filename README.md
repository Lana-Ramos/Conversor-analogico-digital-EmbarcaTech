# Controle de Quadrado em Display SSD1306 com Joystick

## Descrição

**Utilizando o microcontrolador RP2040 e o display SSD1306**

Este repositório contém a atividade referente à aula de 10/02/25 da capacitação em Sistemas Embarcados do EmbartaTech. O projeto envolve o controle do movimento de um quadrado em um display OLED SSD1306, utilizando um joystick conectado ao Raspberry Pi Pico W (RP2040). O movimento do quadrado é realizado com base na leitura dos eixos X e Y do joystick utiizando ADC e pwm, permitindo mover o quadrado de acordo com os valores capturados pelos eixos.

A simulação é realizada no hardware real, com o display SSD1306 exibindo o quadrado que se move dinamicamente pela tela.

## Componentes Utilizados

- **Placa Raspberry Pi Pico W (RP2040)**
- **Display OLED SSD1306 (128x64 pixels)**
- **Joystick com eixos X e Y (conectado aos pinos ADC 26 e 27)**
- **LED RGB - Conectado à GPIO 12, 13 e 14 para controlar as cores com base nos valores do joystick**

## Funcionalidades

- **Controle de movimento do quadrado**:
  - O quadrado de 8x8 pixels é movido conforme a leitura dos eixos X e Y do joystick.
  - O quadrado começa centralizado na tela e se move de acordo com os valores do joystick, permitindo controlar sua posição na tela.

- **Controle de intensidade do LED RGB**:
  - A cor do LED RGB é ajustada conforme a posição do joystick.
  - A intensidade de cada componente (vermelho, verde e azul) é controlada proporcionalmente aos valores dos eixos X e Y do joystick.

## Vídeos do Projeto

- **Link do Vídeo do funcionamento do display e movimento do quadrado**: 
  [Link para o vídeo](https://drive.google.com/file/d/1yXkapn-rLAB9pVwMj8mkMFT59o-fmqL5/view?usp=drivesdk)

## Configuração do Ambiente de Desenvolvimento

### Instalação

Antes de iniciar o programa, você vai precisar instalar as seguintes ferramentas na sua máquina:

- **Git**: [Download do Git](https://git-scm.com/downloads)
- **Visual Studio Code**: [Download do VSCode](https://code.visualstudio.com/download)
- **Compilador para C/C++**

### Dentro do VSCode

- Extensões: 
  - CMake
  - CMake Tools
  - C/C++
  - Raspberry Pi Pico

### Clonagem do Repositório

Para clonar este repositório, você deve ter o Git instalado e, em seguida, usar o comando abaixo no terminal do VSCode:

```bash
$ git clone https://github.com/Lana-Ramos/Conversor-analogico-digital-EmbarcaTech.git
```

Acesse a pasta do projeto:

```bash
$ cd Conversor-analogico-digital-EmbarcaTech
```

### Compile & Run

Compile o projeto utilizando a extensão Raspberry Pi Pico e envie para sua placa via USB. O código pode ser executado diretamente na Raspberry Pi Pico W conectada ao display SSD1306. O movimento do quadrado será controlado pelo joystick.

## Status do Projeto

**Concluído**

## Autor

Lana Ramos Gomes

## Licença

Repositório feito para fins educacionais.
