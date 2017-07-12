#if 0
#include "stm32F10x.h"

RCC_ClocksTypeDef RCC_ClockFreq;

int main(void) {

  SysTick -> LOAD = 32000000 / 1000 - 1;
  SysTick -> VAL = 0;
  SysTick -> CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;

  while(1);
}

uint32_t tick = 0;
void SysTick_Handler(void) {
	tick++;
}
#endif

#if 1
#include "stm32F10x.h"

uint32_t get_ticks();

RCC_ClocksTypeDef RCC_Clocks;

uint32_t prev_1013;
const uint32_t interval_1013 = 1013;
uint32_t tick1013;

uint32_t prev_509;
const uint32_t interval_509 = 509;
uint32_t tick509;

int main(void) {

	RCC_GetClocksFreq(&RCC_Clocks);
	SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

	while(1) {
		uint32_t current = get_ticks();

		if(current-prev_1013 >= interval_1013) {

			prev_1013 = current;
			//work here
			tick1013++;
		}

		if(current-prev_509 >= interval_509) {

			prev_509 = current;
			//work here;
			tick509++;
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
