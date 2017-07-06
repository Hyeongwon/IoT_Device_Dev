#define RCC_APB2ENR     *((volatile unsigned int *) 0x40021018)
#define GPIOA_CRL       *((volatile unsigned int *) 0x40010800)
#define GPIOA_ODR        *((volatile unsigned int *) 0x4001080C)
#define PERIOD 1000000

void delay(unsigned int nTime) {
  for(; nTime>0; nTime--) {}
}  
int main()
{
  // PA5 - USER LED
  RCC_APB2ENR |= (1 << 2);
  
  GPIOA_CRL &= ~(0xF << 20);
  GPIOA_CRL |= (0x3 << 20);
  
  while(1) {
    
    GPIOA_ODR |= (1 << 5);
    delay(PERIOD);
    GPIOA_ODR &= ~(1 << 5);
    delay(PERIOD);
  }
}
