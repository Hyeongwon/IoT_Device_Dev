#if 0
#include "stm32F10x.h"

__IO uint16_t verti;

int main(void) {

	RCC -> APB2ENR |= RCC_APB2Periph_GPIOA;

	GPIOA -> CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);

	RCC -> CFGR &= ~RCC_CFGR_ADCPRE;
	RCC -> CFGR |= RCC_CFGR_ADCPRE_DIV8;

	RCC -> APB2ENR |= RCC_APB2Periph_ADC1;

	ADC1 -> CR2 &= ~ADC_CR2_EXTSEL;
	ADC1 -> CR2 |= (ADC_CR2_EXTSEL_0 |
					ADC_CR2_EXTSEL_1 |
					ADC_CR2_EXTSEL_2);

	ADC1 -> CR2 |= ADC_CR2_EXTTRIG;

	ADC1 -> SQR1 &= ~ADC_SQR1_L; // L[3:0] = 0;

	ADC1 -> SMPR2 &= ~ADC_SMPR2_SMP1;
	ADC1 -> SMPR2 |= ADC_SMPR2_SMP1_0;
	ADC1 -> SQR3 &= ~ADC_SQR3_SQ1;
	ADC1 -> SQR3 |= ADC_SQR3_SQ1_0;

	ADC1 -> CR2 |= ADC_CR2_ADON; // ADC Enable;

	while(1) {

		ADC1 -> CR2 |= ADC_CR2_SWSTART; // start ONE conversion
		while((ADC1 -> SR & ADC_SR_EOC) == 0) {} // wait end of conversion
		verti = ADC1 -> DR;
	}
}
#endif

#if 1
#include "stm32F10x.h"

__IO uint16_t verti[12];

const uint16_t CH[] = {

		0, 1, 4, 5, 6, 7,
		8, 9, 10, 11, 12, 13, 0xFF,
};

uint16_t chNo;

int main(void) {

	RCC -> APB2ENR |= (RCC_APB2Periph_GPIOA |
					   RCC_APB2Periph_GPIOB |
					   RCC_APB2Periph_GPIOC);

	GPIOA -> CRL &= ~( (GPIO_CRL_CNF0 | GPIO_CRL_MODE0) |
					   (GPIO_CRL_CNF1 | GPIO_CRL_MODE1) |
					   (GPIO_CRL_CNF4 | GPIO_CRL_MODE4) |
					   (GPIO_CRL_CNF5 | GPIO_CRL_MODE5) |
					   (GPIO_CRL_CNF6 | GPIO_CRL_MODE6) |
					   (GPIO_CRL_CNF7 | GPIO_CRL_MODE7));

	GPIOB -> CRL &= ~( (GPIO_CRL_CNF0 | GPIO_CRL_MODE0) |
					   (GPIO_CRL_CNF1 | GPIO_CRL_MODE1));

	GPIOC -> CRL &= ~( (GPIO_CRL_CNF0 | GPIO_CRL_MODE0) |
					   (GPIO_CRL_CNF1 | GPIO_CRL_MODE1) |
					   (GPIO_CRL_CNF2 | GPIO_CRL_MODE2) |
					   (GPIO_CRL_CNF3 | GPIO_CRL_MODE3));

	RCC -> CFGR &= ~RCC_CFGR_ADCPRE;
	RCC -> CFGR |= RCC_CFGR_ADCPRE_DIV8;

	RCC -> APB2ENR |= RCC_APB2Periph_ADC1;

	ADC1 -> CR2 &= ~ADC_CR2_EXTSEL;
	ADC1 -> CR2 |= (ADC_CR2_EXTSEL_0|
					ADC_CR2_EXTSEL_1|
					ADC_CR2_EXTSEL_2);

	ADC1 -> CR2 |= ADC_CR2_EXTTRIG;

	ADC -> SQR1 &= ~ADC_SQR1_L; // L[3:0] = 0;

	ADC1 -> SMPR2 &= ~ADC_SMPR2_SMP1;
	ADC1 -> SMPR2 |= ADC_SMPR2_SMP1_0;
	ADC1 -> SQR3 &= ~ADC_SQR3_SQ1;
	ADC1 -> SQR3 |= ADC_SQR3_SQ1_0;

	ADC1 -> CR2 |= ADC_CR2_ADON; // ADC Enable

	while(1) {

		for(chNo = 0; CH[chNo] != 0xFF; chNo++) {

			ADC1 -> SQR3 &= ~ADC_SQR3_SQ1;
			ADC1 -> SQR3 |= CH[chNo];

			ADC1 -> CR2 |= ADC_CR2_SWSTART;
			while((ADC1 -> SR & ADC_SR_EOC) == 0) {}
			verti[chNo] = ADC1 -> DR;
		}
	}


}
#endif
