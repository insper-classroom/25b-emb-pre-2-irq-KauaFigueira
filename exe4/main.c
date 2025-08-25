#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;

const int LED_R = 4;
const int LED_G = 6;

volatile int flag_r = 0;
volatile int flag_g = 0;


void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4 && gpio == BTN_PIN_R) {          
    flag_r = 1;
  } 
  if (events == 0x8 && gpio == BTN_PIN_G) {          
    flag_g= 1;
  } 



}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);

  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  gpio_set_irq_enabled(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true);

  
  int estado_r = 0;
  int estado_g = 0;

  while (true) {
    if (flag_r) {
      estado_r = !estado_r;
      gpio_put(LED_R, estado_r);
      flag_r = 0;
    } 
    if (flag_g) {
      estado_g = !estado_g;
      gpio_put(LED_G, estado_g);
      flag_g = 0;
    }
  }
}