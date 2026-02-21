#include <stdint.h>

void Reset_Handler(void);
int main(void);

// Vektör Tablosu - 0x08000000 adresine yerleşecek
__attribute__ ((section(".vectors")))
const uint32_t vector_table[] = {
  0x20030000,             // Stack Pointer (SRAM sonu)
  (uint32_t)Reset_Handler // Reset Handler
};

void Reset_Handler(void) {
  main();
  while(1);
}

// Register Tanımları
#define RCC_AHB1ENR   (*(volatile uint32_t *)(0x40023800 + 0x30))
#define GPIOG_MODER   (*(volatile uint32_t *)(0x40021800 + 0x00))
#define GPIOG_ODR     (*(volatile uint32_t *)(0x40021800 + 0x14))

void delay(volatile uint32_t count) {
  while(count--) __asm("nop");
}

int main(void) {
  RCC_AHB1ENR |= (1 << 6);      // GPIOG Saat sinyali
  GPIOG_MODER &= ~(3 << 26);    // Temizle
  GPIOG_MODER |=  (1 << 26);    // PG13 Output
    
  while(1) {
    GPIOG_ODR ^= (1 << 13);   // Toggle
    delay(500000);
  }
}
