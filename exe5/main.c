#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
volatile int flag = 0;



void btn_callback(uint gpio, uint32_t events) {
    if (events == 0x4) {
        flag = 1;
    }
    if (events == 0x8) {
        flag = 0;
    }
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  while (true) {
    gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    if (flag){
        sleep_ms(800);
        gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
        if (flag){
            while (flag) {
                gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
                if (!flag) {
                    break;
                }
            }
            printf("Aperto longo!\n");
        } else {
            printf("Aperto curto!\n");
        }
    }
  }
}
