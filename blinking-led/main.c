#include <stdint.h>

void Reset_Handler(void);
int main(void);

// Vector Table - put at address 0x08000000
__attribute__ ((section(".vecgit statutors")))
const uint32_t vector_table[] = {
  0x20030000,             // Stack Pointer (end of SRAM)
  (uint32_t)Reset_Handler // Reset Handler on Reset Vector address
};

void Reset_Handler(void) {
  main();
  while(1);
}

// Register Definitions from RM0090
#define RCC_AHB1ENR   (*(volatile uint32_t *)(0x40023800 + 0x30))
#define GPIOG_MODER   (*(volatile uint32_t *)(0x40021800 + 0x00))
#define GPIOG_ODR     (*(volatile uint32_t *)(0x40021800 + 0x14))

void delay(volatile uint32_t count) {
  while(count--) __asm("nop");
}

int main(void) {
  RCC_AHB1ENR |= (1 << 6);      // GPIOG clock enable (Chapter 7.3.10)
  GPIOG_MODER &= ~(3 << 26);    // Clear Moder13 for PG13 (Chapter 8.4.11)
  GPIOG_MODER |=  (1 << 26);    // PG13 Output
     
  while(1) {
    // output data register
    GPIOG_ODR ^= (1 << 13);   // Toggle
    delay(250000);
  }
}
