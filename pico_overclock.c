/* 1 instruction on a 135MHz microprocessor is 7.4ns */
/* 1 instruction on a 200MHz microprocessor is 5.0ns */
/* 1 instruction on a 270MHz microprocessor is 3.7ns */
/* 1 instruction on a 360MHz microprocessor is 2.8ns */

/* Pick one... */

#define OVERCLOCK 135000
//#define OVERCLOCK 200000
//#define OVERCLOCK 270000
//#define OVERCLOCK 360000

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "hardware/vreg.h"

const uint8_t LED_PIN        = PICO_DEFAULT_LED_PIN;
const uint8_t TEST_OUTPUT_GP = 28;

int main()
{
  bi_decl(bi_program_description("Pico overclock test"));

#if OVERCLOCK > 270000
  /* Above this speed needs increased voltage */
  vreg_set_voltage(VREG_VOLTAGE_1_20);
  sleep_ms(1000);
#endif

  /* Overclock */
  set_sys_clock_khz( OVERCLOCK, 1 );

  /* Just to show were running */
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, 1);

  /* All interrupts off */
  irq_set_mask_enabled( 0xFFFFFFFF, 0 );

  /* Start wih GPIO low */
  gpio_init(TEST_OUTPUT_GP);
  gpio_set_dir(TEST_OUTPUT_GP, GPIO_OUT);
  gpio_put(TEST_OUTPUT_GP, 0);

  /*
   * Loop pauses 20 NOPs which are one cycle each, 
   * raises the GPIO, which is one cycle, then
   * 20 more NOPs, then lowers the GPIO,
   * then jumps back to the start which is 2 cycles.
   * So 44 cycles in total.
   */
  while(1)
  {
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");

    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");

    gpio_put( TEST_OUTPUT_GP, 1 );

    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");

    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");
    __asm volatile ("nop");

    gpio_put( TEST_OUTPUT_GP, 0 );
  }

}
