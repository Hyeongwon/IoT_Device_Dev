#if 0
#include "stm32f10x.h"

int main()
{
  RCC -> APB2ENR |= RCC_APB2Periph_GPIOA;
  GPIOA -> CRL &=  ~(0xF << 12 | 0xF << 8);
  GPIOA -> CRL |= (0x4 << 12 | 0xB << 8); // GPIOA.2 = TX / GPIOA.3 = RX
  
  RCC->APB1ENR |= RCC_APB1Periph_USART2;
  USART2 -> CR1 |= USART_Mode_Rx | USART_Mode_Tx;
  USART2 -> BRR |= 0x00000341; // 8Mhz 클럭 사용시 9600 Bps;
  
  USART2 -> CR1 |= (1 << 13);
  
  while(1) {
    
    if((USART2 -> SR & (1 << 5)) != 0) {
      
      int data = USART2 -> DR;
      while((USART2 -> SR & (1 << 7)) == 0) {}
      USART2 -> DR = data;
    }
  }
}

#endif

#if 0
#include "stm32F10x.h"

int main(void) {
  
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
  USART_StructInit(&USART_InitStruct);
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART2, &USART_InitStruct);
  
  USART_Cmd(USART2, ENABLE);
  
  USART_SendData(USART2, 'H');
}
#endif

#if 0
//printf
#include "stm32F10x.h"
#include <stdio.h>
/*
int fputc(int ch, FILE *f) {
  
  static int last;
  
  if( (ch == (int) '\n') && (last != (int)'\r') ) {
    
    last = (int)'\r';
    
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    USART_SendData(USART2, last); // 1 (USART1)
  }
  else last = ch;
  
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
  USART_SendData(USART2, ch);
  return(ch);
}*/

int main(void) {
  
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
  USART_StructInit(&USART_InitStruct);
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART2, &USART_InitStruct);
  
  USART_Cmd(USART2, ENABLE);
  
  USART_SendData(USART2, 'H');

  int16_t myInt = 0x1234;
  float myFloat = (float)myInt;
  
  printf("myFloat %f\n\r", myFloat);
  printf("myInt %x\n\r", myInt);
  
  while(1) {
  }
}
#endif

#if 1
//Two-Way-UART & Bluetooth module
#include "stm32F10x.h"
#include <stdio.h>

int main(void) {
  
  GPIO_InitTypeDef GPIO_InitStruct;
  USART_InitTypeDef USART_InitStruct;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  //UART1
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
  USART_StructInit(&USART_InitStruct);
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &USART_InitStruct);
  
  USART_Cmd(USART1, ENABLE);
  
  //UART2
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
  USART_StructInit(&USART_InitStruct);
  USART_InitStruct.USART_BaudRate = 9600;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART2, &USART_InitStruct);
  
  USART_Cmd(USART2, ENABLE);
  
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   
  // GPIOC port1;
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  // GPIOC port2;
  GPIO_StructInit(&GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  
  while(1) {
    
    FlagStatus fstatus1 = USART_GetFlagStatus(USART1, USART_FLAG_RXNE);
    FlagStatus fstatus2 = USART_GetFlagStatus(USART2, USART_FLAG_RXNE);
    
    unsigned int input = GPIOC->IDR;
    
    if( (input & 1) != 0) {
      USART_SendData(USART2, '1');
    }
    
    if(fstatus2 == SET) {
      uint16_t rDate = USART_ReceiveData(USART2);
      //USART_SendData(USART2, rDate2);
      USART_SendData(USART2, rDate);
      //printf("rDate  = %x\n", rDate);
      //printf("GPIOC->IDR = %x\n", (input[0]));
      
      if(rDate == '1') {
        
        GPIO_SetBits(GPIOC, GPIO_Pin_1);
      } else if(rDate == '0') {
        
        GPIO_ResetBits(GPIOC, GPIO_Pin_1);
      }
      
      USART_ClearFlag(USART2, USART_FLAG_RXNE);
    }
    if(fstatus1 == SET) {
      uint16_t rDate = USART_ReceiveData(USART1);
      //USART_SendData(USART2, rDate2);
      USART_SendData(USART2, rDate);
      
      USART_ClearFlag(USART1, USART_FLAG_RXNE);
    }
  }
}
#endif

#if 0
#include "stm32F10x.h"

RCC_ClocksTypeDef RCC_ClockFreq;

int main(void) {
  
  // Meaning of ClockFreq
  RCC_GetClocksFreq(&RCC_ClockFreq);
  
  //Set SysClock
  
  /* PLL configuration: = (HSI / 2) * 16 = 64 MHz */
  RCC -> CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC |
                                        RCC_CFGR_PLLMULL));
  
  RCC-> CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_Div2 |
                           RCC_CFGR_PLLMULL16);
  
  // Enable Prefetch Buffer
  FLASH -> ACR |= FLASH_ACR_PRFTBE;
  FLASH -> ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
  FLASH -> ACR |= (uint32_t)((uint32_t)FLASH_ACR_LATENCY_2);
  
  /*HCLK = SYSCLK */
  RCC -> CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
  
  /*PCLK2 = HCLK */
  RCC -> CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
  
  /*PCLK1 = HCLK */
  RCC -> CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;
  
  /* Enable PLL */
  RCC -> CR |= RCC_CR_PLLON;
  
  /* Wait till PLL is ready */
  while( (RCC -> CR & RCC_CR_PLLRDY) == 0) {}
  
  /* Select PLL as system clock source */
  RCC -> CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC -> CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
  
  /*Wait till PLL is used as system clock source */
  while( (RCC -> CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08) {}
  
  RCC_GetClocksFreq(&RCC_ClockFreq);
}
#endif
