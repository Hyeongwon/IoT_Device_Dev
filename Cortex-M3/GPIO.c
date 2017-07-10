#if 0
#include "stm32f10x.h"
#include <stdio.h>
#define PERIOD 1000000

/*
void delay(volatile unsigned int nTime) {
  for(; nTime > 0; nTime--) {}
}*/
int main()
{
  
  //GPIOA 클럭 활성화
  RCC -> APB2ENR |= (1 << 2);
  
  //GPIOA_CRL push-pull & ouput mode, max speed 50MHz. <5Port>
  GPIOA -> CRL &= ~(0xF << 20);
  GPIOA -> CRL |= (0x3 << 20);
  
  //GPIA -> Output port5 data = 1
  GPIOA -> ODR |= (1 << 5);
  
  
  //GPIOC 클럭 활성화
  RCC -> APB2ENR |= (1 << 4);
  
  //GPIOC_CRH Floating input, input mode <13port>
  GPIOC -> CRH &= ~(0xF << 20);
  GPIOC -> CRH |= (0x4 << 20);
  
  while(1) {
    unsigned int data;
    data = GPIOC -> IDR;
      
    if( (data & (1 << 13)) != 0) {
      printf("on : %x\n", data & (1 << 13));
      GPIOA -> ODR |= (1 << 5);
    }
        
      
      else {
           GPIOA -> ODR &= ~(1 << 5);
           printf("off : %x\n", data & (1 << 13));
      }
  }
}
#endif

#if 0
#include "stm32f10x.h"
#include <stdio.h>

int main()
{
  
  //GPIOA 클럭 활성화
  RCC -> APB2ENR |= (1 << 2);
  
  //GPIOA_CRL input mode <port 5>
  GPIOA -> CRL &= ~(0xF << 20);
  GPIOA -> CRL |= (0x4 << 20);
  
  //GPIOC 클럭 활성화
  RCC -> APB2ENR |= (1 << 4);
  
  //GPIOC_CRH output <port 1>
  GPIOC -> CRL &= ~(0xF << 4);
  GPIOC -> CRL |= (0x3 << 4);
  
  while(1) {
    unsigned int data;
    data = GPIOA -> IDR;
      
    if( (data & (1 << 5)) != 0) {
      printf("on : %x\n", data & (1 << 5));
      GPIOC -> ODR |= (1 << 1);
    }
        
    else {
         GPIOC -> ODR &= ~(1 << 1);
         printf("off : %x\n", data & (1 << 5));
    }
  }
}
#endif

#if 1
#include "stm32f10x.h"

int main(void) {
  
  GPIO_InitTypeDef GPIO_InitStruct;
    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  GPIO_SetBits(GPIOA, GPIO_Pin_5);
  
}

#endif
