#if 0
#include "stm32F10x.h"

int main(void) {

	//LED Initialization
	RCC -> APB2ENR |= RCC_APB2Periph_GPIOA;
	GPIOA -> CRL &= ~(0xF << 20);
	GPIOA -> CRL |= (0x3 << 20);

	//Button Initialiazation
	RCC -> APB2ENR |= RCC_APB2Periph_GPIOC;
	GPIOC -> CRH &= ~(0xF << 20);
	GPIOC -> CRH |= (0x4 << 20);

	//AFIO Initialization
	RCC -> APB2ENR |= RCC_APB2Periph_AFIO;
	AFIO -> EXTICR[3] &= ~(0xF << 4);
	AFIO -> EXTICR[3] |= (0x2 << 4);

	//EXTI Configuration
	EXTI -> RTSR |= (1 << 13);
	EXTI -> IMR |= (1 << 13);

	//NVIC Configuration
	NVIC -> IP[40] = 0xFF;
	NVIC -> ISER[1] |= (1 << 8);

	while(1);
}

void EXTI15_10_IRQHandler(void) {

	if((EXTI->PR & (1 << 13)) != 0) {
		GPIOA -> ODR = ~GPIOA -> ODR;
		EXTI -> PR |= (1 << 13);
	}
}
#endif

#if 0
#include "stm32F10x.h"
#include <stdio.h>

int main(void) {

	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct = {0, };

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// External interrupt Initializtion
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource9);
	EXTI_StructInit(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line = EXTI_Line9;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	// NVIC Configuration
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	while(1) {
   }
}

//USART2 Interrupt Handler
void EXTI9_5_IRQHandler(void) {

	ITStatus itStatus = EXTI_GetITStatus(EXTI_Line9);
	static int cnt = 0;
	printf("@@@@@\n");
	if(itStatus == SET) {

		cnt++;

		if(cnt % 2 ==0 ) GPIO_SetBits(GPIOC, GPIO_Pin_1);
		else GPIO_ResetBits(GPIOC, GPIO_Pin_1);

		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}
#endif

#if 0
#include "stm32F10x.h"

int main(void) {

	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct = {0, };

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
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	while(1);
}

//USART2 Interrupt Handler
void USART2_IRQHandler(void) {

	ITStatus itStatus = USART_GetITStatus(USART2, USART_IT_RXNE);

	if(itStatus == SET) {

		uint16_t rDate = USART_ReceiveData(USART2);
		USART_SendData(USART2, rDate);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}
#endif

#if 1
#include "stm32F10x.h"

int counter = 0;

int main(void) {

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStruct = {0, };

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 64000 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 1000 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM3, ENABLE);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	while(1);
}

void TIM3_IRQHandler(void) {

	ITStatus itStatus = TIM_GetITStatus(TIM3, TIM_FLAG_Update);

	if(itStatus == SET) {

		counter++;
		TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
	}
}
#endif
