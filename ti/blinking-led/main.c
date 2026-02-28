#include <stdint.h>

// Register addresses for TMS570LC4357 GIO
#define GIO_PORTB_DIR   (*(volatile uint32_t *)0xFFF7BC54)
#define GIO_PORTB_DOUT  (*(volatile uint32_t *)0xFFF7BC58)

void delay(uint32_t count) {
  while(count--) { __asm__("nop"); }
}

// Minimal vector table
__attribute__((section(".intvecs")))
void rst_vector() {
  __asm__("b _start"); // Jump to startup
}

int main(void) {
  GIO_PORTB_DIR |= (1 << 2); // Set Pin 2 as output

  while(1) {
    GIO_PORTB_DOUT ^= (1 << 2); // Toggle LED
    delay(1000000);
  }
}

void _start(void) {
  // In a real app, you must disable the Watchdog (DCC/VBP) here
  // For a quick test, we jump straight to main
  main();
}
