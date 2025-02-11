// adicionando bibliotecas necessárias
#include <stdio.h> 
#include "pico/stdlib.h"
#include "pico/time.h" 
#include "hardware/pwm.h" 

//definição dos pinos e valores
#define SERVO_PIN 28
//#define SERVO_PIN 12          //PINO DO LED PARA O EXPERIMENTO
#define CLOCK_DIV 64.0 
#define TPWM 20000.0    
#define WRAP_VALUE 39063

//definição de variáveis
uint volatile slice_numero;

//função para calcular o ciclo de trabalho
uint16_t calculate_duty_cycle(float T_ON){
    return (uint16_t)((T_ON / TPWM) * WRAP_VALUE);
}

//função para movimentação do servo motor
void movimentacao(uint slice, float T_ON){
    uint16_t duty = calculate_duty_cycle(T_ON);
    pwm_set_gpio_level(SERVO_PIN, duty);       
}

//função principal
int main(){
    
     stdio_init_all(); //inicialização da comunicação serial
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); //configuração do pino do servo motor
    slice_numero = pwm_gpio_to_slice_num(SERVO_PIN); //definição do slice do pwm
    pwm_set_clkdiv(slice_numero, CLOCK_DIV);    //definição do divisor de clock
    pwm_set_wrap(slice_numero, WRAP_VALUE);    //definição do valor de wrap
    pwm_set_enabled(slice_numero, true);    //habilitação do pwm
 
    //primeira movimentação do servo motor
    printf("Movendo para 180 graus\n");
    movimentacao(slice_numero, 2400); 
    sleep_ms(5000);
    //segunda movimentação do servo motor
    printf("Movendo para 90 graus\n");
    movimentacao(slice_numero, 1470);
    sleep_ms(5000);
    //terceira movimentação do servo motor
    printf("Movendo para 0 graus\n");
    movimentacao(slice_numero, 500);
    sleep_ms(5000);

    //LOOP PRINCIPAL
    while(1){

        //movimentação suave do servo motor
        printf("Inicio da Movimentação Suave\n");
        for(float pulse = 500; pulse <= 2400; pulse += 5){  
            movimentacao(slice_numero, pulse);  
            sleep_ms(10);
        }

        //movimentação suave do servo motor
        printf("Retorno da Movimentação Suave\n");
        for(float pulse = 2400; pulse >= 500; pulse -= 5){
            movimentacao(slice_numero, pulse);
            sleep_ms(10);
        }
    }
}
