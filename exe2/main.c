#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED_R = 4;


volatile int flag;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) {    
    if (flag == 1) {
      flag = 0;
    }      
    } else {
      flag = 1;
    }
  
  
}

int main() {
  stdio_init_all();
  flag = 0;

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);
  int estado = 0;


  while (true) {
    gpio_set_irq_enabled_with_callback(
      BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    
    if (flag){

      estado = !estado;
      gpio_put(LED_R, estado);
      flag = 0;

    }
    

  }
}
