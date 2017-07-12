#if 0
#include "stm32F10x.h"

int counter = 0;

int main(void) {

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 64000 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 1000 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM3, ENABLE);

	while(1) {

		FlagStatus fStatus = TIM_GetFlagStatus(TIM3, TIM_FLAG_Update);

		if(fStatus == SET) {

			counter++;
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		}
	}
}

#endif

#if 0
#include "stm32F10x_tim.h"

int main(void) {

	RCC -> APB1ENR |= RCC_APB1Periph_TIM3;
	RCC -> APB2ENR |= (RCC_APB2Periph_GPIOA |
						RCC_APB2Periph_GPIOB);

	GPIOA -> CRL &= ~(0xFF << 24);
	GPIOA -> CRL |= (0xBB << 24); //PA6, 7
	GPIOB -> CRL &= ~(0xFF << 0);
	GPIOB -> CRL |= (0xBB << 0); //PB0, 1

	TIM3 -> CR1 &= ~(TIM_CR1_CMS | TIM_CR1_DIR);
	TIM3 -> ARR = 1000 - 1;
	TIM3 -> PSC = 640 - 1; // 640 x 1000 => 100Hz
	TIM3 -> EGR |= TIM_EGR_UG;

	TIM3 -> CCMR1 &= ~(TIM_CCMR1_OC2M | TIM_CCMR1_OC1M);
	TIM3 -> CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 |
					TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);

	TIM3 -> CCMR2 &= ~(TIM_CCMR2_OC4M | TIM_CCMR2_OC3M);
	TIM3 -> CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 |
					TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1);

	TIM3 -> CCER |= TIM_CCER_CC4E |
					TIM_CCER_CC3E |
					TIM_CCER_CC2E |
					TIM_CCER_CC1E;

	TIM3 -> CR1 |= TIM_CR1_CEN;

	TIM3 -> CCR1 = 1000;	// 0% ¹à±â
	TIM3 -> CCR2 = 500;		// 50% ¹à±â
	TIM3 -> CCR3 = 250;		// 75% ¹à±â
	TIM3 -> CCR4 = 0;		// 100% ¹à±â

	while(1);
}

#endif

#if 0
#include "stm32F10x_tim.h"

uint32_t get_ticks();

RCC_ClocksTypeDef RCC_Clocks;

uint32_t prev_1013;
const uint32_t interval_1013 = 1013;
uint32_t tick_1013;

int main(void) {

	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency/1000);

	RCC -> APB1ENR |= RCC_APB1Periph_TIM3;
	RCC -> APB2ENR |= RCC_APB2Periph_GPIOA;

	GPIOA -> CRL &= ~(0xF << 24);
	GPIOA -> CRL |= (0xB << 24);

	TIM3 -> CR1 &= ~(TIM_CR1_CMS | TIM_CR1_DIR);
	TIM3 -> ARR = 1000 -1;
	TIM3 -> PSC = 640 -1; // 640 x 1000 = 100Hz;
	TIM3 -> EGR |= TIM_CCMR1_OC1M;
	TIM3 -> CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM3 -> CCMR1 |= (TIM_CCMR1_OC1M_2 |
					TIM_CCMR1_OC1M_1);
	TIM3 -> CCER |= TIM_CCER_CC1E;
	TIM3 -> CR1 |= TIM_CR1_CEN;

	while(1) {

		uint32_t current = get_ticks();

		if(current-prev_1013 >= interval_1013) {

			prev_1013 = current;
			tick_1013++;
			if(tick_1013 % 2 == 0) TIM3 -> CCR1 = 1000;
			else TIM3 -> CCR1 = 0;
		}
	}
}

uint32_t tick = 0;

void SysTick_Handler(void) {

	tick++;
}

uint32_t get_ticks() {

	return tick;
}
#endif

#if 0
#include "stm32F10x_tim.h"

uint32_t get_ticks();

RCC_ClocksTypeDef RCC_Clocks;

uint32_t prev_1013;
const uint32_t interval_1013 = 1013;
uint32_t tick_1013;


uint32_t prev_1;
const uint32_t interval_1 = 1;
uint32_t tick_1 = 1;

int main(void) {

	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency/1000);

	RCC -> APB1ENR |= RCC_APB1Periph_TIM3;
	RCC -> APB2ENR |= RCC_APB2Periph_GPIOA;

	GPIOA -> CRL &= ~(0xF << 24);
	GPIOA -> CRL |= (0xB << 24);

	TIM3 -> CR1 &= ~(TIM_CR1_CMS | TIM_CR1_DIR);
	TIM3 -> ARR = 1000 -1;
	TIM3 -> PSC = 640 -1; // 640 x 1000 = 100Hz;
	TIM3 -> EGR |= TIM_CCMR1_OC1M;
	TIM3 -> CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM3 -> CCMR1 |= (TIM_CCMR1_OC1M_2 |
					TIM_CCMR1_OC1M_1);
	TIM3 -> CCER |= TIM_CCER_CC1E;
	TIM3 -> CR1 |= TIM_CR1_CEN;

	while(1) {

		static uint32_t inc = 1;
		uint32_t current = get_ticks();

		if(current-prev_1 >= interval_1) {

			prev_1 = current;
			tick_1 += inc;
			if(tick_1 == 1000 || tick_1 == 0) inc = -inc;
			TIM3 -> CCR1 = tick_1;
		}

	}
}

uint32_t tick = 0;

void SysTick_Handler(void) {

	tick++;
}

uint32_t get_ticks() {

	return tick;
}
#endif

#if 1
#include "stm32f10x.h"

static GPIO_InitTypeDef GPIO_InitStruct;
static TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
static TIM_OCInitTypeDef TIM_OCInitStruct;

void piezo_setup() {

	//GPIO configuration for PWM
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

	//Timer configuration
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseInitStruct.TIM_Period = 1000 - 1;	// 0.999
	TIM_TimeBaseInitStruct.TIM_Prescaler = 64 - 1;	// Div 64
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

	//PWM configuration
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);

	TIM_Cmd(TIM2, ENABLE);
}

static int buzzer_en = 0;
void piezo_buzzer_loop_by_pwm() {

	const uint32_t melody[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
	static int cnt;

	if(buzzer_en == 1) {

		cnt++;
		TIM_SetAutoreload(TIM2, melody[cnt % 8]*2 - 1);
		TIM_SetCompare4(TIM2, melody[cnt % 8] - 1);
		buzzer_en = 0;
	}
}

static __IO uint32_t buzzer_cnt;
void piezo_buzzer_tick_by_pwm() {

	buzzer_cnt++;
	if(buzzer_cnt % 500 == 0) buzzer_en = 1;
}

RCC_ClocksTypeDef RCC_Clocks;

int main() {

	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

	piezo_setup();
	while(1) piezo_buzzer_loop_by_pwm();
}

void SysTick_Handler(void) {
	piezo_buzzer_tick_by_pwm();
}
#endif

#if 0
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

static GPIO_InitTypeDef GPIO_InitStruct;
static TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
static TIM_OCInitTypeDef TIM_OCInitStruct;

void servo_motor_loop_by_pwm();

void main() {

	//GPIO configuration for PWM
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

	//Timer configuration
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseInitStruct.TIM_Period = 20000 - 1;	// 0.999
	TIM_TimeBaseInitStruct.TIM_Prescaler = 64 - 1;	// Div 24
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

	//PWM configuration
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);

	TIM_Cmd(TIM2, ENABLE);

	while(1)
	servo_motor_loop_by_pwm();
}

static int motor_en = 0;
void servo_motor_loop_by_pwm() {

	static int cnt;
	volatile int i = 0;

	for(i = 0; i < 30000; i++);

	cnt += 10;
	TIM_SetCompare4(TIM2, 500+cnt%2400);
	if(cnt % 2400 == 0)
		for(i = 0; i < 2000000; i++);
}
#endif
