#include "stm32f10x.h"

#define PERIOD 1000000

void delay(volatile unsigned int nTime) {
  for(; nTime > 0; nTime--) {}
}
int main()
{
  RCC -> APB2ENR |= (1 << 2);
  
  GPIOA -> CRL &= ~(0xF << 20);
  GPIOA -> CRL |= (0x3 << 20);
  
  while(1) {
    GPIOA -> ODR |= (1 << 5);
    delay(PERIOD);
    GPIOA -> ODR &= ~(1 << 5);
    delay(PERIOD);
  }
}
