#include <stdio.h> 
#include "pico/stdlib.h"
#include "pico/time.h" 
#include "hardware/pwm.h" 

//definição dos pinos e valores
#define SERVO_PIN 28
#define CLOCK_DIV 64.0 
#define TPWM 20000.0    
#define WRAP_VALUE 39063

uint volatile slice_numero;


uint16_t calculate_duty_cycle(float T_ON){
    return (uint16_t)((T_ON / TPWM) * WRAP_VALUE);
}


void movimentacao(uint slice, float T_ON){
    uint16_t duty = calculate_duty_cycle(T_ON);
    pwm_set_gpio_level(SERVO_PIN, duty);       
}


int main(){
     stdio_init_all(); 

    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    slice_numero = pwm_gpio_to_slice_num(SERVO_PIN); 

    pwm_set_clkdiv(slice_numero, CLOCK_DIV);
    pwm_set_wrap(slice_numero, WRAP_VALUE);
    pwm_set_enabled(slice_numero, true);
 
    printf("Movendo para 180 graus\n");
    movimentacao(slice_numero, 2400); 
    sleep_ms(5000);
    
    printf("Movendo para 90 graus\n");
    movimentacao(slice_numero, 1470);
    sleep_ms(5000);
 
    printf("Movendo para 0 graus\n");
    movimentacao(slice_numero, 500);
    sleep_ms(5000);

    while(1){

    }
}
